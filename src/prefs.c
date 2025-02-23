#include "prefs.h"

bool retardUnits;
bool avasEnabled;
const char * battery1Address;
const char * battery2Address;
const char * motorControllerAddress;

bool prefSave(){
    return true;
}

bool prefGetAvasEnabled(){
    return avasEnabled;
}

void prefSetAvasEnabled(bool b){
    avasEnabled=b;
}

bool prefGetRetardUnits(){
    return retardUnits;
}

void prefSetRetardUnits(bool b){
    retardUnits=b;
    prefSave();
}

const char * prefGetBattery1Address(){
    return battery1Address;
}

bool prefLoad(){ 
    json_t * root=json_load_file("./settings.json",0 , NULL);
    if(root==NULL){
        return false;
    }
    
    
    
    if(0 != json_unpack(root, "{s:b, s:b, s:{s:s}, s:{s:s}, s:{s:s}", "retardUnits", &retardUnits, "avasEnabled", &avasEnabled, "battery1","address",&battery1Address, "battery2","address",&battery2Address, "motorController","address",&motorControllerAddress)){
        return false;
    }
    return true;
}

