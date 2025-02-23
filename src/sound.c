#include <stdint.h>

#include "sound.h"
#include "assets/avassound.h"

//#include <ESP_I2S.h>
//#include <DebugLog.h>

bool sound_on=true;
unsigned long laststep;
unsigned long i=0;
unsigned int rate=100;
uint8_t volume_perc=70;
int8_t fac=1;
#define PLAY_BUF_SIZE 100 //should be a multiple of 100

unsigned char play_buffer[PLAY_BUF_SIZE]; 



/** sanitize index */
uint16_t sind(uint16_t i){
  i=i%sizeof(avasbytes);
  return i;
}

void soundLoop() {


}

void soundT(void *pvParameters){

}

void soundSetup(){
 // laststep=millis();

//   xTaskCreate(
//     soundT,       // Function name of the task
//     "Blink 1",    // Name of the task (e.g. for debugging)
//     2048,         // Stack size (bytes)
//     NULL,         // Parameter to pass
//     1,            // Task priority
//     NULL // Task handle
// );

 // I2S.setPins(0,18, 17); //SCK, WS, SDOUT, SDIN, MCLK
 // I2S.begin(I2S_MODE_STD, 22000, I2S_DATA_BIT_WIDTH_8BIT, I2S_SLOT_MODE_MONO);

}
void soundEnable(){

  sound_on=true;
}
void soundDisable(){
  sound_on=false;
}
