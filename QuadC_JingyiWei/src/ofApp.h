//Parsons Collab QuadC
//Jingyi Wei (Vivian)
//FFT reference to https://github.com/julapy/ofxFFT
//Special thanks to Bernardo Schorr and Umi Syam

#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxFFTFile.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //---------fft-----------//
    ofxFFTLive fftLive;
    ofxFFTFile fftFile;
    ofSoundPlayer player;
    //mesh
    ofEasyCam cam;
    ofMesh meshOri;
    ofMesh meshWrap;
    ofMesh mesh;
};