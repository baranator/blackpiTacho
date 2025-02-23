#ifndef BTBLUETOOTH_H
#define BTBLUETOOTH_H



void btStartScan();
void btScanSetup(void (*newDevCallback)(const char*));

#endif