/**
 **************************************************
 *
 * @file        alertPin.ino
 * 
 * @brief       Example showing how to configure alarm callbacks
 *              when using the ALR pin
 *
 * @link        solde.red/333175
 *
 * @authors     Nils Minor, modified by Josip Šimun Kuči @ soldered.com
 ***************************************************/
#include "Soldered-TMP117.h"

#define ALERT_PIN               26     // low active alert pin
#define LOW_TEMPERATURE_ALERT   20    // low alert at 20°C
#define HIGH_TEMPERATURE_ALERT  28    // highalert at 28°C

bool alert_flag = false;
Soldered_TMP117 tmp;
void setup() {

  // Initiate wire library and serial communication
  Wire.begin();
  Serial.begin(115200);

  tmp.init ( new_temperature );     // set callback function. will be called if there is new sensor data
  tmp.setConvMode (TMP117_CMODE::CONTINUOUS);     // contious measurement, also ONESHOT or SHUTWDOWN possible


  tmp.init ( new_temperature );
  tmp.setConvTime (TMP117_CONVT::C15mS5);         // 1. setup C125mS+NOAVE = 15.5 mS measurement time
  tmp.setAveraging (TMP117_AVE::NOAVE);
  
  tmp.setAlertMode(TMP117_PMODE::ALERT);          // use THERMAL or ALERT to activate alert feature
  tmp.setAlertCallback ( temperature_alert, ALERT_PIN );
  tmp.setAlertTemperature (LOW_TEMPERATURE_ALERT, HIGH_TEMPERATURE_ALERT);      
}

/************************* Infinite Loop Function **********************************/
void loop() {

  tmp.update();

  if (alert_flag) {
    if (tmp.getAlertType () == TMP117_ALERT::HIGHALERT) {
    Serial.print("High Temperature alert : ");
    Serial.print (tmp.getTemperature());
    Serial.println (" °C");
    }
    else if (tmp.getAlertType () == TMP117_ALERT::LOWALERT) {
      Serial.print("Low Temperature alert : ");
      Serial.print (tmp.getTemperature());
      Serial.println (" °C");
    }
    else {
      alert_flag = false;
    }
  }

  delay(100);
}

// calback for new temperature
void new_temperature ( void ) {
  if (!alert_flag) {
    Serial.print ("Temperature : ");
    Serial.print (tmp.getTemperature());
    Serial.println (" °C");
  }
}

// callback function when an temperature alert occurs
void temperature_alert (void) {
  alert_flag = true;
}