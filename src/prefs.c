#include <string.h>
#include "prefs.h"

bool retardUnits;
bool avasEnabled;
pref_btg_dev bluetooth_devices[NUM_BT_DEVICES];

bool prefSave(){
    json_t *btdevs=json_array();
    
    for(int i=0;i<NUM_BT_DEVICES;i++){
        char* tp;
        //printf("%s\n",dtype);
        if(bluetooth_devices[i].type == BMS_DALY){
            tp="bms_daly";
        }else if(bluetooth_devices[i].type == CTRL_FARDRIVER){
            tp="ctrl_fardriver";
        }else{
            tp="xxy";
        }
        
        json_t* t=json_pack("{s:s,s:s}", "address", bluetooth_devices[i].address, "type", tp);
        json_array_append(btdevs, t);
    }

    json_t * root =json_pack("{s:b, s:b, s:o}", "retardUnits", retardUnits, "avasEnabled", avasEnabled, "bluetooth_devices",btdevs);
    
   // printf("Settings loaded successfully: pref-returncode: %d\n",ret);
    return json_dump_file(root, "bin/settings2.json", JSON_INDENT(2));
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

const char * prefGetBtDeviceAddress(int i){
    if(i>=NUM_BT_DEVICES)
        return NULL;
    return bluetooth_devices[i].address;
}

void prefSetBtDeviceAddress(int i,char* a){
    if(i>=NUM_BT_DEVICES)
        return;
    strcpy(bluetooth_devices[i].address, a);
}

bool prefLoad(){ 
    json_t * root=json_load_file("bin/settings.json",0 , NULL);
    if(root==NULL){
        printf("settings.json not found/bad format");
        return false;
    }
    
    json_t* btdevs;;
    int ret=json_unpack(root, "{s:b, s:b, s:o}", "retardUnits", &retardUnits, "avasEnabled", &avasEnabled, "bluetooth_devices",&btdevs);
    

    if(0 != ret){
        return false;
    }
    
    int num_bt_devs=json_array_size(btdevs);
    printf("asize %d\n",num_bt_devs);
    
    if(num_bt_devs>NUM_BT_DEVICES){
        return false;
    }
    
    for(int i=0;i<num_bt_devs;i++){
        printf("grundsturktur psst\n");
        json_t* t=json_array_get(btdevs,i);
        char* dtype,*dadd;
        json_unpack(t, "{s:s,s:s}", "address", &dadd, "type", &dtype);
        strcpy(bluetooth_devices[i].address, dadd);
        
        printf("DEVCIE_ADR:%s\n",bluetooth_devices[i].address);
        //printf("%s\n",dtype);
        if(strcmp(dtype,"bms_daly") == 0){
            bluetooth_devices[i].type=BMS_DALY;
        }else if(strcmp(dtype,"ctrl_fardriver") == 0){
            bluetooth_devices[i].type=CTRL_FARDRIVER;
        }else{
            bluetooth_devices[i].type=UNKNOWN;
        }
        
    }
    
    printf("Settings loaded successfully: pref-returncode: %d\n",ret);
    return true;
}

