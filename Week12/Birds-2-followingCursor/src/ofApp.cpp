#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //Systemwide Settings
    ofEnableAlphaBlending();
    ofSetVerticalSync(TRUE);
    ofSetBackgroundAuto(FALSE);
    ofSetFrameRate(60);
    ofSetBackgroundColor(0, 0, 0);
    
    //number of birds initiation
    numBirds = 1000;
    
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
        float aFactor = 0.02; // aF - a multiplier for scaling the "temp acceleration" (A)
        ofPoint A;  // A
        ofPoint A1 = accTowardsCenterOfMass(i); // A1 - the bird wanting to move towards the middle of all other birds
        ofPoint A2 = accAwayFromNearbyBirds(i); // A2 - the bird wanting to move away from fellow birds that are too close
        ofPoint A3 = accInDirectionOfNearbyBirdMovement(i); // A3 - the bird wanting to move the same speed as nearby friends
        ofPoint A4 = accTowardsCursor(i);
        
        //----------------------------------------------------------------
        // Give this bird some individuality
        //----------------------------------------------------------------
        float loneWolfliness = 1.0; // lW - find this bird's desire to explore alone
        float proximityComfort = 1.0; // pC - find this bird's apathy to being in close quarters with other birds
        float flowConsideration = 1.0; // fC - find this bird's consideration for other birds' desire to get home from work
        float cursorCuriosity = 10.0; // cC - find the bird's desire to move towards your cursor
        
        //----------------------------------------------------------------
        // A = (aF) * ( (lW)*A1 + (pC)*A2 + (fC)*A3 (cC)*A4 ) ... find my total influence of sub-intentions
        //----------------------------------------------------------------
        A = (aFactor) * ((loneWolfliness)*A1 + (proximityComfort)*A2 + (flowConsideration)*A3 + (cursorCuriosity)*A4);
        myBirds[i].acc = A; //myBirds.acc = A
    }
    
    for(int i = 0; i < myBirds.size(); i++){
        myBirds[i].update();
    } //tempBird is no more
    
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
}

ofPoint ofApp::accTowardsCenterOfMass(int birdNumber){
    ofPoint myValue;
    ofPoint megaPosition = ofPoint(0,0,0);
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
    ofPoint myValue = ofPoint(0,0,0);
    
    return myValue;
}
ofPoint ofApp::accInDirectionOfNearbyBirdMovement(int birdNumber){
    ofPoint myValue = ofPoint(0,0,0);
    
    return myValue;
}

ofPoint ofApp::accTowardsCursor(int birdNumber){
    ofPoint myValue = ofPoint(0,0,0);
    ofPoint myMousePosition = ofPoint(mouseX, mouseY, 0);
    myValue = myMousePosition - myBirds[birdNumber].pos;
    myValue = myValue.normalize();
    
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
