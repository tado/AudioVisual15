//
//  PerlinPlane.cpp
//  BeyondCode15
//
//  Created by Atsushi Tadokoro on 8/17/15.
//
//

#include "PerlinPlane.h"

PerlinPlane::PerlinPlane(int _num, int _nth, int _cutoff, float _gain){
    num = _num;
    nth = _nth;
    cutoff = _cutoff;
    gain = _gain;
    
    lived = true;
    fadeIn = true;
    
    name = "PerlinPlane";
    int width = 1920;
    int height = 1080;
    unsigned char pixels[width * height];
    
    for (int i = 0; i < width * height; i += 18){
        pixels[i] = pixels[i+1] = pixels[i+2] = 255;
        if (i % 2 == 0) {
            pixels[i + 3] = 255;
        } else {
            pixels[i + 3] = 0;
        }
    }
    tex.loadData(pixels, width / 4.0, height / 4.0, GL_RGBA);
    
    mesh = ofSpherePrimitive(ofGetHeight()/1.4, 48).getMesh();
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        ofVec2f texCoord = mesh.getTexCoord(i);
        texCoord.x *= tex.getWidth();
        //texCoord.y  = (1.0 - texCoord.y) * tex.getHeight();
        texCoord.y  *= tex.getHeight();
        mesh.setTexCoord(i, texCoord);
        
        sphereVertex.push_back(ofVec3f(mesh.getVertices()[i].x, mesh.getVertices()[i].y, mesh.getVertices()[i].z));
        currentVertex.push_back(ofVec3f(mesh.getVertices()[i].x, mesh.getVertices()[i].y, mesh.getVertices()[i].z));
    }
    
    noiseScale = nth * 2.0 + 5.0;
    shiftSpeed = 0.5;
    noiseStrength = 100;
    rotSpeed = ofRandom(0.1, 0.3);
    rotation = ofRandom(180);
    fade = 0.0;
    fadeSpeed = 0.002;
    color.setHsb(ofMap(nth, 0, 11, 0, 255), 200, 255); 
    
    synth = new ofxSCSynth("moog");
    synth->set("nth", nth);
    synth->set("cutoff", cutoff);
    synth->set("gain", gain);
    synth->create();
}

void PerlinPlane::update(){
    float time = ofGetElapsedTimef();
    float noiseTime = time * shiftSpeed;
    
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        float noiseX = ofMap(currentVertex[i].x, 0, ofGetWidth(), 0, noiseScale);
        float noiseY = ofMap(currentVertex[i].y, 0, ofGetWidth(), 0, noiseScale);
        float noiseZ = ofMap(currentVertex[i].z, 0, ofGetWidth(), 0, noiseScale);
        float offset = ofNoise(noiseX + ofGetElapsedTimef() * shiftSpeed,
                               noiseY + ofGetElapsedTimef() * shiftSpeed,
                               noiseZ + ofGetElapsedTimef() * shiftSpeed
                               ) - 0.5;
        ofVec3f vec = currentVertex[i].normalize() * offset * noiseStrength;
        currentVertex[i] = sphereVertex[i] + vec;
        mesh.setVertex(i, currentVertex[i]);
    }
    
    rotation += rotSpeed;
    
    if (fadeIn) {
        lived = true;
        fade += fadeSpeed;
        if (fade > 1.0) {
            fade = 1.0;
        }
    } else {
        fade -= fadeSpeed * 4.0;
        if (fade < 0.0) {
            lived = false;
        }
    }
}

void PerlinPlane::draw(){
    if (lived) {
        tex.bind();
        ofPushMatrix();
        ofRotateX(rotation);
        ofRotateY(rotation * 1.3);
        ofRotateZ(rotation * 1.7);
        ofSetColor(color.r, color.g, color.b, fade * 170);
        mesh.draw();
        ofPopMatrix();
        tex.unbind();
    }
}

void PerlinPlane::exit(){
    synth->free();
}

void PerlinPlane::keyPressed(int key){
    
}

void PerlinPlane::keyReleased(int key){
    
}

void PerlinPlane::mouseMoved(int x, int y ){
    
}

void PerlinPlane::mouseDragged(int x, int y, int button){
    
}

void PerlinPlane::mousePressed(int x, int y, int button){
    
}

void PerlinPlane::mouseReleased(int x, int y, int button){
    
}
