#pragma once

#include "ofMain.h"

class Bird : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    vector<ofPoint> posPrevious; //keep track of where this bird has been
    ofPoint pos, vel, acc; //variable that belong to each bird
    float radius;
    int tailLength; //number of segments of tail
    
};