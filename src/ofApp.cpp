
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
    
    if( oneShot ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }

    coneComplexity  =       6;
    scoopComplexity =       6;
    scoopSkip       =       3;
    
    triangleHeight  =     280;
    triangleWidth = triangleHeight/coneComplexity*2;
    
    screenMidpoint.set(ofGetWidth()/2, ofGetHeight()/2);
    //screenMidpoint.set(500,200);
    triPtA = screenMidpoint;
    triPtB.set(triPtA.x - triangleWidth/2, triPtA.y +triangleHeight);
    triPtC.set(triPtA.x + triangleWidth/2, triPtA.y + triangleHeight);
    
    ofNoFill();
    ofSetLineWidth(2);
    ofSetColor(180);
    //ofEllipse(triPtA, triangleHeight/3, triangleHeight/3);
    
    //float angleToRotate = getAngle(triPtA.x, triPtA.y)/(ofGetMouseY()/50);
    //float angleToRotate = ofGetMouseY()/10;
    float angleToRotate = 19;
    
    cout << "angleToRotate: " << angleToRotate << "   mouseX: " << ofGetMouseX() << "    mouseY: " << ofGetMouseY() << endl;
    
    ofTranslate(triPtA);
    ofRotate(-angleToRotate);
    ofTranslate(-triPtA);
    
    ofTranslate(screenMidpoint.x, -screenMidpoint.y*.5);
    
    for(unsigned int j = 0; j < coneComplexity; j++){
        ofTranslate(triPtA);

        
        //fuck, triganometry... I need to get the angle from the length of the two sides of the triangle
        
        ofRotate(angleToRotate);
        //ofRotate(((triangleWidth * coneComplexity) * (2 * PI * triangleHeight)) / coneComplexity   );
        ofTranslate(-triPtA);
        ofPoint rectCorner;
        rectCorner = triPtB;
        ofPoint offset;
        offset.set(triangleWidth / scoopComplexity * scoopSkip, 0);
        ofSetColor(180);
        
        
        ofTriangle(triPtA, triPtB, triPtC);
        
       
        for(int k=0; k < scoopComplexity; k+=scoopSkip){
            rectCorner+=offset/2;

            ofSetColor(255, 255, 255);
            
            //cout << rectCorner << endl;
            short int cutoutDist = triangleHeight/30;
            short int cutoutHeight = triangleHeight/80;
            short int coneHeight = triangleWidth*coneComplexity/2;
            
            ofFill();
            ofSetColor(255);
            
            for(int m=0; m<2; m++){
                int mHeight = (m * coneHeight) + (m * cutoutHeight);
                int mYpos =  (m * cutoutDist); //(l * coneHeight) +
                ofRect(rectCorner.x, rectCorner.y - mYpos, triangleWidth/scoopComplexity, coneHeight - mHeight );
                //cout << m << endl;
            }
            ofNoFill();
            rectCorner+=offset/2;
            
        }

        
    }
    
    

    
    if( oneShot ){
        ofEndSaveScreenAsPDF();
        oneShot = false;
    };
    
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

float ofApp::getAngle(float _x, float _y) {
	if (_x == 0.0) {
		if(_y < 0.0)
			return 270;
		else
			return 90;
	} else if (_y == 0) {
		if(_x < 0)
			return 180;
		else
			return 0;
	}
    
	if ( _y > 0.0)
		if (_x > 0.0)
			return atan(_y/_x) * GRAD_PI;
		else
			return 180.0 - (atan(_y/-_x) * GRAD_PI);
		else
			if (_x > 0.0)
				return 360.0 - (atan(-_y/_x) * GRAD_PI);
			else
				return 180.0 + (atan(-_y/-_x) * GRAD_PI);
}


