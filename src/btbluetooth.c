#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>

#include "btbluetooth.h"

int scanTime = 5; 

char available_bt_devices[20][18];
atomic_int lastInsert=0;

pthread_t gattbt_bgthread;

atomic_bool btjob_scan=true;


static pthread_mutex_t m_available_bt_devices_lock = PTHREAD_MUTEX_INITIALIZER;


char (*gattbt_get_available_devices())[18]{
	return available_bt_devices;
}

void btScanSetup(void(*newDevCallback)(const char*)){
}
void btStartScan(){
}





#include <ctype.h>
#include <glib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef GATTLIB_LOG_BACKEND_SYSLOG
#include <syslog.h>
#endif

#include "gattlib.h"

#define BLE_SCAN_TIMEOUT   10


#define NUM_BT_DEVICES 2
#define BMS_MAX_CELLS 32

typedef enum btg_devtype {
	UNKNOWN=0,
	DALYBMS=1,
	FARDRIVER=2
} btg_devtype;


typedef struct btg_bmsdata{
	uint16_t soc_perm;
	uint16_t voltage_x10;
	int32_t current_x10;
	uint8_t num_cells;
	uint16_t cell_voltage_x10[BMS_MAX_CELLS];
	
} btg_bmsdata;

typedef struct btg_dev{
	btg_devtype type;
	char* mac_address;
	gattlib_connection_t* connection;
	btg_bmsdata data;
} btg_dev;


btg_dev btg_devices[NUM_BT_DEVICES]; 



static struct {
	char *adapter_name;
	char* mac_address;
	uuid_t gatt_notification_uuid;
	uuid_t gatt_write_uuid;
	long int gatt_write_data;
} m_argument;

// Declaration of thread condition variable
static pthread_cond_t m_connection_terminated = PTHREAD_COND_INITIALIZER;

// declaring mutex
static pthread_mutex_t m_connection_terminated_lock = PTHREAD_MUTEX_INITIALIZER;



static int stricmp(char const *a, char const *b) {
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

void btg_parse_data_dalybms(btg_dev* d, const uint8_t* data, size_t data_length){
	printf("parsedaly");
		if(data[2]==0x90){
			d->data.soc_perm=data[10]*256+data[11];
			d->data.current_x10=data[8]*256+data[9]-30000;
			d->data.voltage_x10=data[4]*256+data[5];
			
		printf("SOC:\n");
		printf("overall volt x10: %d\n",d->data.voltage_x10);
		printf("current x10: %d\n",d->data.current_x10);
		printf("soc perm: %d\n",d->data.soc_perm);
	}
	
	           //  "total_voltage": parts[0] / 10,
            // # "x_voltage": parts[1] / 10, # always 0
            // "current": (parts[2] - 30000) / 10,  # negative=charging, positive=discharging
            // "soc_percent": parts[3] / 10
}


static void notification_handler(const uuid_t* uuid, const uint8_t* data, size_t data_length, void* user_data) {

	GATTLIB_LOG(GATTLIB_INFO, "notif invcomming");

	printf("Notification Handler: ");
	char* addr=(char*)user_data;
	printf(addr);
	
	//scan devarray for adress, then fill data.attribvte
	for (unsigned int i = 0; i < data_length; i++) {
		printf("%02x ", data[i]);
	}
	printf("\n");
	
	for(unsigned int i=0;i<NUM_BT_DEVICES;i++){
		printf("dev %d \n",i);
		if(btg_devices[i].mac_address!=NULL && stricmp(btg_devices[i].mac_address, addr)==0){
			printf("treffer ");
			if(btg_devices[i].type == DALYBMS){
				btg_parse_data_dalybms(btg_devices+i,data,data_length);
			}
			
		}
		
	}


	

}




void setup_dalybms(const char *addr, gattlib_connection_t* connection){
	int ret;
	char* ktmps="f000ffc2-0451-4000-b000-000000000000";
	uuid_t kickoff;

	char* ntmps="0000fff1-0000-1000-8000-00805f9b34fb";
	uuid_t notify;

	char* wtmps="0000fff2-0000-1000-8000-00805f9b34fb";
	uuid_t wri;
	
	gattlib_string_to_uuid(ktmps, strlen(ktmps) + 1, &kickoff);
	gattlib_string_to_uuid(ntmps, strlen(ntmps) + 1, &notify);
	gattlib_string_to_uuid(wtmps, strlen(wtmps) + 1, &wri);
	
	
	ret = gattlib_register_notification(connection, notification_handler, (char
	*)addr);
	if (ret) {
		GATTLIB_LOG(GATTLIB_ERROR, "Fail to register notification callback.");
		goto EXIT;
	}

	ret = gattlib_notification_start(connection, &notify);
	if (ret) {
		GATTLIB_LOG(GATTLIB_ERROR, "Fail to start notification.");
		goto EXIT;
	}

	GATTLIB_LOG(GATTLIB_INFO, "notifyok1");
	//SOC, OVERALLVOLTAGE, CURRENT
	char arr[13] = {0xa5,0x80,0x90,0x08,0,0,0,0,0,0,0,0,0xbd};
	
	GATTLIB_LOG(GATTLIB_INFO, "notifyok2");

	ret = gattlib_write_char_by_uuid(connection, &kickoff, "", 0);
	if (ret != GATTLIB_SUCCESS) {
		GATTLIB_LOG(GATTLIB_INFO, "kickofffail");
	}
	GATTLIB_LOG(GATTLIB_INFO, "notifyok2.5");
	

	GATTLIB_LOG(GATTLIB_INFO, "notifyok3");

	ret = gattlib_write_char_by_uuid(connection, &wri, arr, sizeof(arr));
	if (ret != GATTLIB_SUCCESS) {
			GATTLIB_LOG(GATTLIB_INFO, "writefail");
	}


	GATTLIB_LOG(GATTLIB_INFO, "Wait for notification for 20 seconds...");
	g_usleep(20 * G_USEC_PER_SEC);
	
EXIT:
	gattlib_disconnect(connection, false /* wait_disconnection */);

	pthread_mutex_lock(&m_connection_terminated_lock);
	pthread_cond_signal(&m_connection_terminated);
	pthread_mutex_unlock(&m_connection_terminated_lock);
}

void btg_setup_device(const char *addr, gattlib_connection_t* connection){
	GATTLIB_LOG(GATTLIB_ERROR, "setting up device: ",addr);
	setup_dalybms(addr, connection);
}

static void on_device_connect(gattlib_adapter_t* adapter, const char *addr, gattlib_connection_t* connection, int error, void* user_data) {
	//m_argument.gatt_write_data=0xa580 9308 0000 0000 0000 0000 c0;
	
	
	GATTLIB_LOG(GATTLIB_ERROR, addr);
	btg_setup_device(addr, connection);
	
	
	
	

}


static void ble_discovered_device(gattlib_adapter_t* adapter, const char* addr, const char* name, void *user_data) {
	int ret;
	int16_t rssi;
	
	strcpy(available_bt_devices[lastInsert], addr);
	printf( "Found other bluetooth device '%s', putitng it to %d \n", addr,lastInsert);
	lastInsert=(lastInsert+1)%20;
	
	return;
	
	
	if (stricmp(addr, m_argument.mac_address) != 0) {
		GATTLIB_LOG(GATTLIB_INFO, "Found other bluetooth device '%s'", addr);
		return;
	}

	ret = gattlib_get_rssi_from_mac(adapter, addr, &rssi);
	if (ret == 0) {
		GATTLIB_LOG(GATTLIB_INFO, "Found bluetooth device '%s' with RSSI:%d", m_argument.mac_address, rssi);
	} else {
		GATTLIB_LOG(GATTLIB_INFO, "Found bluetooth device '%s'", m_argument.mac_address);
	}

	ret = gattlib_connect(adapter, addr, GATTLIB_CONNECTION_OPTIONS_NONE, on_device_connect, NULL);
	if (ret != GATTLIB_SUCCESS) {
		GATTLIB_LOG(GATTLIB_ERROR, "Failed to connect to the bluetooth device '%s'", addr);
	}else{
		GATTLIB_LOG(GATTLIB_ERROR, "Connected to the bluetooth device '%s'", addr);
		
	}
}

static void* ble_task(void* arg) {
	char* addr = arg;
	gattlib_adapter_t* adapter;
	int ret;

	//openadapter
	ret = gattlib_adapter_open(m_argument.adapter_name, &adapter);
	while(ret!=GATTLIB_SUCCESS){
		GATTLIB_LOG(GATTLIB_ERROR, "Failed to open adapter.retry in 2s");
		g_usleep(20 * G_USEC_PER_SEC);
		ret = gattlib_adapter_open(m_argument.adapter_name, &adapter);
	}
	GATTLIB_LOG(GATTLIB_INFO, "adapter opened");
	
	while(true){
		if(btjob_scan){
			btjob_scan=false;
			ret = gattlib_adapter_scan_enable(adapter, ble_discovered_device, BLE_SCAN_TIMEOUT, addr);
			if (ret) {
				GATTLIB_LOG(GATTLIB_ERROR, "Failed to scan.");
				return NULL;
			}
			GATTLIB_LOG(GATTLIB_INFO, "scan succ");
		}
	}
	


}

void gattbt_disconnect(){
	
}

void gattbt_startcrawl(){
	
}



void gattbt_scan(){
	
}

bool gattbt_connect(const char* addr, int type){
	
	return true;
}


void* gattbt_bgthread_f(void* vargp){	
    
    int ret = gattlib_mainloop(ble_task, NULL);
	GATTLIB_LOG(GATTLIB_ERROR, "running!");
	if (ret != GATTLIB_SUCCESS) {
		GATTLIB_LOG(GATTLIB_ERROR, "Failed to create gattlib mainloop");
	}
	GATTLIB_LOG(GATTLIB_ERROR, "running!!!!!");
   
}

void gattbt_init(){
	int ret;
    pthread_create(&gattbt_bgthread, NULL, gattbt_bgthread_f, NULL);


}

int smain(int argc, char *argv[]) {
	

	m_argument.adapter_name = NULL;
	//m_argument.mac_address = "E4:52:49:AE:AC:2C";
	m_argument.mac_address = "86:68:02:01:0d:2d";
	btg_devices[0].mac_address = "86:68:02:01:0d:2d";
	btg_devices[0].type = DALYBMS;
	gattbt_init();

	return 0;
}

