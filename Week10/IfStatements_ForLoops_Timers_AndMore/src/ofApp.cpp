#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    xMargin = 100;
    yMargin = 100;
    numColumns = 10;
    numRows = 10;
    timeOfLastImportantMomemt = 0;
    haveIGrabbedAThing = false; //make sure to defaul this to false
    
    for(int i = 0; i < numColumns; i++){
        for(int j = 0; j < numRows; j++){
            Thing tempThing;
            float xLocation = xMargin + i*((ofGetWidth()-(xMargin*2))/(numColumns-1)); //find x locations based on numColumns
            float yLocation = yMargin + j*((ofGetHeight()-(yMargin*2))/(numRows-1));
            tempThing.setup(xLocation, yLocation);
            myThings.push_back(tempThing);
        }
    }
    cout << "myThings[] has [";
    cout << myThings.size();
    cout << "] things!" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //a timer!!! these are very useful.
    if(ofGetElapsedTimeMillis() - timeOfLastImportantMomemt > 3000){ //if system as logged 3 more seconds since last important moment
//        cout << "Important Moment!" << endl;
        for(int i = 0; i < myThings.size(); i++){ //loop through all of my things, and set there color to a new color
            cout << i;
            cout << ", ";
            cout << numRows*numColumns << endl;
            myThings[i].myColor = myThings[i].returnNewColor(i, numColumns*numRows); //have each thing pick a new color
        }
        timeOfLastImportantMomemt = ofGetElapsedTimeMillis(); //
    }
    
    if(haveIGrabbedAThing){
        myThings[thingGrabbed].pos.x = mouseX;
        myThings[thingGrabbed].pos.y = mouseY;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < myThings.size(); i++){
        myThings[i].draw();
    }

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
    if(!haveIGrabbedAThing){
        for(int i = 0; i < myThings.size(); i++){
            int minX = (myThings[i].pos.x - myThings[i].diameter/2);
            int maxX = (myThings[i].pos.x + myThings[i].diameter/2);
            int minY = (myThings[i].pos.y - myThings[i].diameter/2);
            int maxY = (myThings[i].pos.y + myThings[i].diameter/2);
            
            //if my mouse is on a thing when I click it
            if (mouseX >= minX && mouseX <= maxX && mouseY >= minY && mouseY <= maxY) {
                //I've grabbed a thing!
                haveIGrabbedAThing = true;
                thingGrabbed = i;
                cout << "I grabbed thing [";
                cout << thingGrabbed;
                cout << "]";
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //when you release your mouse, set haveIgrabbed a thing back to false, so that you don't keep moving the thing
    haveIGrabbedAThing = false;
    cout << "thing [";
    cout << thingGrabbed;
    cout << "] released!" << endl;
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
