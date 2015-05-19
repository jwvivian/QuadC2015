//Parsons Collab QuadC
//Jingyi Wei (Vivian)
//FFT reference to https://github.com/julapy/ofxFFT
//Special thanks to Bernardo Schorr and Umi Syam

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //setup
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    
    //fft setup, set mirrordata to true because we want symmetrical data, set threshold, peakdecay and maxdecay to fixed values.
    fftLive.setMirrorData(true);
    fftLive.setup();
    fftLive.setThreshold(0.5);
    fftLive.setPeakDecay(0.915);
    fftLive.setMaxDecay(0.995);
    
    meshOri = meshWrap = ofMesh::plane(ofGetWindowWidth(), ofGetWindowHeight(), 100, 100);
    
    meshWrap.setMode(OF_PRIMITIVE_POINTS);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //update for fft
    fftLive.update();
    
    vector<ofVec3f> & vertsOriginal = meshOri.getVertices();
    vector<ofVec3f> & vertsWarped = meshWrap.getVertices();
    int numOfVerts = meshOri.getNumVertices();
    
    float * audioData = new float[numOfVerts];
    fftLive.getFftPeakData(audioData, numOfVerts);
    
    float diff = 300;
    
    for (int i=0; i<numOfVerts; i++){
        
        float audioValue = audioData[i];
        ofVec3f & vertOriginal = vertsOriginal[i];
        ofVec3f & vertWarped = vertsWarped[i];
        
        ofVec3f direction = vertOriginal.getNormalized();
        
        //fft controls mesh displacement direction
        if(audioValue>=0.5){
            vertWarped = vertOriginal + direction * diff * audioValue;
        }
        if(audioValue<0.5){
            vertWarped = vertOriginal - direction * diff * audioValue;
        }
        
        //adding mesh color
        meshWrap.addColor(ofColor::fromHsb(ofRandom(150,200), ofRandom(200, 255), 255));
    }
    delete[] audioData;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw the mesh, and rotate it around z-axis
    ofBackgroundGradient(ofColor(200), ofColor(0));
    cam.begin();
    //cout<<cam.getDistance()<<endl;
    cam.setDistance(440);
    float angle = ofGetElapsedTimef()*5;
    ofRotate(angle, 0, 0, 1);
    meshWrap.drawWireframe();
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'm' && 'M'){
        player.loadSound("music.mp3");
        player.setLoop(true);
        player.play();
        fftFile.startFrameSync(&player, 30);
    }
    
    if(key == 's' && 'S'){
        player.stop();
        player.unloadSound();
    }
    
    if(key == 'p' && 'P'){
        meshWrap.setMode(OF_PRIMITIVE_POINTS);
    }
    
    if(key == 't' && 'T'){
        meshWrap.setMode(OF_PRIMITIVE_TRIANGLES);
    }
    
    if(key == 'l' && 'L'){
        meshWrap.setMode(OF_PRIMITIVE_LINES);
    }
    
    if(key == 'h' && 'H'){
        meshOri = meshWrap = ofMesh::sphere(300);
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