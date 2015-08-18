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
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->update();
        while (perlins[0]->lived == false) {
            perlins.pop_front();
        }
    }
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
    post->begin(cam);
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->draw();
    }
    post->end();
    
    ofSetColor(255, 127);
    ofLine(0, mouseY, ofGetWidth(), mouseY);
    ofLine(mouseX, 0, mouseX, ofGetHeight());
}

void ofApp::exit(){
    fx->free();
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i]->exit();
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
    switch (mode) {
        case 0:
            int nth = int(ofMap(y, 0, ofGetHeight(), 12, 0));
            int cutoff = ofMap(abs(ofGetWidth() - x), 0, ofGetWidth() / 2.0, 20, 500);
            PerlinPlane *p = new PerlinPlane(perlins.size(), nth, cutoff);
            perlins.push_back(p);
            if (perlins.size() > 5) {
                perlins[0]->synth->free();
                perlins[0]->fadeIn = false;
            }
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
