#include "DA62_Oxygen_Gauge.h"
#include "allocateMem.h"
#include "commandmessenger.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <gauge_face.h>
#include <needle.h>

/* **********************************************************************************
    This is just the basic code to set up your custom device.
    Change/add your code as needed.
********************************************************************************** */

long int startTime;

int drefOxygenPSI;         // this stores a handle to the Oxygen PSI

int drefBeacon;           // Beacon status dataref

float OxygenPSIValue;     // Value of the Oxygen PSI

int drefRPM;

float engineRPM = 0;

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// Sprites used in display
TFT_eSprite mainSpr = TFT_eSprite(&tft); // Main sprite. Full screen.

// The main gauge sprite
TFT_eSprite gaugeSpr = TFT_eSprite(&tft); // Needle Sprite

// The needle need to be sprite so it can be rotated and masked.
TFT_eSprite needleSpr = TFT_eSprite(&tft); // Needle Sprite

TFT_eSprite needleBackSpr = TFT_eSprite(&tft); // Needle Sprite

// Not passing any PINs
DA62_Oxygen_Gauge::DA62_Oxygen_Gauge(uint8_t Pin1, uint8_t Pin2)
{

}

void DA62_Oxygen_Gauge::begin()
{
}

void DA62_Oxygen_Gauge::attach(uint16_t Pin3, char *init)
{
    _pin3 = Pin3;
}

void DA62_Oxygen_Gauge::detach()
{
    if (!_initialised)
        return;
    _initialised = false;
}

void DA62_Oxygen_Gauge::set(int16_t messageID, char *setPoint)
{
    /* **********************************************************************************
        Each messageID has it's own value
        check for the messageID and define what to do.
        Important Remark!
        MessageID == -2 will be send from the board when PowerSavingMode is set
            Message will be "0" for leaving and "1" for entering PowerSavingMode
        MessageID == -1 will be send from the connector when Connector stops running
        Put in your code to enter this mode (e.g. clear a display)

    ********************************************************************************** */
    int32_t  data = atoi(setPoint);
    uint16_t output;

    // do something according your messageID
    switch (messageID) {
    case -1:
        // tbd., get's called when Mobiflight shuts down
    case -2:
        // tbd., get's called when PowerSavingMode is entered
    case 0:
        output = (uint16_t)data;
        data   = output;
        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    default:
        break;
    }
}

void DA62_Oxygen_Gauge::update()
{
    // Do something which is required regulary
}
