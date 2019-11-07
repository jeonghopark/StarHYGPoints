#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxGui.h"

//using namespace wng;


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
	
    ofxCsv csv;
    
    ofMesh starMesh;
    ofMesh starLineMesh;
    int countLine;
    
    ofEasyCam easyCam;
    
    void drawingCircle(int _degX);
    
    void drawingBaseCircle(int _degX);

    
    float rotY;
    
    float sinY;
    
    void information();
  
    ofxPanel gui;
    ofxIntSlider numCircle;
    ofxFloatSlider circleSizeRatio;
    ofxIntSlider innerCircleSize;
    ofxFloatSlider innerCircleAlpha;
    
    ofxIntSlider numBaseCircle;
    ofxFloatSlider circleBaseSizeRatio;
    ofxIntSlider innerBaseCircleSize;
    ofxFloatSlider innerBaseCircleAlpha;

    ofxIntSlider starAlpha;
    ofxIntSlider lineAlpha;

    bool guiOnOff;

    ofPoint posSize;

    float rotationY;
    
};
