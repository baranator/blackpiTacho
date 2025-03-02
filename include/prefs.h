#ifndef PREFS_H
#define PREFS_H
#include <stdbool.h>
#include<jansson.h>

#define NUM_BT_DEVICES 3


typedef enum btg_devtype {
	UNKNOWN=0,
	BMS_DALY=1,
	CTRL_FARDRIVER=2
} btg_devtype;


typedef struct pref_btg_dev{
	btg_devtype type;
	char address[18];
} pref_btg_dev;


bool prefSave();
bool prefGetAvasEnabled();
void prefSetAvasEnabled(bool b);
bool prefGetRetardUnits();
void prefSetRetardUnits(bool b);
const char * prefGetBtDeviceAddress(int i);
bool prefLoad();




#endif
