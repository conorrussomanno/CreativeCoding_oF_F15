#pragma once

#include "ofMain.h"

class Bird : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    ofPoint pos, vel, acc; //variable that belong to each bird
    
};