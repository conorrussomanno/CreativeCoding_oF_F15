#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);

    //create the particles
    num = 50;

    for(int i =0; i < num; i++){
        
        Particle p;
        MyParticles.push_back(p);
        MyParticles[i].init();
   
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i =0; i < num; i++){
        MyParticles[i].update(MyParticles);
        MyParticles[i].bounding();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
	ofSetColor(255);
    
    //note that easy cam gives you the ability to move the "camera" w/ mouse
    ofPushMatrix();
    
    cam.begin();
    light.enable();
    ofEnableLighting();
    glEnable(GL_DEPTH_TEST);
    
    //drawing my particles
    for(int i = 0; i < num; i++){
        MyParticles[i].draw();
    }
    
    glDisable(GL_DEPTH_TEST);
    ofDisableLighting();
    light.disable();
    cam.end();
    
    ofPopMatrix();
    
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
