#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    post = new ofxPostProcessing();
    post->init(ofGetWidth(), ofGetHeight());
    bloom = post->createPass<BloomPass>();
    bloom->setEnabled(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //cam.begin();
    post->begin(cam);
    //ofEnableDepthTest();
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->draw();
    }
    //ofDisableDepthTest();
    //cam.end();
    post->end();
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
    PerlinPlane *p = new PerlinPlane();
    perlins.push_back(p);
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
