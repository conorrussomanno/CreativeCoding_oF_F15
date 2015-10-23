#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(0,0,0);
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    mode = 0;
	
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update

    for(int i = 0; i < webs.size(); i++){
        webs[i].update();
    }
    
    if(stretchWeb==true){
        webs[0].stretchWeb(mouseX, mouseY);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofSetColor(255);
    for(int i = 0; i < webs.size(); i++){
        webs[i].draw();
    }

    ofSetColor(0,130,130, 200);
	ofRect(10,10,275,70);
	ofSetColor(255,255,255);
	ofDrawBitmapString("space to clear\ntoggle mode 'm'", 30, 30);
	
	
	ofSetColor(255,255,130);
	switch (mode){
		case 0: ofDrawBitmapString("drawing mode: place web", 30, 60);
			break;
		case 1: ofDrawBitmapString("drawing mode: mess with web!", 30, 60);
			break;
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
			
		case ' ':

            for(int i = 0; i<webs.size(); i++){
                webs.erase(webs.begin());
            }

			break;
            
        case 'm':
            if(mode<1){
                mode++;
            }
            else{
                mode=0;
            }
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(mode==0){
        web myWeb;
        myWeb.setInitialCondition(x, y);
        webs.push_back(myWeb);
    }
    if(mode==1){
        stretchWeb=true;
        cout << "stretchWeb = ";
        cout << stretchWeb << endl;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
//	particles[0].bFixed = false;
    stretchWeb=false;
    cout << "stretchWeb = ";
    cout << stretchWeb << endl;
}

