#ifndef PREFS_H
#define PREFS_H
#include <stdbool.h>
#include<jansson.h>

#include "btbluetooth.h"


// typedef struct pref_btg_dev{
// 	btg_devtype type;
// 	char address[18];
// } pref_btg_dev;


bool prefSave();
bool prefGetAvasEnabled();
void prefSetAvasEnabled(bool b);
bool prefGetRetardUnits();
void prefSetRetardUnits(bool b);
const char * prefGetBtDeviceAddress(int i);
void prefSetBtDeviceAddress(int i,char* a);

void prefSetBtDeviceType(int i, btg_devtype t);
char* btg_devtype2string(btg_devtype t);
bool prefLoad();




#endif
