#pragma once

#include "ofMain.h"
#include "PerlinPlane.h"
#include "ofxPostProcessing.h"
#include "ofxSuperCollider.h"
#include "SawSynth.h"
#include "Blink.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void drawPerlin();
    void drawSaw();
    void drawBlinks();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofEasyCam cam;
    ofxPostProcessing *post;
    BloomPass::Ptr bloom;
    
    static const int PERLIN_NUM = 5;
    deque <shared_ptr<PerlinPlane> > perlins;
    shared_ptr<ofxSCSynth> fx;
    shared_ptr<ofxSCSynth> rhythm;
    shared_ptr<ofxSCSynth> fxSaw;
    shared_ptr<ofxSCSynth> fxBlink;
    shared_ptr<ofxSCSynth> saw;
    shared_ptr<ofxSCSynth> sin;
    deque <shared_ptr<SawSynth> > sawsynths;
    int sawNum;
    deque <shared_ptr<Blink> > blinks;
    bool playRhythm;
    int mode;
};
