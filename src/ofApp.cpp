
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    angle = 0;
    oneShot = false;
    pdfRendering = false;
    
    ofBackground(0,0,0);
    ofSetVerticalSync(true);
    
    font.loadFont("frabk.ttf", 24, true, false, true);
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    angle++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofFill();
    //ofSetColor(255, 100, 100);
    
    coneComplexity  =       8;
    scoopComplexity =       8;
    scoopSkip       =       3;
    
    triangleHeight  =     ofGetHeight()/5;
    triangleWidth = triangleHeight/coneComplexity*2;
    
    
    screenMidpoint.set(ofGetWidth()/2, ofGetHeight()/2);
    //screenMidpoint.set(500,200);
    triPtA = screenMidpoint;
    triPtB.set(triPtA.x - triangleWidth/2, triPtA.y +triangleHeight);
    triPtC.set(triPtA.x + triangleWidth/2, triPtA.y + triangleHeight);
    
    //cout << triPtA << triPtB << triPtC << endl;
    
    //ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(180);
    ofEllipse(triPtA, triangleHeight/3, triangleHeight/3);
    
    for(unsigned int j = 0; j < coneComplexity; j++){
        ofTranslate(triPtA);
        ofRotate(360/coneComplexity);
        ofTranslate(-triPtA);
        ofPoint rectCorner;
        rectCorner = triPtB;
        ofPoint offset;
        offset.set(triangleWidth / scoopComplexity * scoopSkip, 0);
        for(int k=0; k < scoopComplexity; k+=scoopSkip){
            ofSetColor(255, 255, 255);
            
            //cout << rectCorner << endl;
            short int cutoutDist = triangleHeight/10;
            for(int l=0; l<2; l++){
                ofRect(rectCorner, triangleWidth/scoopComplexity, triangleWidth*coneComplexity/2);
            }
            rectCorner+=offset;
            
        }
        ofSetColor(180);
        ofTriangle(triPtA, triPtB, triPtC);
        
    }
    
    
    
    
    
    
    
    if( oneShot ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }
    
    if( oneShot ){
        ofEndSaveScreenAsPDF();
        oneShot = false;
    }
    
    /*
     
     ofSetColor(255);
     
     //lets draw a box with a trail
     ofSetColor(245, 58, 135);
     
     ofRectangle boxBounds(32, 500, ofGetWidth()-32, 250);
     
     
     
     ofNoFill();
     ofBeginShape();
     ofVertices(boxTrail);
     ofEndShape(false);
     
     ofFill();
     ofSetRectMode(OF_RECTMODE_CENTER);
     
     ofPushMatrix();
     //      ofTranslate(x, y, 0);
     ofRotate(angle);
     ofRect(0, 0, 30, 30);
     ofPopMatrix();
     
     
     */
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key=='r'){
        pdfRendering = !pdfRendering;
        if( pdfRendering ){
            ofSetFrameRate(12);  // so it doesn't generate tons of pages
            ofBeginSaveScreenAsPDF("recording-"+ofGetTimestampString()+".pdf", true);
        }else{
            ofSetFrameRate(60);
            ofEndSaveScreenAsPDF();
        }
    }
    
    if( !pdfRendering && key == 's' ){
        oneShot = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    for(unsigned int j = 0; j < dropZoneRects.size(); j++){
        if( dropZoneRects[j].inside( dragInfo.position ) ){
            images[j].loadImage( dragInfo.files[0] );
            break;
        }
    }
}


