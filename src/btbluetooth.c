//#include <Arduino.h>

#include "btbluetooth.h"

int scanTime = 5; // in seconds
// BLEScan* pBLEScan;


// class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
//   void (*cb)(const char*);
//   public:
//   MyAdvertisedDeviceCallbacks(void(*newDevCallback)(const char*)){
//     cb=newDevCallback;
//   }
//     void onResult(BLEAdvertisedDevice advertisedDevice) {
//       //Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
//       (*cb)(advertisedDevice.getName().c_str());
//     }
//   };

void btScanSetup(void(*newDevCallback)(const char*)){
    // BLEDevice::init("");
    // 
    // pBLEScan = BLEDevice::getScan(); //create new scan
    // pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(newDevCallback));
    // pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    // pBLEScan->setInterval(100);
    // pBLEScan->setWindow(99);  // less or equal setInterval value
}
void btStartScan(){
    // BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);

}
