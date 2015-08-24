#include "SawSynth.h"

SawSynth::SawSynth(int n){
    death = false;
    detune = ofRandom(-0.15, 0.15);
    nth = n;
    alpha = 1;
    alphaMax = 127;
    //startTime = ofGetElapsedTimef();
    
    synth = new ofxSCSynth("col_closesaw");
    synth->set("gate", 1);
    synth->set("amp", 0.75);
    synth->set("rq", 1.0);
    synth->set("n", nth);
    synth->set("detune", detune);
    synth->create();
    
    freq = 20.0 * powf(1.5, nth);
    height = float(ofGetHeight()) / freq * 20.0;
    
    scanPos = ofRandom(ofGetWidth());
    scanSpeed = powf(1.1, nth + 1) * 40.0;
    if (nth % 2 == 0) {
        direction = 1.0;
    } else {
        direction = -1.0;
    }
    
    col = ofColor::fromHsb(ofRandom(255), 255, 180);
    fade = 0;
    fadeSpeed = 0.005;
}

SawSynth::~SawSynth() {
    synth->free();
}

void SawSynth::update(){
    scanPos = scanPos + scanSpeed * direction;
    if (scanPos < 0) {
        scanPos = ofGetWidth();
    }
    if (scanPos > ofGetWidth()) {
        scanPos = 0;
    }
    
    if (fade < 0.5) {
        fade += fadeSpeed;
    }
}

void SawSynth::draw(){
    ofSetColor(col, fade * 255);
    ofRect(scanPos, 0, 400, ofGetHeight());
}

void SawSynth::clear(){
    
}