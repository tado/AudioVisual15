#pragma once

#include "ofMain.h"
#include "PerlinPlane.h"
#include "ofxPostProcessing.h"
#include "ofxSuperCollider.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void drawPerlin();
    
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
    
    static const int PERLIN_NUM = 5;
    deque<PerlinPlane *> perlins;
    
    ofxPostProcessing *post;
    BloomPass::Ptr bloom;
    
    ofxSCSynth *fx;
    
    int mode;
};
