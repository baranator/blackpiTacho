#ifndef PREFS_H
#define PREFS_H
#include <stdbool.h>
#include<jansson.h>


#include "prefs.h"


bool prefSave();
bool prefGetAvasEnabled();
void prefSetAvasEnabled(bool b);
bool prefGetRetardUnits();
void prefSetRetardUnits(bool b);
const char * prefGetBattery1Address();
bool prefLoad();




#endif
