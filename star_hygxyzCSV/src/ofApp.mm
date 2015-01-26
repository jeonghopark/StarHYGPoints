// http://www.astronexus.com/node/34
// https://github.com/astronexus/HYG-Database


#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
<<<<<<< HEAD:src/ofApp.mm

    ofSetOrientation(OF_ORIENTATION_90_RIGHT);
    ofSetFrameRate(60);
    
    ofxAccelerometer.setup();               //accesses accelerometer data
    ofxiPhoneAlerts.addListener(this);      //allows elerts to appear while app is running
	ofRegisterTouchEvents(this);            //method that passes touch events

    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];

=======
    
>>>>>>> 98328db... + change update:src/ofApp.cpp
    ofBackground( 10 );
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    ofSetCircleResolution(64);
    
<<<<<<< HEAD:src/ofApp.mm

//    inputBuffer.clear();
    volHistory.clear();
    volNumHeight = 256;
    
	bufferSize = 256;
    initialBufferSize = 256;
	sampleRate = 44100;
    
//	inputBuffer.assign(bufferSize, 0.0);
	volHistory.assign(volNumHeight, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
//    inputBuffer = new float[initialBufferSize];
//	memset(inputBuffer, 0, initialBufferSize * sizeof(float));
    volHistory.push_back( scaledVol );
    
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 1);
    

    
=======
>>>>>>> 98328db... + change update:src/ofApp.cpp
    csv.loadFile(ofToDataPath("hygxyz.csv"));
    
    //    glPointSize(1);
    
    easyCam.rotate(-10, 1, 0, 0);
    easyCam.setDistance(300);
    
	for(int i=1; i<csv.numRows; i++) {
        
        float tempX = ofToFloat( csv.data[i][17] );
        float tempY = ofToFloat( csv.data[i][18] );
        float tempZ = ofToFloat( csv.data[i][19] );
        float tempBright = ofMap( ofToFloat( csv.data[i][14] ), 40, -10, 0, 255 );
        
        ofVec3f _position( tempX, tempY, tempZ );
        starMesh.addVertex( _position );
        zPositionFactor.push_back(tempZ);
        
        ofColor c (tempBright,tempBright,tempBright,80);
        starMesh.addColor( c );
        
	}
    
    starLineMesh = starMesh;
    
    float connectionDistanceStar = 40;
    int numberStars = starLineMesh.getNumVertices();
    
    for (int i=0; i<numberStars; i+=50) {
        ofVec3f verFirst = starLineMesh.getVertex(i);
        for (int j=i+1; j<numberStars; j+=50) {
            ofVec3f verSecond = starLineMesh.getVertex(j);
            float distance = verFirst.distance(verSecond);
            if (distance < connectionDistanceStar) {
                starLineMesh.addIndex(i);
                starLineMesh.addIndex(j);
                countLine++;
            }
        }
    }
    
    cout << csv.data[0][14] << endl;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
<<<<<<< HEAD:src/ofApp.mm
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 3.0, true);
  
//    cout << scaledVol << endl;
    
//    volHistory.push_back( scaledVol );
	
//    if( volHistory.size() > volNumHeight ){
//		volHistory.erase(volHistory.begin());
//	}

    int numberVerts = starMesh.getNumVertices();
//
//    for (int i=0; i<numberVerts; i++) {
//        ofVec3f temp = starMesh.getVertex(i);
//        temp.z = temp.z;
//        scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 30.0, true);
//    }
    
=======
>>>>>>> 98328db... + change update:src/ofApp.cpp
    rotY = rotY + 0.1;
    
    sinY = sin(ofDegToRad(rotY));
    
<<<<<<< HEAD:src/ofApp.mm
//    for (int i=0; i<numberVerts; i++) {
//        ofVec3f temp = starMesh.getVertex(i);
//        temp.x = temp.x;
//        temp.y = temp.y;
//        temp.z = temp.z;
//        starMesh.setVertex( i, ofVec3f( temp.x, temp.y, zPositionFactor[i]) );
//        starLineMesh.setVertex( i, ofVec3f( temp.x, temp.y, zPositionFactor[i]) );
//    }
=======
    int numberVerts = starMesh.getNumVertices();
    for (int i=0; i<numberVerts; i++) {
        ofVec3f temp = starMesh.getVertex(i);
        temp.x = temp.x;
        temp.y = temp.y;
        temp.z = temp.z;
        starMesh.setVertex( i, temp );
    }
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor centerColor = ofColor(35, 28, 18);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    
    ofRotateY(rotY);
    drawingCircle(90);
    
    starMesh.setMode(OF_PRIMITIVE_POINTS);
    starMesh.draw();
    starLineMesh.setMode(OF_PRIMITIVE_LINES);
    starLineMesh.draw();
    
    easyCam.end();
    
    ofSetColor(255);
    ofDrawBitmapString( ofToString(ofGetFrameRate()), 10, 20 );
    ofDrawBitmapString( "starNum : " + ofToString( starMesh.getNumVertices() ), 10, 40 );
    ofDrawBitmapString( "lineNum : " + ofToString( countLine ), 10, 60 );
    
<<<<<<< HEAD:src/ofApp.mm
//    ofDrawBitmapString( "StarData : https://github.com/astronexus/HYG-Database", 10, ofGetHeight()-20 );
=======
    ofDrawBitmapString( "StarData : https://github.com/astronexus/HYG-Database", 10, ofGetHeight()-20 );
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}


void ofApp::drawingCircle(int _degX){
    
    ofPushMatrix();
    ofRotateX(_degX);
    for (int i=0; i<20; i++) {
        ofNoFill();
        ofSetColor(255,ofMap(i,0,19,140,0));
        ofCircle(0, 0, 50+i*i);
    }
    ofPopMatrix();
    
}

<<<<<<< HEAD:src/ofApp.mm

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	int numCounted = 0;
    
	for (int i = 0; i < bufferSize; i++){
//		inputBuffer[i]		= input[i];
		curVol += input[i] * input[i];
		numCounted+=2;
	}
	
	curVol /= (float)numCounted;
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;

=======
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='f') {
        ofToggleFullscreen();
    }
    
>>>>>>> 98328db... + change update:src/ofApp.cpp
}




void ofApp::exit(){
        
}


//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::touchDown(ofTouchEventArgs & touch){
=======
void ofApp::keyReleased(int key){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
=======
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
=======
void ofApp::mousePressed(int x, int y, int button){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::touchCancelled(ofTouchEventArgs & touch){
=======
void ofApp::mouseReleased(int x, int y, int button){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::lostFocus(){
=======
void ofApp::windowResized(int w, int h){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::gotFocus(){
=======
void ofApp::gotMessage(ofMessage msg){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}

//--------------------------------------------------------------
<<<<<<< HEAD:src/ofApp.mm
void ofApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
=======
void ofApp::dragEvent(ofDragInfo dragInfo){
>>>>>>> 98328db... + change update:src/ofApp.cpp
    
}
