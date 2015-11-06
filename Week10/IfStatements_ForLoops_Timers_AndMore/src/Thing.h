#pragma once

#include "ofMain.h"

class Thing : public ofBaseApp{
    
public:
    void setup(float xLocation, float yLocation);
    void update();
    void draw();
    ofColor returnNewColor(int thingNumber, int numThings);
    
    //my custom method
    ofPoint pos; //has .x, .y, .z by default
    ofPoint vel; //has .x, .y, .z by default
    ofPoint acc; //has .x, .y, .z by default
    int diameter;
    ofColor myColor;
    
};