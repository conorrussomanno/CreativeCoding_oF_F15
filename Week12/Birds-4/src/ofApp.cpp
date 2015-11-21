#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Systemwide Settings
    ofEnableAlphaBlending();
    ofSetVerticalSync(TRUE);
    ofSetBackgroundAuto(FALSE);
    ofSetFrameRate(60);
    ofSetFullscreen(true);
    ofSetBackgroundColor(0, 0, 0);
    ofSetCircleResolution(128);
    
    isMousePressed = false;
    
    //number of birds initiation
    numBirds = 300;
    framesBetweenRecordedPosition = 3;
    frameCounter = 0;
    
    //create all my birds
    for(int i = 0; i < numBirds; i++){
        Bird tempBird; //create a temp bird
        tempBird.setup(); //give it life
        myBirds.push_back(tempBird); //copy it and stick it in the vectory
    } //tempBird is no more
}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i = 0; i < myBirds.size(); i++){//loop through every bird
        
        
        //----------------------------------------------------------------
        // create temporary (ie this frame) acceleration (A), and 3 sub accelerations (A1, A2, A3) that will soon be calculated and added to our birds vel
        //----------------------------------------------------------------
        aFactor = 0.01; // aF - a multiplier for scaling the "temp acceleration" (A)
        A = ofPoint(0,0,0);  // A
        A1 = accTowardsCenterOfMass(i); // A1 - the bird wanting to move towards the middle of all other birds
        A2 = accAwayFromNearbyBirds(i); // A2 - the bird wanting to move away from fellow birds that are too close
        A3 = accInDirectionOfNearbyBirdMovement(i); // A3 - the bird wanting to move the same speed as nearby friends
        A4 = accTowardsCursor(i);
        
        //----------------------------------------------------------------
        // Give this bird some individuality
        //----------------------------------------------------------------
        herdDependency = myBirds[i].herdDependency; // lW - find this bird's desire to explore alone
        proximityDiscomfort = myBirds[i].proximityDiscomfort; // pD - find this bird's apathy to being in close quarters with other birds
        flowConsideration = myBirds[i].flowConsideration; // fC - find this bird's consideration for other birds' desire to get home from work
        cursorCuriosity;
        
        if(isMousePressed){
            cursorCuriosity = myBirds[i].cursorCuriosity; // cC - find the bird's desire to move towards your cursor
        } else {
            cursorCuriosity = 0;
        }
        
        //----------------------------------------------------------------
        // A = (aF) * ( (lW)*A1 + (pD)*A2 + (fC)*A3 (cC)*A4 ) ... find my total influence of sub-intentions
        //----------------------------------------------------------------
        A = (aFactor) * ((herdDependency)*A1 + (proximityDiscomfort)*A2 + (flowConsideration)*A3 + (cursorCuriosity)*A4);
        myBirds[i].acc = A; //myBirds.acc = A
    }
    
    if (frameCounter >= framesBetweenRecordedPosition) { //if it's been long enough to add the bird's position to its memory
        for(int i = 0; i < myBirds.size(); i++){
            myBirds[i].update(true); //add that position
        }
        frameCounter = 0;
    } else { //if it hasn't been long enough to store a memory
        for(int i = 0; i < myBirds.size(); i++){
            myBirds[i].update(false); //add that position
        }
    }
    frameCounter++; //update the frame counter that's being tracked to store previous positions
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //** Create Fading Effect
    ofPushStyle();
        ofSetColor(0,0,0,255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    //**
    
    for(int i = 0; i < myBirds.size(); i++){
        myBirds[i].draw();
    } //tempBird is no more
    
    if(isMousePressed){ //cursor glow sphere when pressed
        ofPushStyle();
            float sinFadeNormalized = ofMap(sin(0.005*ofGetElapsedTimeMillis()), -1, 1, 0, 1);
            ofSetColor(255,114,0, 255*sinFadeNormalized);
            ofEllipse(mouseX, mouseY, 30*(1/(sinFadeNormalized+1)), 30*(1/(sinFadeNormalized+1)));
        ofPopStyle();
    } else {
        ofPushStyle();
            ofSetColor(255,0,0);
            ofEllipse(mouseX, mouseY, 5, 5);
        ofPopStyle();
    }

}

ofPoint ofApp::accTowardsCenterOfMass(int birdNumber){
    myValue;
    megaPosition = ofPoint(0,0,0);
    //find center of position of all other birds, not including ourself
    //create a normalized vector the is the difference between our position and the center position
    for(int i = 0; i < myBirds.size(); i++){
        if(i != birdNumber){
            megaPosition += myBirds[i].pos;
        }
    }
    megaPosition = megaPosition / (myBirds.size()-1); //add position of other bird to megapostion
    //divide megaposition by number of birds - 1
    
//    cout << "megaPosition = ";
//    cout << megaPosition << endl;
    
    myValue = megaPosition - myBirds[birdNumber].pos;//myValue = the difference between current birds position and megaPosition
    myValue = myValue.normalize();
    
    return myValue;
}


ofPoint ofApp::accAwayFromNearbyBirds(int birdNumber){
    runAway; //value that will be turned to
    numBirdsInfluencing = 0;
    
    for(int i = 0; i < myBirds.size(); i++){
        if(i != birdNumber){
            if((myBirds[i].pos - myBirds[birdNumber].pos).length() <=  myBirds[birdNumber].comfortDistance){
                runAway += myBirds[i].pos; //add the position of any bird that is too close
                numBirdsInfluencing++; //count upwards!
            }
        }
    }
    runAway /= float(numBirdsInfluencing); //finish the average by dividing by the number of birds that were considered
    runAway = runAway - myBirds[birdNumber].pos; //find the difference vector between the birds this bird is running away from and the this bird
    runAway *= -1; //turn around and run!!!
    runAway = runAway.normalize();
    
    return ofPoint(0,0,0);
//    return runAway;
}


ofPoint ofApp::accInDirectionOfNearbyBirdMovement(int birdNumber){
    avgVelOfNearbyBirds;
    numBirdsInfluencing = 0;
    
    for(int i = 0; i < myBirds.size(); i++){
        if(i != birdNumber){
            if((myBirds[i].pos - myBirds[birdNumber].pos).length() <=  myBirds[birdNumber].flowDistance){
                avgVelOfNearbyBirds += myBirds[i].vel; //add the position of any bird that is too close
                numBirdsInfluencing++; //count upwards!
            }
        }
    }
    avgVelOfNearbyBirds /= float(numBirdsInfluencing);
    avgVelOfNearbyBirds = avgVelOfNearbyBirds.normalize();
    
    return ofPoint (0,0,0);
//    return avgVelOfNearbyBirds;
}

ofPoint ofApp::accTowardsCursor(int birdNumber){
    myValue = ofPoint(0,0,0);
    myMousePosition = ofPoint(mouseX, mouseY, 0);
    myValue = myMousePosition - myBirds[birdNumber].pos;
    
//    float amplifier = 100/(myValue.length()); //add a distance sensor to the curiosity ... the closer the more interested
    float amplifier = 1.0;
    if(myValue.length() <= myBirds[birdNumber].cursorCuriosityDistance){
        amplifier = ofMap(myValue.length(), 0.0, myBirds[birdNumber].cursorCuriosityDistance, 10.0, 1.0);
    }
    
    myValue = amplifier*myValue.normalize();
    
    return myValue;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
