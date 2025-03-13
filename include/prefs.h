#ifndef PREFS_H
#define PREFS_H
#include <stdbool.h>
#include<jansson.h>

#include "btbluetooth.h"


bool prefSave();
bool prefGetAvasEnabled();
void prefSetAvasEnabled(bool b);
bool prefGetRetardUnits();
void prefSetRetardUnits(bool b);

btg_dev * prefGetBtDevices();

const char * prefGetBtDeviceAddress(int i);
void prefSetBtDeviceAddress(int i,char* a);

void prefSetBtDeviceType(int i, btg_devtype t);
btg_devtype* prefGetBtDeviceType(int i);

char* btg_devtype2string(btg_devtype t);
bool prefLoad();




#endif
