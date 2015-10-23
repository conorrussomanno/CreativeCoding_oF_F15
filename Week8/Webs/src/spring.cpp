#include "spring.h"

//---------------------------------------------------------------------
spring::spring(){
	particleA = NULL;
	particleB = NULL;
}

//---------------------------------------------------------------------
void spring::update(){
	if ((particleA == NULL) || (particleB == NULL)){
		return;
	}
	
	ofVec2f pta = particleA->pos;
	ofVec2f ptb = particleB->pos;
	
	float theirDistance = (pta - ptb).length();
	float springForce = (springiness * (distance - theirDistance));
	ofVec2f frcToAdd = (pta-ptb).normalized() * springForce;
	
    if(theirDistance>distance){
        particleA->addForce(frcToAdd.x, frcToAdd.y);
        particleB->addForce(-frcToAdd.x, -frcToAdd.y);
    }
}


//---------------------------------------------------------------------
void spring::draw(){
	
	if ((particleA == NULL) || (particleB == NULL)){
		return;
	}
    float tempGray = 200;
    int randoRange = 3;
	ofSetColor(tempGray, tempGray, tempGray);
    ofLine((particleA->pos.x)+particleA->x1, particleA->pos.y+particleA->y1, particleB->pos.x+particleB->x1, particleB->pos.y+particleB->y1);
    
    
    tempGray = 150;
	ofSetColor(tempGray, tempGray, tempGray);
    ofLine((particleA->pos.x)+particleA->x2, particleA->pos.y+particleA->y2, particleB->pos.x+particleB->x2, particleB->pos.y+particleB->y2);
    
    
    tempGray = 100;
	ofSetColor(tempGray, tempGray, tempGray);
    ofLine((particleA->pos.x)+particleA->x3, particleA->pos.y+particleA->y3, particleB->pos.x+particleB->x3, particleB->pos.y+particleB->y3);
    
}