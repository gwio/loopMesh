#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(false);

	ofEnableAntiAliasing();
	ofEnableDepthTest();
	//ofEnableLighting();
	light.setPosition(0,200,0);
	//light.enable();
	light.setSpecularColor(ofColor(255,255,255));
	material.setShininess(0.5);
	material.setAmbientColor(ofColor(122,0,0));

	glShadeModel(GL_FLAT);
	schleifen.clear();


	int resolution = 180;
	for (int i = 0; i < 2; i++) {
	

			//closed, flip, polypoints, width, angle, addnoise, radius, position, color 
			schleifen.push_back( Schleife(true,false,resolution, 201, TWO_PI/resolution, false, 600*(i+1) ,ofVec3f(0,0,0), ofRandom(255) ));
		

		
	}
	


}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < schleifen.size(); i++) {
		schleifen[i].update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor(255));
	cam.begin();
	//ofEnableLighting();
	material.begin();
	//ofDrawAxis(100);
	ofSetColor(ofColor(0));
	

	for (int i = 0; i < schleifen.size(); i++) {
		schleifen[i].draw();
	}



	cam.end();

	ofDrawBitmapString( ofToString(ofGetFrameRate(),2), ofGetWidth()-60, 50);
}
//--------------------------------------------------------------



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 's') {
		ofSaveScreen("frame"+ofGetTimestampString()+".png");
	}

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
