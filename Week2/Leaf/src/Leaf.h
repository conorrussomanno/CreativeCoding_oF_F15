//
//  Leaf.h
//  Leaf
//
//  Created by Conor Russomanno on 9/10/15.
//
//

#ifndef __Leaf__Leaf__
#define __Leaf__Leaf__

#include "ofMain.h"

class Leaf : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
private:
    
    //LEAFE VARIABLES
    float xPos, yPos; //position
    float leafLength, leafWidth;//leaf length/width
    float stemLength, stemWidth; //stem
    float rotation; //rotation
    ofColor stemColor, leafColor; //color
    float scaleFactor; //scale
    
};

#endif /* defined(__Leaf__Leaf__) */
