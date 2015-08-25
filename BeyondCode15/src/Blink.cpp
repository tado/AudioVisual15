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
    fade = 0;
    fadeSpeed = 0.005;
    fadeIn = true;
    lived = true;
}

void Blink::draw(){
    if (fadeIn) {
        fade += fadeSpeed;
        if (fade > 1.0) {
            fade = 1.0;
        }
    } else {
        fade -= fadeSpeed * 2.0;
        if (fade < 0.0) {
            lived = false;
            synth->free();
        }
    }
    
    float br = abs(sin((ofGetElapsedTimef() - startTime) * freq) * 255) * fade;
    synth.get()->set("amp", br / 255.0 * 0.5);
    ofSetColor(color.r, color.g, color.b, br);
    ofSetRectMode(OF_RECTMODE_CORNER);
    if ((ofGetFrameNum() - startFrame) % 4 == 0) {
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
}