// http://www.astronexus.com/node/34
// https://github.com/astronexus/HYG-Database
// http://www.astronexus.com/hyg

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    
    ofBackground(0, 255);
    ofEnableAntiAliasing();
//    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSetCircleResolution(128);
    
    starMesh.enableColors();
    starMesh.enableIndices();
    starLineMesh.enableColors();
    starLineMesh.enableIndices();
    
    starMesh.setMode(OF_PRIMITIVE_POINTS);
    starLineMesh.setMode(OF_PRIMITIVE_LINES);
    
    glEnable(GL_POINT_SMOOTH);
    glLineWidth(1);
    glPointSize(1);
    
    posSize = ofPoint(ofGetWidth()*4, ofGetHeight()*4);
    
    gui.setup();
    //    gui.add(starAlpha.setup("Star Alpha", 0.5, 0, 1) );
    //    gui.add(lineAlpha.setup("Line Alpha", 0.5, 0, 1) );
    //    gui.add(numBaseCircle.setup("Num BaseCircle", 65, 10, 100));
    //    gui.add(circleBaseSizeRatio.setup("BaseCircle Size", 0.08, 0, 0.5) );
    //    gui.add(innerBaseCircleSize.setup("InnerBaseCircle Size", 235, 0, 1000) );
    //    gui.add(innerBaseCircleAlpha.setup("InnerCircle Size", 0.695, 0, 1) );
    //    gui.add(numCircle.setup("Num Circle", 66, 10, 100));
    //    gui.add(circleSizeRatio.setup("Circle Size", 0.15, 0, 5) );
    //    gui.add(innerCircleSize.setup("InnerCircle Size", 560, 0, 1000) );
    //    gui.add(innerCircleAlpha.setup("InnerCircle Size", 0.565, 0, 1) );
    
    csv.loadFile( ofToDataPath("hygxyz.csv") );
    
    for(int i=1; i<csv.numRows; i++) {
        float tempX = ofToFloat( csv.data[i][17] );
        float tempY = ofToFloat( csv.data[i][18] );
        float tempZ = ofToFloat( csv.data[i][19] );
        float tempBright = ofMap( ofToFloat( csv.data[i][14] ), 30, -20, 0, 255 );
        string tempColor = csv.data[i][15];
        
        ofVec3f _position = ofVec3f( tempX, tempY, tempZ );
        
        starMesh.addVertex( _position );
        //        ofColor _cS = ofColor(255,tempBright);
        
        ofColor _hColor;
        if (tempColor.size()>0) {
            switch (tempColor.at(0)) {
                case 'O':
                    _hColor = ofColor(120,120,255,tempBright);
                    break;
                case 'B':
                    _hColor = ofColor(192,207,255,tempBright);
                    break;
                case 'A':
                    _hColor = ofColor(247,246,255,tempBright);
                    break;
                case 'F':
                    _hColor = ofColor(253,255,203,tempBright);
                    break;
                case 'G':
                    _hColor = ofColor(255,243,145,tempBright);
                    break;
                case 'K':
                    _hColor = ofColor(253,146,64,tempBright);
                    break;
                case 'M':
                    _hColor = ofColor(250,70,67,tempBright);
                    break;
                default:
                    _hColor = ofColor(255,255,255,tempBright);
                    break;
            }
            
        }
        
        ofColor _cS = ofColor(_hColor);
        starMesh.addColor( _cS );
        
        starLineMesh.addVertex(_position);
        ofColor _cL = ofColor(255,40);
        starLineMesh.addColor( _cL );
    }
    
    
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
    
    easyCam.setAutoDistance(false);
    easyCam.setPosition(0, 0, 500);
    
    guiOnOff = true;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=1; i<csv.numRows; i++) {
        //        ofColor _cS = starMesh.getColor(i);
        //        starMesh.setColor(i, ofColor( _cS.r, _cS.g, _cS.b, _cS.a * starAlpha ));
        //
        //        ofColor _cL = ofColor(225,lineAlpha);
        //        starLineMesh.setColor(i, _cL );
    }
    
    rotationY = rotationY + 0.125;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    easyCam.begin();
    
    ofPushMatrix();
    
    ofRotateY( rotationY );
    
    ofPushStyle();
    
    //    drawingBaseCircle(90);
    //    drawingCircle(90);
    //    drawingCircle(180);
    
    //    starLineMesh.draw();
    starMesh.draw();
    
    ofPopStyle();
    ofPopMatrix();
    
    easyCam.end();
    
    //    if (guiOnOff) {
    //        ofPushMatrix();
    //        ofPushStyle();
    //        ofDisableDepthTest();
    //        gui.draw();
    //        ofPopStyle();
    //        ofPopMatrix();
    //    }
    
    //    information();
}


//--------------------------------------------------------------
void ofApp::drawingBaseCircle(int _degX){
    
    ofPushMatrix();
    ofPushStyle();
    ofRotateX(_degX);
    int _numCircle = numBaseCircle;
    for (int i=0; i<_numCircle; i++) {
        ofNoFill();
        ofSetColor( 255, ofMap(i,0,_numCircle-1,140,0)*innerBaseCircleAlpha );
        ofCircle(0, 0, innerBaseCircleSize+i*i*circleBaseSizeRatio);
    }
    ofPopStyle();
    ofPopMatrix();
    
}


//--------------------------------------------------------------
void ofApp::drawingCircle(int _degX){
    
    ofPushMatrix();
    ofPushStyle();
    ofRotateX(_degX);
    int _numCircle = numCircle;
    for (int i=0; i<_numCircle; i++) {
        ofNoFill();
        ofSetColor( 255, ofMap(i,0,_numCircle-1,140,0)*innerCircleAlpha );
        ofCircle(0, 0, innerCircleSize+i*i*circleSizeRatio);
    }
    ofPopStyle();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::information(){
    
    ofSetColor(255);
    ofDrawBitmapString( ofToString(ofGetFrameRate()), 10, 20 );
    ofDrawBitmapString( "starNum : " + ofToString( starMesh.getNumVertices() ), 10, 40 );
    ofDrawBitmapString( "lineNum : " + ofToString( countLine ), 10, 60 );
    
    ofDrawBitmapString( "StarData : https://github.com/astronexus/HYG-Database", 10, ofGetHeight()-20 );
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='g') {
        guiOnOff = !guiOnOff;
    }
    
    
    if (key=='c') {
        ofImage _pix;
        string _file;
        _pix.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
        _pix.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        _file = "../../../"+ofGetTimestampString()+" Capture.png";
        _pix.saveImage( _file );
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
    
}
