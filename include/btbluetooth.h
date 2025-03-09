#ifndef BTBLUETOOTH_H
#define BTBLUETOOTH_H


typedef struct btg_av_dev{
	char mac_address[18];
	char name[25];
} btg_av_dev;


btg_av_dev* gattbt_get_available_devices();
void gattbt_init();

void btStartScan();
void btScanSetup(void (*newDevCallback)(const char*));

#endif
