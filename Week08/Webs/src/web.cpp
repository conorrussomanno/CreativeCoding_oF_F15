//
//  web.cpp
//  springs
//
//  Created by Conor Russomanno on 11/26/12.
//
//

#include "web.h"
#include "ofMain.h"

//---------------------------------------------------------------------
void web::setInitialCondition(int x, int y){

    center.x = x; //center of web, values retrieved from mouse pressed
    center.y = y;
    cout << "center " << center.x << " " << center.y << endl;
    numSpines = (int)ofRandom(10,30); //spines coming out from center of web
    cout << numSpines << endl;
    numSpirals = (int)ofRandom(5,30); //number of times the circular webs spiral the center
    cout << numSpirals << endl;
    splitAvg = ofRandom(20,50); //average split between each spiral
    cout << splitAvg << endl;
    
    float spineAngle[numSpines]; //array for number of spines
    for (int i = 0; i < numSpines; i++) {
        spineAngle[i] = (float)((360)/numSpines)*(i) + ofRandom(15); //sets angle of the various spines with slight randomization to obtain "natural" look
        cout << i << " " << spineAngle[i] << endl;
    }
    
    //nodes for spring connections:
    for (int i=0; i < 1; i++){
        particle *tempParticle = new particle();
        tempParticle->setInitialCondition(center.x, center.y, 0, 0);
        nodes.push_back(tempParticle);
    }
    
    for (int i=0; i < numSpirals; i++){
        for (int j=0; j < numSpines; j++){
            particle *tempParticle = new particle();
            float angle = spineAngle[j]; //just use angle of j...
            float radius = j*(splitAvg/numSpines) + i*splitAvg;
            cout << "radius " << i << " " << j << " " << radius << endl;
            cout << "angle " << i << " " << j << " " << angle << endl;
            float adjustedX, adjustedY;
            adjustedX = center.x + radius * cos(spineAngle[j]*(PI/180)); //
            adjustedY = center.y + radius * sin(spineAngle[j]*(PI/180));
            cout << adjustedX << " " << adjustedY << endl;
            tempParticle->setInitialCondition(adjustedX, adjustedY, 0, 0);
            nodes.push_back(tempParticle);
        }
    }
    
    //spring connections:
    for(int i = 0; i < nodes.size()-1; i++){    //creates spiral lines
        spring mySpring;
        mySpring.distance = ofDist(nodes[i]->pos.x, nodes[i]->pos.y, nodes[i+1]->pos.x, nodes[i+1]->pos.y);
        mySpring.springiness	= 0.04f;
        mySpring.particleA = nodes[i];
        mySpring.particleB = nodes[i+1];
        springs.push_back(mySpring);
    }
    
    for (int i = 0; i<numSpirals*numSpines-numSpines; i++) { //creates all other layers of spines
        spring mySpring;
        mySpring.distance = ofDist(nodes[i]->pos.x, nodes[i]->pos.y, nodes[i+numSpines]->pos.x, nodes[i+numSpines]->pos.y);
        mySpring.springiness	= 0.04f;
        mySpring.particleA = nodes[i];
        mySpring.particleB = nodes[i+numSpines];
        springs.push_back(mySpring);

    }
    
    cout << "springs.size(): " << springs.size() << endl;
    
}

//---------------------------------------------------------------------
void web::update(){
    for (int i = 0; i < nodes.size(); i++){
		nodes[i]->resetForce();
	}
	
	
	for (int i = 0; i < nodes.size(); i++){
		//particles[i].addForce(0,0.1);
	}
    
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
	
	for (int i = 0; i < nodes.size(); i++){
		nodes[i]->addDampingForce();
		nodes[i]->update();
	}

}


void web::stretchWeb(int x, int y){
    //find closest node
    int closestNode;
    float nodeDistance = ofGetScreenWidth();
    for(int i = 0; i<nodes.size(); i++){
        if(ofDist(nodes[i]->pos.x, nodes[i]->pos.y, x, y)<nodeDistance){
            nodeDistance = ofDist(nodes[i]->pos.x, nodes[i]->pos.y, x, y);
            closestNode = i;
        }
    }
    nodes[closestNode]->pos.x = x;
    nodes[closestNode]->pos.y = y;
    
    //set closest node position equal to mouse position
//    cout << "springs.size(): " << springs.size() << endl;
}


//---------------------------------------------------------------------
void web::draw(){
    if (nodes.size()>0) {
        for(int i = 0; i < nodes.size()-1; i++){    //creates spiral lines
            ofPushStyle();
            ofSetColor(255, 255, 255);
            ofEllipse(nodes[i]->pos.x, nodes[i]->pos.y, 3, 3);
            ofPopStyle();
            ofLine(nodes[i]->pos.x, nodes[i]->pos.y, nodes[i+1]->pos.x, nodes[i+1]->pos.y);
        }
        
        for(int i = 0; i < numSpines; i++){ //creates inner-most layer of spine lines from center of web
            ofLine(nodes[0]->pos.x, nodes[0]->pos.y, nodes[1+i]->pos.x, nodes[1+i]->pos.y);
            
            ofPushStyle();
            ofSetColor(200);
            ofLine(nodes[0]->pos.x, nodes[0]->pos.y, nodes[1+i]->pos.x+nodes[1+i]->x1, nodes[1+i]->pos.y+nodes[1+i]->y1);
            ofSetColor(150);
            ofLine(nodes[0]->pos.x, nodes[0]->pos.y, nodes[1+i]->pos.x+nodes[1+i]->x2, nodes[1+i]->pos.y+nodes[1+i]->y2);
            ofSetColor(100);
            ofLine(nodes[0]->pos.x, nodes[0]->pos.y, nodes[1+i]->pos.x+nodes[1+i]->x3, nodes[1+i]->pos.y+nodes[1+i]->y3);
            ofPopStyle();
        }
        
        for (int i = 0; i<numSpirals*numSpines-numSpines; i++) { //creates all other layers of spines
            ofLine(nodes[i]->pos.x, nodes[i]->pos.y, nodes[i+numSpines]->pos.x, nodes[i+numSpines]->pos.y);
        }
        for(int i = 0; i < springs.size(); i++){
            springs[i].draw();
        }
    }
}