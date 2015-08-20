#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    
    mode = 0;
    playRhythm = false;
    
    post = new ofxPostProcessing();
    post->init(ofGetWidth(), ofGetHeight());
    bloom = post->createPass<BloomPass>();
    bloom->setEnabled(true);
    
    fx = shared_ptr<ofxSCSynth>(new ofxSCSynth("fx_allpass"));
    fx.get()->create();
    fxSaw = shared_ptr<ofxSCSynth>(new ofxSCSynth("fx_saw"));
    fxSaw.get()->create();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    switch (mode) {
        case 0:
            drawPerlin();
            break;
            
        default:
            break;
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0);
    ofCircle(mouseX, mouseY, 10);
    ofSetColor(255);
    ofCircle(mouseX, mouseY, 5);
}

void ofApp::drawPerlin(){
    //update
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i].get()->update();
        
    }
    if (perlins.size() > PERLIN_NUM) {
        perlins[0].get()->synth->free();
        perlins[0].get()->fadeIn = false;
    }
    if (perlins.size() > 1) {
        while (perlins[0].get()->lived == false) {
            perlins.pop_front();
        }
    }
    
    //draw
    post->begin(cam);
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i].get()->draw();
    }
    post->end();
}

void ofApp::exit(){
    fx.get()->free();
    fxSaw.get()->free();
    if (rhythm != NULL) {
        rhythm->free();
    }
    for (int i = 0; i < perlins.size(); i++) {
        perlins[i].get()->exit();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'z' && playRhythm == false) {
        rhythm = shared_ptr<ofxSCSynth>(new ofxSCSynth("pulse_rhythm"));
        rhythm.get()->create();
        playRhythm = true;
    }
    if (key == '/' && playRhythm == true) {
        rhythm.get()->free();
        playRhythm = false;
    }
    if (key == 'x') {
        saw = shared_ptr<ofxSCSynth>(new ofxSCSynth("fade_saw"));
        saw.get()->create();
    }
    if (key == 'c' || key == 'v') {
        sin = shared_ptr<ofxSCSynth>(new ofxSCSynth("simple_sine"));
        sin.get()->create();
    }
    if (key == 'd') {
        perlins[0].get()->synth->free();
        perlins[0].get()->fadeIn = false;
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
            shared_ptr<PerlinPlane> p = shared_ptr<PerlinPlane>(new PerlinPlane(perlins.size(), nth, cutoff, gain));
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
