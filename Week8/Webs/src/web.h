//
//  web.h
//  springs
//
//  Created by Conor Russomanno on 11/26/12.
//
//
#include "ofMain.h"
#include "particle.h"
#include "spring.h"

#ifndef springs_web_h
#define springs_web_h

class web {
    
public:

    void setInitialCondition(int x, int y);
    void update();
    void draw();
    void stretchWeb(int x, int y);
    
    int numSpines;
    int numSpirals;
    float splitAvg;
    
    ofVec2f center;
    
    vector <particle*> nodes;
    vector <spring> springs;
	
};

#endif
