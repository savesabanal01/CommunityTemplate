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


TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// Sprites used in display
TFT_eSprite mainSpr = TFT_eSprite(&tft); // Main sprite. Full screen.

// The main gauge sprite
TFT_eSprite gaugeSpr = TFT_eSprite(&tft); // Needle Sprite

// The needle need to be sprite so it can be rotated and masked.
TFT_eSprite needleSpr = TFT_eSprite(&tft); // Needle Sprite

TFT_eSprite needleBackSpr = TFT_eSprite(&tft); // Needle Sprite

// Not passing any PINs
DA62_Oxygen_Gauge::DA62_Oxygen_Gauge()
{

}

void DA62_Oxygen_Gauge::begin()
{

    pinMode(LED_BUILTIN, OUTPUT);     // built in LED on arduino board will turn on and off with the status of the beacon light
    digitalWrite(LED_BUILTIN, HIGH);
  

   delay(1000); // wait for serial monitor to open
   

   Serial.println("\r\nOxygen Gauge Start\n");

    digitalWrite(LED_BUILTIN, LOW);

 

    tft.begin();
    tft.setRotation(0); // 0 & 2 Portrait. 1 & 3 landscape
    tft.fillScreen(TFT_BLACK); // Clear screen. We are only going to use the top part. If you don't clear, the bottom half will be noise.


    // Create the gauge sprite
    gaugeSpr.createSprite(240, 240);
    gaugeSpr.setSwapBytes(true);
    gaugeSpr.fillSprite(TFT_BLACK);
    // Set the pivot point for the needle to rotate
    gaugeSpr.setPivot(120, 120); 
    gaugeSpr.pushImage(0, 0, 240, 240, gauge_face);

    // Create the needle sprite
    needleSpr.createSprite(28, 148);
    needleSpr.setSwapBytes(true);
    needleSpr.setPivot(14, 110); 
    needleSpr.fillScreen(TFT_BLACK);
    needleSpr.pushImage(0, 0, 28, 148, needle);
    

    
}

void DA62_Oxygen_Gauge::attach()
{

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
    // int32_t  data = atoi(setPoint);
    // uint16_t output;

    // do something according your messageID
    switch (messageID) {
    case -1:
        // tbd., get's called when Mobiflight shuts down
    case -2:
        // tbd., get's called when PowerSavingMode is entered
    case 0:
        setOxygenPSIValue(atof(setPoint));
        break;
    case 1:
        /* code */
        setInstrumentBrigthnessRatio(atof(setPoint));
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

  gaugeSpr.pushImage(0, 0, 240, 240, gauge_face);

  needleSpr.pushImage(0, 0, 28, 148, needle);
  needleSpr.setSwapBytes(false);

  needleRotDegrees = map(OxygenPSIValue, 0, 4000, -140, 140);
  // Map the Oxygen PSI value to the degrees of rotation of the needle

  Serial.println(needleRotDegrees);

  needleSpr.setSwapBytes(false);
  needleSpr.pushRotated(&gaugeSpr, needleRotDegrees, TFT_BLACK);
  needleSpr.setSwapBytes(true);
  
  gaugeSpr.pushSprite(0, 0, TFT_BLACK);

  InstrumentBrightness = int(scaleValue(InstrumentBrightnessRatio, 0.1, 1, 0, 255));
  // Set the instrument light brightness
  analogWrite(TFT_BL, InstrumentBrightness);

}



// Scale function
float DA62_Oxygen_Gauge::scaleValue (float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void DA62_Oxygen_Gauge::setOxygenPSIValue(double value) 
{
    OxygenPSIValue = value;
    setNeedleRotationDegrees(value);
}

void DA62_Oxygen_Gauge::setInstrumentBrigthnessRatio(double ratio)
{
    InstrumentBrightnessRatio = ratio;
    setInstrumentBrightness(ratio);
}

void DA62_Oxygen_Gauge::setInstrumentBrightness(double ratio)
{
    InstrumentBrightness = scaleValue(ratio, 0.15, 1, 0, 255);
}

void DA62_Oxygen_Gauge::setNeedleRotationDegrees(double value)
{
    needleRotDegrees = map((int)value, 0, 4000, -140, 140);
}