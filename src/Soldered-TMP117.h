/**
 **************************************************
 *
 * @file        Soldered-TMP117.h
 * @brief       Header file for the TMP117 temperature sensor.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Josip Šimun Kuči @ soldered.com
 ***************************************************/
#include "libs/TMP117-Arduino/TMP117.h"

// Create a custom class constructor that creates a default address
// if none are provided
class Soldered_TMP117 : public TMP117 {
public:
    Soldered_TMP117(uint8_t address = 0x49) 
        : TMP117(address) 
    {
    }
};
