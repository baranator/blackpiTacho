#ifndef BTBLUETOOTH_H
#define BTBLUETOOTH_H

char (*gattbt_get_available_devices())[18];
void gattbt_init();

void btStartScan();
void btScanSetup(void (*newDevCallback)(const char*));

#endif
