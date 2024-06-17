#pragma once

#include "Arduino.h"




class DA62_Oxygen_Gauge
{
public:
    DA62_Oxygen_Gauge();
    void begin();
    void attach();
    void detach();
    void set(int16_t messageID, char *setPoint);
    void update();

private:
    bool    _initialised;
    uint8_t _pin1, _pin2, _pin3;

    // Values from Sim
    double OxygenPSIValue = 0;     // Value of the Oxygen PSI
    double InstrumentBrightnessRatio = 1; // Instrument Brightness ratio
    double InstrumentBrightness; // Instrument Brightness for TFT

    // Needel Rotation in degrees
    int needleRotDegrees = -140;

    // Scale function
    float scaleValue (float x, float in_min, float in_max, float out_min, float out_max); 

    // Setters
    void setOxygenPSIValue(double value);
    void setInstrumentBrigthnessRatio(double ratio);
    void setInstrumentBrightness(double brightness);
    void setNeedleRotationDegrees(double value);

};

