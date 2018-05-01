#pragma once

#include "ofMain.h"
#include "json_helper.hpp"
#include "song.hpp"
#include "ofxDatGui.h"
#include "ofxGSTT.h"


class mediaPlayer : public ofBaseApp {
    
    const int IMAGE_SPACE_VAL = 75;
    const int TEXT_SPACE_VAL = 75;
    const int BTN_SPACE_VAL = 75;
    
    const int INITIAL_IMG_Y_VAL = 30;
    const int INITIAL_BTN_Y_VAL = 30;
    const int INITIAL_TEXT_Y_VAL = 55;
    
    const int INITIAL_IMG_X_VAL = 30;
    const int INITIAL_TEXT_X_VAL = 102;
    const int INITIAL_BTN_X_VAL = 90;
    
    const int IMG_X_OFFSET = 300;
    const int TEXT_X_OFFSET = 372;
    const int BTN_X_OFFSET = 360;
    
    const int IMG_SIZE_SCALER = 50;
    
    const int BTN_WIDTH = 180;
    
    const int CURRENT_SONG_IMG_X = 630;
    const int CURRENT_SONG_IMG_Y = 120;
    const int CURRENT_SONG_IMG_DIM = 300;
    
    const int CURRENT_SONG_INFO_X = 630;
    const int CURRENT_SONG_NAME_Y = 450;
    const int CURRENT_SONG_ARTIST_Y = 475;
    
    const int PLAY_BTN_X = 750;
    const int PLAY_BTN_Y = 510;
    const int PLAY_BTN_DIM = 75;
    
    const int MIC_BTN_X = 758;
    const int MIC_BTN_Y = 595;
    const int MIC_BTN_DIM = 60;
    
    const int SKIP_CTRL_BTNS_Y = 520;
    const int SKIP_CTRL_BTNS_DIM = 50;
    
    const int SKIP_BTN_X = 843;
    const int PREVIOUS_BTN_X = 683;

private:
    
    JSONHelper helper_;
    std::vector<Song> songs_;
    std::vector<ofImage> song_images_;
    
    std::vector<ofxDatGuiButton*> song_buttons_;
    std::vector<ofSoundPlayer> song_players_;
    
    ofTrueTypeFont name_font_;
    ofTrueTypeFont artist_font_;
    
    ofImage play_button_;
    ofImage pause_button_;
    ofImage skip_button_;
    ofImage previous_button_;
    ofImage mic_button_;
    
    std::map<std::string, int> song_indeces_;
    
    ofSoundStream sound_stream_;
    ofxGSTT gstt_;
    //string response_str_;
    bool is_auto_recording_ = false;
    float volume_threshold_ = 0.05f;
    bool is_mic_on_ = false;
    
    bool has_clicked_song_ = false;
    bool is_paused_ = false;
    int current_song_index_ = -1;
    
    


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
    void PopulateImagesAndSongMap();
    
    void SkipButtonPressed();
    void PreviousButtonPressed();
    void ShuffleCommand();
    
    void LoadSoundPlayers();
    
    void DrawImagesAndButtons();
    
    void SetupButtons();
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    void gsttResponse(ofxGSTTResponseArgs & response);
    void SetupGSTT();

		
};
