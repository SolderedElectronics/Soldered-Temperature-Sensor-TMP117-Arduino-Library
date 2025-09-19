/**
 **************************************************
 *
 * @file        simpleReading.ino
 * 
 * @brief       Example showing how to take temperature measurements every
 *              100ms in Celsius
 *
 * @link        solde.red/333175
 *
 * @authors     Nils Minor, modified by Josip Šimun Kuči @ soldered.com
 ***************************************************/
#include "Soldered-TMP117.h"

// Our breakout has the I2C address of 0x49 by default which can be changed by 
// connecting the onboard jumpers

// If you're using the default address, you can declare the object like so:
Soldered_TMP117 tmp;

// Otherwise declare it as so:
// Soldered_TMP117 tmp(0x48);

/************************* Initialization Setup Function **************************/
void setup() {
  // Initiate wire library and serial communication
  Wire.begin();           
  Serial.begin(115200);

  /* The default setup is :
   *    Conversion mode = CONTINUOUS  ---> continuous
   *    Conversion time = C125mS      -|
   *    Averaging mode  = AVE8        -|-> new data every 125mS
   *    Alert mode      = data        ---> alert pin states that new data is available
   *    
   */
  tmp.init ( NULL );    
}

/************************* Infinite Loop Function **********************************/
void loop() {

  Serial.print ("Temperature : ");
  Serial.print (tmp.getTemperature());
  Serial.println (" °C");
  delay(100);
}