//
//  Leaf.h
//  Leaves
//
//  Created by Conor Russomanno on 9/10/15.
//
//

#ifndef __Leaves__Leaf__
#define __Leaves__Leaf__

#include "ofMain.h"

class Leaf {
    
    public:
    
        void setup();
        void update();
        void draw();
    
    // stuff pertaining to each instance of the Leaf class
    private:
    
        ofColor stemColor;
        ofColor leafColor;
        float xPos, yPos;
        float scaleFactor;
        float rotation;
    
        float stemLength, stemWidth;
        float leafLength, leafWidth;
        float leafCurvature;
    
};

#endif /* defined(__Leaves__Leaf__) */
