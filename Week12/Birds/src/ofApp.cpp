#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //number of birds initiation
    numBirds = 100;
    
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
        ofPoint tempAcc;//create temporary acceleration, and 3 sub accelerations that will soon be calculated and added to our birds vel
        ofPoint a1 = accTowardsCenterOfMass(i);
        ofPoint a2 = accAwayFromNearbyBirds(i);
        ofPoint a3 = accInDirectionOfNearbyBirdMovement(i);
        //A1 = the bird wanting to move towards the middle of all other birds
        //A2 = the bird wanting to move away from fellow birds that are too close
        //A3 = the bird wanting to move the same speed as nearby friends
        tempAcc = a1 + a2 + a3; //A = A1 + A2 + A3 ... find my total influence of sub-intentions
        myBirds[i].acc = tempAcc; //myBirds.acc = A
    }
    
    for(int i = 0; i < myBirds.size(); i++){
        myBirds[i].update();
    } //tempBird is no more
    
}

//--------------------------------------------------------------
void ofApp::draw(){
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
    
    cout << "megaPosition = ";
    cout << megaPosition << endl;
    
    myValue = megaPosition - myBirds[birdNumber].pos;//myValue = the difference between current birds position and megaPosition
    myValue = myValue.normalize();
    

    
    return myValue;
}
ofPoint ofApp::accAwayFromNearbyBirds(int birdNumber){
    ofPoint myValue;
    
    return ofPoint(0,0,0);
}
ofPoint ofApp::accInDirectionOfNearbyBirdMovement(int birdNumber){
    ofPoint myValue;
    
    return ofPoint(0,0,0);
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
