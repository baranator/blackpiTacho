#ifndef BTBLUETOOTH_H
#define BTBLUETOOTH_H
#include <stdint.h>
#include "gattlib.h"

#define BMS_MAX_CELLS 32
#define NUM_BT_DEVICES 2
#define BT_MAX_SCAN_DEVS 20

typedef enum btg_devtype {
	UNKNOWN=0,
	BMS_DALY=1,
	CTRL_FARDRIVER=2
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
	char address[18];
	char name[25];
	uint16_t key;
	gattlib_connection_t* connection;
	btg_bmsdata data;
} btg_dev;


char* btg_devtype2string(btg_devtype t);
btg_devtype btg_string2devtype(char* s);

btg_dev* gattbt_get_available_devices();
btg_dev gattbt_get_available_device(uint16_t i);
btg_dev* gattbt_get_devices();
void gattbt_init();


#endif
