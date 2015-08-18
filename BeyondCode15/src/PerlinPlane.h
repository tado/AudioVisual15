#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"

class PerlinPlane {
public:
    PerlinPlane(int num, int nth, int cutoff);
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    int num;
    int nth;
    int cutoff;
    
    bool lived;
    bool fadeIn;
    ofVboMesh mesh;
    ofTexture tex;
    float radius;
    
    //vector<ParticleVec3> currentParticle;
    vector<ofVec3f> sphereVertex;
    vector<ofVec3f> currentVertex;
    string name;
    
    float noiseScale;
    float shiftSpeed;
    float noiseStrength;
    float rotation;
    float rotSpeed;
    float fade;
    float fadeSpeed;
    ofColor color;
    
    ofxSCSynth *synth;
};