#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    mode = 0;
    
    post = new ofxPostProcessing();
    post->init(ofGetWidth(), ofGetHeight());
    bloom = post->createPass<BloomPass>();
    bloom->setEnabled(true);
    
    fx = new ofxSCSynth("fx_allpass");
    fx->create();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    switch (mode) {
        case 0:
            drawPerlin();
            break;
            
        default:
            break;
    }
}

void ofApp::drawPerlin(){
    //update
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->update();
        
    }
    if (perlins.size() > PERLIN_NUM) {
        perlins[0]->synth->free();
        perlins[0]->fadeIn = false;
    }
    if (perlins.size() > 1) {
        while (perlins[0]->lived == false) {
            perlins.pop_front();
        }
    }
    
    //draw
    post->begin(cam);
    //cam.begin();
    //ofEnableDepthTest();
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->draw();
    }
    //ofDisableDepthTest();
    post->end();
    //cam.end();
    
    ofSetColor(255, 127);
    ofLine(0, mouseY, ofGetWidth(), mouseY);
    ofLine(mouseX, 0, mouseX, ofGetHeight());
}

void ofApp::exit(){
    fx->free();
    rhythm->free();
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->exit();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'z') {
        rhythm = new ofxSCSynth("pulse_rhythm");
        rhythm->create();
    }
    if (key == 'd') {
        perlins[0]->synth->free();
        perlins[0]->fadeIn = false;
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
    switch (mode) {
        case 0:
            int nth = int(ofMap(y, 0, ofGetHeight(), 11, 0));
            int cutoff = 500;
            float gain = ofMap(abs(ofGetWidth()/2 - x), 0, ofGetWidth() / 2.0, 1.0, 3.9);
            PerlinPlane *p = new PerlinPlane(perlins.size(), nth, cutoff, gain);
            perlins.push_back(p);
            break;
    }
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
