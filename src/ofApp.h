#pragma once

#include "ofMain.h"
#include "json_helper.hpp"
#include "song.hpp"
#include "ofxDatGui.h"


class mediaPlayer : public ofBaseApp {
    
    const int IMAGE_SPACE_VAL = 75;
    const int TEXT_SPACE_VAL = 75;
    
    const int INITIAL_IMG_Y_VAL = 30;
    const int INITIAL_TEXT_Y_VAL = 50;
    
    const int INITIAL_IMG_X_VAL = 30;
    const int INITIAL_TEXT_X_VAL = 90;
    
    const int IMG_X_OFFSET = 300;
    const int TEXT_X_OFFSET = 360;
    
    const int IMG_SIZE_SCALER = 50;

private:
    
    JSONHelper helper_;
    std::vector<Song> songs_;
    std::vector<ofImage> song_images_;
    
    std::vector<ofxDatGuiButton*> song_buttons;



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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void PopulateSongs();
    void PopulateImages();
    
    void DrawImagesAndButtons();
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
		
};
