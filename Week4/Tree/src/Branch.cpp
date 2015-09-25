//
//  Branch.cpp
//  Branches
//
//  Created by Conor Russomanno on 9/17/15.
//
//

#include "Branch.h"

//--------------------------------------------------------------
void Branch::setup(float _xPos,
                   float _yPos,
                   float _width,
                   float _length,
                   float _splitPercentage,
                   float _maxSplitAngle,
                   int _maxSubdivisions,
                   int _maxSegments,
                   int _segmentsSinceStart,
                   float _angle,
                   float _curvature,
                   ofColor _color,
                   int _season,
                   int numberOfBobs){
    
    //===========================================
    // set incoming values based on what was passed in from previous instance of branch
    //===========================================
    
    xPos = _xPos;
    yPos = _yPos;
    width = _width;
    length = _length;
    splitPercentage = _splitPercentage;
    maxSplitAngle = _maxSplitAngle;
    maxSubdivsions = _maxSubdivisions;
    maxSegments = _maxSegments;
    segmentsSinceStart = _segmentsSinceStart;
    angle = _angle;
    curvature = _curvature;
    color = _color;
    season = _season;
    
    //===========================================
    //does the branch split??
    //===========================================
    if(ofRandom(0, 1) > splitPercentage && segmentsSinceStart != maxSegments){ //if random number between 0-1 is greater than split %, then split ... and never split on last branch
        split = true;
    } else{
        split = false;
    }
    
    //===========================================
    // create some leaves!!!
    //===========================================
    
    numLeaves = (int)ofRandom(0,4);
    if(segmentsSinceStart == maxSegments){ // make sure there are leaves at the end of the final branch
        numLeaves = (int)ofRandom(3,5);
    }
    if(segmentsSinceStart == 0){ // no leaves at the end of the first branch (aka the Trunk!)
        numLeaves = 0;
    }
    
    if(season != 2){
        for(int i = 0; i < numLeaves; i++){
            Leaf tempLeaf;
            tempLeaf.setup(angle, season);
            leaves.push_back(tempLeaf);
        }
    }
    
    //===========================================
    // SOME FEEDBACK
    //===========================================
    
//    cout << "New Branch" << endl;
//    cout << "Segment Count = ";
//    cout << segmentsSinceStart << endl;
    
    //===========================================
    //draw current branch instance
    //===========================================
    
    ofSetColor(color);
    ofSetLineWidth((int)width);
    ofLine(xPos, yPos, xPos + length*cos(angle), yPos + length*sin(angle)); //draw the branch segnment
    
    //  ATTEMPT TO USE RECTANGLES INSTEAD!!!
    //    ofPushMatrix();
    //        ofTranslate(xPos + length*cos(angle), yPos + length*sin(angle));
    //        ofRotateZ(angle * (180/PI));
    //        ofRect(0, 0 - length/2, length, width);
    //    ofPopMatrix();
    
    //===========================================
    //draw leaves on current branch
    //===========================================
    
    if(_season != 2){
        for(int i = 0; i < numLeaves; i++){
            leaves[i].draw(xPos + length*cos(angle), yPos + length*sin(angle)); //drawing leaves at the end of this branch...based on length and angle
        }
    }

    //===========================================
    //update variables to pass to next (sub) branch
    //===========================================
    
    xPos += length*cos(angle);
    yPos += length*sin(angle);
    width = width*(ofRandom(0.5,0.8));
    length = length*(ofRandom(0.7, 0.9));
    angle += curvature;
    curvature += ofRandom(0, (float)(2*PI)/360.0);
    
    //========================================
    segmentsSinceStart += 1; // DO THIS OR THE RECURSION WILL NEVER STOP!!!
    //========================================
    
    //===========================================
    //RECURSION!
    //===========================================
    
    if (segmentsSinceStart <= maxSegments) {
        if(!split){ //if the branch does not split... just create one more branch to keep going (in roughly the same direction)
            Branch subBranch;
            subBranch.setup(xPos, yPos, width, length, splitPercentage, maxSplitAngle, maxSubdivsions, maxSegments, segmentsSinceStart, angle, curvature, color, season, 5);
        } else { //if the branch does split!! create two sub-branches
            cout << "split" << endl; //some feedback
            Branch subBranch1;
            float angle1 = angle + ofRandom(0, maxSplitAngle);
            Branch subBranch2;
            float angle2 = angle - ofRandom(0, maxSplitAngle);
            
            subBranch1.setup(xPos, yPos, width, length, splitPercentage, maxSplitAngle, maxSubdivsions, maxSegments, segmentsSinceStart, angle1, curvature, color, season, 5);
            
            subBranch2.setup(xPos, yPos, width, length, splitPercentage, maxSplitAngle, maxSubdivsions, maxSegments, segmentsSinceStart, angle2, curvature, color, season, 5);
        }
    }  
}

//--------------------------------------------------------------
void Branch::update(){
    
}

//--------------------------------------------------------------
void Branch::draw(){
    
}