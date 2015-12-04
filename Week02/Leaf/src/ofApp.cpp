#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numLeaves = ofRandom(10,20);
    for(int i = 0; i < numLeaves; i++){
        Leaf tempLeaf;
        tempLeaf.setup();
        leaves.push_back(tempLeaf);
    }
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableSmoothing(); //let's make it smoooooooth.
    ofEnableAlphaBlending(); //transparency
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < numLeaves; i++){
        leaves[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < numLeaves; i++){
        leaves[i].draw();
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    leaves.clear();
    setup();

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
