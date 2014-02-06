#pragma once

#define GRAD_PI 180.000/PI

#include "ofMain.h"
#include "ofMath.h"

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
    float getAngle(float _x, float _y);
    
    vector <ofImage> frames;
    ofVideoGrabber grabber;
    
    vector <ofRectangle> dropZoneRects;
    vector <ofImage> images;
    vector <ofPoint> boxTrail;
    
    ofTrueTypeFont font;
    
    bool                    oneShot;
    bool                    pdfRendering;
    float                   angle;
    
    int     coneComplexity;
    int     scoopComplexity;
    short int scoopSkip;
    ofPoint screenMidpoint;
    
    short int triangleHeight, triangleWidth;
    ofPoint triPtA, triPtB, triPtC;
    
    
};
