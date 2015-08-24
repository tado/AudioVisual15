//
//  Blink.cpp
//  BeyondCode15
//
//  Created by Atsushi Tadokoro on 8/24/15.
//
//

#include "Blink.h"

Blink::Blink(float _freq){
    freq = _freq;
    color = ofColor::fromHsb(ofRandom(255), 255, 255);
    startFrame = int(ofRandom(4));
    startTime = ofGetElapsedTimef();
    synth = shared_ptr<ofxSCSynth>(new ofxSCSynth("blink"));
    synth.get()->create();
}

void Blink::draw(){
    float br = sin((ofGetElapsedTimef() - startTime) * freq) * 127 + 127;
    ofSetColor(color.r, color.g, color.b, br);
    ofSetRectMode(OF_RECTMODE_CORNER);
    if ((ofGetFrameNum() - startFrame) % 4 == 0) {
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
}