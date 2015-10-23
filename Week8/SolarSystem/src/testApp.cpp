#include "testApp.h"

/*
 Modes:
	0 - orbit (planets in motion)
	1 - add (goes directly to mode 2 after adding new planet)
	2 - edit (leads to possibility to select modes 4-8)
	3 - delete
	4 - location
	5 - size
	6 - speed/direction
	7 - mass
	8 - color
	9 - select planet to edit
 */

float test = 0.0;
int planetToEdit = 0;
int planetToDelete = 0;

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetFrameRate(80);
	ofSetCircleResolution(80);// MAKES CIRCLES SMOOOOOTH!

	//default mode to orbit
	mode = 0;
    
	//clickmode used to display different images while mouse is pressed
	clickMode = 0;
	
	//load images
	imageOrbit.loadImage("imageOrbit.png");
	imageAdd.loadImage("imageAdd.png");
	imageEdit.loadImage("imageEdit.png");
	imageDelete.loadImage("imageDelete.png");
	densitySlider.loadImage("slider.png");
	colorSlider.loadImage("slider.png");
	sliderBars.loadImage("sliderBars.png");
	imageEditClicked.loadImage("imageEditClicked.png");
	imageSelectPlanet.loadImage("imageSelectPlanet.png");
	imageDeleteClicked.loadImage("imageDeleteClicked.png");
	positionCursor.loadImage("positionCursor25x25.png");
	
	//AUDIO STUFF ------------
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	ofSetVerticalSync(true);
	soundStream.listDevices();
	
	int bufferSize = 256;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
	
	audioIndicator = 0;
	
	//---------------------

}

//--------------------------------------------------------------
void testApp::update(){
	
	//AUDIO STUFF-------------
	
	//lets scale the vol up to a 0-1 range
	if (audioIndicator==1) {
		scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
	}
    
	else {
		scaledVol = .01;
	}

	
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
	
	//-------------------
	
	
	//updates the opacity of each planet
	for(int i=0; i<planets.size(); i++){
		planets[i].opacity = planets[i].density/100.0*255;
	}
	
	//UPDATE criteria for system while in orbit
	if(mode==0){
		
		//PHYSICS!!!
		//calc ForceMain for each planet (interaction between all other planets)
		for(int i=0; i<planets.size(); i++){
			for(int j=0; j<planets.size(); j++){
				if (i!=j) {
					forceMain[i][j] = (scaledVol*100.0) * gConstant*(planets[i].density*(4/3)*PI*pow((planets[i].radius), 3))*(planets[j].density*(4/3)*PI*pow((planets[j].radius), 3))/(ofDistSquared(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y));
				}
			    else{
					forceMain[i][j] = 0;
				}
			}
		}
		
		//convert to forceX and forceY
		for (int i = 0; i < planets.size(); i++) { //main force on each ball (direction from one to the other)
			for (int j = 0; j < planets.size(); j++) {
				if (planets[i].position.x>planets[j].position.x) {
					forceX[i][j] = ((planets[j].position.x-planets[i].position.x)/ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y))*forceMain[i][j];
				}
				if (planets[i].position.y>planets[j].position.y) {        
					forceY[i][j] = ((planets[j].position.y-planets[i].position.y)/ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y))*forceMain[i][j];
				}
				if (planets[i].position.x<planets[j].position.x) {
					forceX[i][j] = ((planets[j].position.x-planets[i].position.x)/ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y))*forceMain[i][j];
				}
				if (planets[i].position.y<planets[j].position.y) {
					forceY[i][j] = ((planets[j].position.y-planets[i].position.y)/ofDist(planets[i].position.x, planets[i].position.y, planets[j].position.x, planets[j].position.y))*forceMain[i][j];
				}
			}
		}
		//sum x and y total force and store for each planet
		for (int i = 0; i < planets.size(); i++) { //main force on each ball (direction from one to the other)
			for (int j = 0; j < planets.size(); j++) {
				if (i!=j) {
					planets[i].totalForce.x += forceX[i][j];
					planets[i].totalForce.y += forceY[i][j];
					cout << "planet0.v.x: " << planets[0].velocity.x << endl;
					cout << "planet0.v.y: " << planets[0].velocity.y << endl;
					cout << "forceMain[0][1]: " << forceMain[0][1] << endl;
					cout << "forceX[0][1]: " << forceX[0][1] <<endl;
					cout << "planets[0].totalX: " << planets[0].totalForce.x << endl;
					cout << "planets[0].totalY: " << planets[0].totalForce.y << endl;
					cout << "	SAME	" << endl;
				}
			}
		}
		
		//update each planet
		for(int i=0; i<planets.size(); i++){
			planets[i].update();
		}
	}
	
	cout << "clickMode: " << clickMode << endl;
	cout << "mode: " << mode << endl;
	cout << mouseX << endl;
	cout << mouseY << endl;
	cout << "planets.size: " << planets.size() << endl;
	cout << test << endl;
	cout << "planetToEdit: " << planetToEdit << endl;
	if (planets.size()>0) {
		cout << "planet.density: " << planets[planetToEdit].density << endl;
		cout << "planet.hue: " << planets[planetToEdit].hue << endl;
		cout << "planet.saturation: " << planets[planetToEdit].saturation << endl;
		cout << "planet.opacity: " << planets[planetToEdit].opacity << endl;
		cout << "planet0.v.x: ' " << planets[0].velocity.x << endl;
		cout << "planet0.v.y: ' " << planets[0].velocity.y << endl;
		cout << "forceMain[0][1]: ' " << forceMain[0][1] << endl;
		cout << "forceX[0][1]: ' " << forceX[0][1] <<endl;
		cout << "planets[0].totalX: ' " << planets[0].totalForce.x << endl;
	}
	cout << "scaledVol: " << scaledVol*100.0 << endl;

	
	cout << " " << endl;
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//add appropriate background image
	if(mode==0){
		imageOrbit.draw(0,0);
	}
	if(mode==1 || clickMode==1){
		imageAdd.draw(0,0);
		if(clickMode==0){
			ofPushStyle();
			ofSetColor(255,255,255,50);
			ofCircle(mouseX, mouseY, 50);
			ofPopStyle();
		}
	}
	if(mode==2 || clickMode==2){
		imageEdit.draw(0,0);
		if(mouseX<510 && mouseX>384 && mouseY>16 && mouseY<80){
			imageEditClicked.draw(0,0);
		}
	}
	if(mode==3 || clickMode==3){
		imageDelete.draw(0,0);
		if(mouseX<510 && mouseX>384 && mouseY>16 && mouseY<80){
			imageDeleteClicked.draw(0,0);
		}
	}
	
	if(mode==4 || mode==5 || mode==6 || mode==7 || mode==8){
		imageEdit.draw(0,0);
	}
	
	//edit interface
	if(mode==2 || mode==4 || mode==5 || mode==6 || mode==7 || mode==8){
	//Draw Edit Interface features: //color bar, position cross-hair, radius indicator, density slider, velocity arrow
		
		//sliderBars.draw(0,0);
		densitySlider.draw(795-40, ofMap(planets[planetToEdit].density, 0, 100, 790, 128)-40);
		colorSlider.draw(855-40, ofMap(planets[planetToEdit].hue, 0, 359, 790, 128)-40);
	}
	
	if (mode==9) {
		imageSelectPlanet.draw(0.0);
	}
	
	for(int i=0; i<planets.size(); i++){ //draw
		planets[i].draw();
	}
	
	if(mode==2 || mode==4 || mode==5 || mode==6 || mode==7 || mode==8){
		//Draw Edit Interface features: //color bar, position cross-hair, radius indicator, density slider, velocity arrow
		
		ofPushStyle();
		ofSetColor(255,0, 0, 150);
		ofLine(planets[planetToEdit].position.x, planets[planetToEdit].position.y, planets[planetToEdit].position.x+planets[planetToEdit].velocity.x, planets[planetToEdit].position.y+planets[planetToEdit].velocity.y);
		ofPopStyle();
		positionCursor.draw(planets[planetToEdit].position.x-13, planets[planetToEdit].position.y-12);
	}
	
	//Draw Audio Indicator
	if (audioIndicator == 1) {
		ofPushStyle();
		ofSetColor(0, 255, 0);
		ofCircle(ofGetWidth()-25, ofGetHeight()-25, 5);
		ofPopStyle();
	}
	else {
		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofCircle(ofGetWidth()-25, ofGetHeight()-25, 5);
		ofPopStyle();
	}

}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	
	
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
		
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if( key == 's' ){
		soundStream.start();
		audioIndicator = 1;
		
	}
	
	if( key == 'e' ){
		soundStream.stop();
		audioIndicator = 0;
	}
	
	if( key == 'b' ){
		soundStream.start();
		audioIndicator = 2;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	if (mode==8) {
		if(y<=790 && y>=128){
			planets[planetToEdit].hue=ofMap(y, 128, 790, 359, 0);
		}
	}
	if (mode==7) {
		if(y<=790 && y>=128){
			planets[planetToEdit].density=ofMap(y, 128, 790, 100, 0);
		}
	}
	if (mode==6) {
		planets[planetToEdit].velocity.x = (x - planets[planetToEdit].position.x);
		planets[planetToEdit].velocity.y = (y - planets[planetToEdit].position.y);
	}
	
	if (mode==5) { //i should be planetToEdit?
		planets[planetToEdit].radius = ofDist(x, y, planets[planetToEdit].position.x, planets[planetToEdit].position.y);
	}
	if(mode==4){//same?
		planets[planetToEdit].position.x = x;
		planets[planetToEdit].position.y = y;
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	if (mode==2) {
		int i = planetToEdit;
		float dist = ofDist(x, y, planets[i].position.x, planets[i].position.y);
		test = dist;
//		double xVel = (planets[i].velocity.x)*(planets[i].velocity.x);
//	    double yVel = (planets[i].velocity.y)*(planets[i].velocity.y);
//		double speed = pow((xVel+yVel),0.5); //a^2+b^2=c^2
//		float direction;
		float distX = planets[i].velocity.x + planets[i].position.x;
		float distY = planets[i].velocity.y + planets[i].position.y;
		
	
		//mode 7 - mass... pull density % from slider on right
		if (x<=810 && x>=782 && y<=790 && y>=128) {
			planets[planetToEdit].density=ofMap(y, 128, 790, 100, 0);
			mode=7;
		}
	
		//mode 8 - color... pull colorvalue from table on right
		if (x<=870 && x>=842 && y<=790 && y>=128) {
			planets[planetToEdit].hue=ofMap(y, 128, 790, 359, 0);
			mode=8;
		}
	
		//mode 4 - position
		if(dist<=8){
			mode=4;
		}
		
		//mode 5 - radius
		if (dist-planets[i].radius<=10 && dist-planets[i].radius>=-10){
			mode=5;
		}
		
		//mode 6 - speed/direction		
		if(x-distX<8 && x-distX>-8 && y-distY<8 && y-distY > -8){
			mode=6;
		}
	}
	
	//to show mouse interaction when pressed (doesn't change setting until released)
	if(mode==0){ //while in orbit mode
		if(x>10 && x<50 && y>50 && y<90) { //add button
			clickMode=1;
		}
		if(x>60 && x<100 && y>50 && y<90) { //edit button
			clickMode=2;
		}
		if(x>110 && x<150 && y>50 && y<90) { //delete button
			clickMode=3;
		}
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	//select orbit button while in edit
	if(mode==2 && x<510 && x>384 && y>16 && y<80){
		mode=0;
    }
	
	//select orbit button while in delete
	if(mode==3 && x<510 && x>384 && y>16 && y<80){
		mode=0;
    }
	
	if(mode==9){ //runs through planets after releasing mouse to find which one should be edited
		for(int i = 0; i<planets.size(); i++){
			double xWR = (x-planets[i].position.x)*(x-planets[i].position.x);
			double yWR = (y-planets[i].position.y)*(y-planets[i].position.y);
			double withinRad = pow((xWR+yWR),0.5);
			float rad = planets[i].radius;
			if (withinRad<rad && x<planets[i].position.x+rad && x>planets[i].position.x-rad && y<planets[i].position.y+rad && y>planets[i].position.y-rad) {
				planetToEdit = i;
			}
		}
		mode=2;
	}
	
	if (mode==8) {
		mode=2;
	}
	
	if (mode==7) {
		mode=2;
	}
	
	if(mode==6){
		mode=2;
	}
	
	if (mode==5) {
		mode=2;
	}
	
	if(mode==4){
		mode=2;
	}
	
	if (mode==3) {
		for(int i = 0; i<planets.size(); i++){
			double xWR = (x-planets[i].position.x)*(x-planets[i].position.x);
			double yWR = (y-planets[i].position.y)*(y-planets[i].position.y);
			double withinRad = pow((xWR+yWR),0.5);
			float rad = planets[i].radius;
			if (withinRad<rad && x<planets[i].position.x+rad && x>planets[i].position.x-rad && y<planets[i].position.y+rad && y>planets[i].position.y-rad) {
				planetToDelete = i;
			}
		}
		planets.erase(planets.begin()+planetToDelete);
		mode=0;
	}
	
	if (mode==1) {
		Planet p;
		p.setup(x,y);
		planets.push_back(p);
		planetToEdit = planets.size()-1;
		mode=2;
	}
	
	if(mode==0){ //while in orbit mode
		if (x>10 && x < 50 && y>50 && y<90) { //add button
//			imageAdd.draw(0,0);
			mode=1;
			clickMode=0;
		}
		if (x>60 && x<100 && y>50 && y<90 && planets.size()>0) { //edit button
//			imageEdit.draw(0,0);
			mode=9;  //sends to planetToEdit selector
			clickMode=0;
		}
		if (x>110 && x<150 && y>50 && y<90 && planets.size()>0) {
//			imageDelete.draw(0,0);
			mode=3;
			clickMode=0;
		}
		else {
			clickMode=0;
		}

	}
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}