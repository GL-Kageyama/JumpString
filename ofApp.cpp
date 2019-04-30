#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowTitle("JumpString");
    
    ofBackground(255, 255, 255);
    ofSetLineWidth(5);
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
    
    ofTrueTypeFont font;
    // Prepare the font yourself.
    font.loadFont("SourceHanSansTW-Heavy.otf", 250, true, true, true);
    this->span = 20;
    
    ofFbo fbo;
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(0);
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    
    string word = "JUMP!";
    font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) * 0.5);
    
    fbo.end();
    
    ofPixels pixels;
    fbo.readToPixels(pixels);
    
    for(int x = 0; x < fbo.getWidth(); x += this->span){
        for(int y = 0; y < fbo.getHeight(); y += this->span){
            if(pixels.getColor(x, y) != ofColor(0, 0)){
                this->locations.push_back(glm::vec2(x - ofGetWidth() * 0.5, ofGetHeight() - y - ofGetHeight() * 0.5));
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    this->cam.begin();
    
    float threshold = 0.7;
    for(auto& location : this->locations){
        float noise_value = ofNoise(location.x * 0.005, location.y * 0.005, ofGetFrameNum() * 0.005);
        int z = 0;
        float rotate_x = 0.f;
        if(noise_value > threshold){
            z += ofMap(noise_value, threshold, 1.0, 0, 600);
            rotate_x = ofMap(noise_value, threshold, 1.0, 0, 360 * 4);
        }
        auto draw_location = glm::vec3(location, z);
        
        ofPushMatrix();
        ofTranslate(draw_location);
        ofRotateX(rotate_x);
        ofRotateY(rotate_x);
        
        ofFill();
        ofSetColor(244, 66, 125, 220);
        ofDrawRectangle(glm::vec3(), this->span - 8, this->span - 8);
        
        ofNoFill();
        ofSetColor(79, 42, 158, 80);
        ofDrawRectangle(glm::vec3(), this->span - 4, this->span - 4);
        
        ofPopMatrix();
    }
    
    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
