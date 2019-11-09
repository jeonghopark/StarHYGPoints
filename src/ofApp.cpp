// http://www.astronexus.com/node/34
// https://github.com/astronexus/HYG-Database
// http://www.astronexus.com/hyg

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

//#ifdef DEBUG
//
//#else
//    ofSetDataPathRoot("../Resources/data/");
//#endif

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

    posSize = ofPoint(ofGetWidth() * 4, ofGetHeight() * 4);


    csv.load(ofToDataPath("hygxyz.csv"));
    for (int i = 1; i < csv.getNumRows(); i++) {
        if (ofToFloat(csv.getData()[i][9]) < 10) {
            float tempX = ofToFloat(csv.getData()[i][17]);
            float tempY = ofToFloat(csv.getData()[i][18]);
            float tempZ = ofToFloat(csv.getData()[i][19]);
            float tempBright = ofMap(ofToFloat(csv.getData()[i][14]), 30, -20, 0, 255);
            string tempColor = csv.getData()[i][15];

            ofVec3f _position = ofVec3f(tempX, tempY, tempZ);

            starMesh.addVertex(_position);
            //        ofColor _cS = ofColor(255,tempBright);

            ofColor _hColor;

            if (tempColor.size() > 0) {
                switch (tempColor.at(0)) {
                case 'O':
                    _hColor = ofColor(120, 120, 255, tempBright);
                    break;

                case 'B':
                    _hColor = ofColor(192, 207, 255, tempBright);
                    break;

                case 'A':
                    _hColor = ofColor(247, 246, 255, tempBright);
                    break;

                case 'F':
                    _hColor = ofColor(253, 255, 203, tempBright);
                    break;

                case 'G':
                    _hColor = ofColor(255, 243, 145, tempBright);
                    break;

                case 'K':
                    _hColor = ofColor(253, 146, 64, tempBright);
                    break;

                case 'M':
                    _hColor = ofColor(250, 70, 67, tempBright);
                    break;

                default:
                    _hColor = ofColor(255, 255, 255, tempBright);
                    break;
                }

            }

            ofColor _cS = ofColor(_hColor);
            starMesh.addColor(_cS);

            starLineMesh.addVertex(_position);
            ofColor _cL = ofColor(255, 40);
            starLineMesh.addColor(_cL);
        }

    }


    float connectionDistanceStar = 40;
    int numberStars = starLineMesh.getNumVertices();

    for (int i = 0; i < numberStars; i += 50) {
        ofVec3f verFirst = starLineMesh.getVertex(i);

        for (int j = i + 1; j < numberStars; j += 50) {
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
    easyCam.setPosition(0, 0, 18);

//    guiOnOff = true;

}

//--------------------------------------------------------------
void ofApp::update() {

    for (int i = 1; i < csv.getNumRows(); i++) {
        //        ofColor _cS = starMesh.getColor(i);
        //        starMesh.setColor(i, ofColor( _cS.r, _cS.g, _cS.b, _cS.a * starAlpha ));
        //
        //        ofColor _cL = ofColor(225,lineAlpha);
        //        starLineMesh.setColor(i, _cL );
    }

    rotationY = rotationY + 0.08;

}

//--------------------------------------------------------------
void ofApp::draw() {

    easyCam.begin();

    ofPushMatrix();

    
    ofRotateXDeg(-40);
    ofRotateYDeg(rotationY);

    ofPushStyle();


    //    starLineMesh.draw();
    glPointSize(3);
    starMesh.draw();


    
    for (int i = 0; i < starMesh.getNumVertices(); i++) {
        ofPushMatrix();
        ofPushStyle();
        ofSetLineWidth(0.3);
        ofSetColor(255, 30);
        ofDrawLine(starMesh.getVertex(i).x, starMesh.getVertex(i).y, starMesh.getVertex(i).z, starMesh.getVertex(i).x, 0, starMesh.getVertex(i).z);
        ofPopStyle();
        ofPopMatrix();
    }

    for (int i = 0; i < starMesh.getNumVertices(); i++) {
        ofPushMatrix();
        ofPushStyle();
        ofSetLineWidth(0.3);
        ofRotateXDeg(90);
        ofSetColor(255, 30);
        ofDrawCircle(starMesh.getVertex(i).x, starMesh.getVertex(i).z, 0, 0.05);
        ofPopStyle();
        ofPopMatrix();
    }

    ofPushMatrix();
    ofPushStyle();
    ofSetLineWidth(0.3);
    ofSetColor(255, 30);
    ofDrawLine(-12, 0, 0, 12, 0, 0);
    ofDrawLine(0, 0, 12, 0, 0, -12);
    ofPopStyle();
    ofPopMatrix();
    
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 30);
    ofSetLineWidth(0.3);
    ofRotateXDeg(90);
    for (int i = 0; i< 12; i++) {
        ofDrawCircle(0, 0, 1 * i);
    }
    ofPopStyle();
    ofPopMatrix();
    
    
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
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    if (key == 'c') {
        ofImage _pix;
        string _file;
        _pix.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
        _pix.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        _file = "../../../" + ofGetTimestampString() + " Capture.png";
        _pix.save(_file);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
