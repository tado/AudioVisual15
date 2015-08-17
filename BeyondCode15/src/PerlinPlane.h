#pragma once
#include "ofMain.h"

class PerlinPlane {
public:
    PerlinPlane();
    void update();
    void draw();
    
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
};