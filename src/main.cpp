#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    float print_width = 17;
    float print_height = 23;
    // This will help make the sketch window bigger
    float make_bigger = 40;

	//ofSetupOpenGL(1024,768, OF_WINDOW);			// <--------
    ofSetupOpenGL(int(print_width * make_bigger), int(print_height * make_bigger), OF_WINDOW);
    //setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
                  
                

}
