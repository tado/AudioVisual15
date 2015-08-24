#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"

class Blink {
public:
    Blink(float freq);
    void update();
    void draw();
    
    float freq;
    ofColor color;
    int startFrame;
    float startTime;
    shared_ptr<ofxSCSynth> synth;
};