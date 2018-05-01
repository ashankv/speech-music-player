#pragma once

#include "ofMain.h"
#include "json_helper.hpp"
#include "song.hpp"
#include "ofxDatGui.h"
#include "ofxGSTT.h"

class mediaPlayer : public ofBaseApp {
    
    // Change absolute path to data according to you
    const std::string ABS_PATH = "/Users/ashank/Documents/of_v0.9.8_osx_release/apps/myApps/SpeechMusicPlayer/bin/data/";
    
    // Spacing for image, artist text, and buttons on the left.
    const int VERT_SPACE_VAL = 75;
    
    // Initial y-values for images, buttons, and text
    const int INITIAL_IMG_Y_VAL = 30;
    const int INITIAL_BTN_Y_VAL = 30;
    const int INITIAL_TEXT_Y_VAL = 55;
    
    // Initial x-values for images, buttons, and text
    const int INITIAL_IMG_X_VAL = 30;
    const int INITIAL_TEXT_X_VAL = 102;
    const int INITIAL_BTN_X_VAL = 90;
    
    // Horizontal offset spacing for 2nd column
    const int IMG_X_OFFSET = 300;
    const int TEXT_X_OFFSET = 372;
    const int BTN_X_OFFSET = 360;
    
    // Size scaler for the 20 images
    const int IMG_SIZE_SCALER = 50;
    
    // Button width
    const int BTN_WIDTH = 180;
    
    // Current song image coordinates and dimension
    const int CURRENT_SONG_IMG_X = 630;
    const int CURRENT_SONG_IMG_Y = 120;
    const int CURRENT_SONG_IMG_DIM = 300;
    
    // Current song info text coordinates
    const int CURRENT_SONG_INFO_X = 630;
    const int CURRENT_SONG_NAME_Y = 450;
    const int CURRENT_SONG_ARTIST_Y = 475;
    
    // Play button coordinates and dimension
    const int PLAY_BTN_X = 750;
    const int PLAY_BTN_Y = 510;
    const int PLAY_BTN_DIM = 75;
    
    // Mic button coordinates and dimension
    const int MIC_BTN_X = 758;
    const int MIC_BTN_Y = 610;
    const int MIC_BTN_DIM = 60;
    
    // Skip button coordinates and dimension
    const int SKIP_CTRL_BTNS_Y = 520;
    const int SKIP_CTRL_BTNS_DIM = 50;
    
    // Previous button coordinates and dimension
    const int SKIP_BTN_X = 843;
    const int PREVIOUS_BTN_X = 683;
    
    // Push to talk information coordinates
    const int TALK_INFO_X = 825;
    const int TALK_INFO_Y = 628;
    
    // Font sizes
    const int NAME_FONT_SIZE = 22;
    const int ARTIST_FONT_SIZE = 15;
    const int INFO_FONT_SIZE = 12;
    
    // "Play" constants for speech recognition
    const int PLAY_TXT_SIZE = 4;
    const int PLAY_PARAMETER_INDEX = 5;
    
    // Background color of the window
    const int BACKGROUND_HEX_COLOR = 0x90CAF9;
    
private:
    
    JSONHelper helper_; // JSON helper object for parsing JSON
    std::vector<Song> songs_; // Vector of Song objects
    std::vector<ofxDatGuiButton*> song_buttons_; // Vector of Buttons corresponding to Song objects (NEEDS TO BE SEPARATED FROM SONG CLASS!)
    std::vector<ofImage> song_images_; // Vector of Images corresponding to Song objects (NEEDS TO BE SEPARATED FROM SONG CLASS!)
    std::map<std::string, int> song_indeces_; // Map of song name to index in songs_ vector
    
    bool has_clicked_song_ = false; // Check if song has been clicked yet
    bool is_paused_ = false; // Check if current song is paused
    int current_song_index_ = -1; // Holds the index of the current song
    
    // GSTT variables
    ofSoundStream sound_stream_;
    ofxGSTT gstt_;
    float volume_threshold_ = 0.05f;
    bool is_mic_on_ = false;
    
    ofTrueTypeFont name_font_; // Font of name of song
    ofTrueTypeFont artist_font_; // Font of name of artist
    ofTrueTypeFont info_font_; // Font of any appearing instructions
    
    // Media control images
    ofImage play_button_;
    ofImage pause_button_;
    ofImage skip_button_;
    ofImage previous_button_;
    ofImage mic_button_;
    
    // Sound players for opening and closing mics
    ofSoundPlayer mic_open_;
    ofSoundPlayer mic_close_;
    
    // Functions for populating song data structure
    void PopulateSongsAndMap();
    void PopulateImagesAndSoundPlayers();
    
    // Setup UI/Speech Recognition elements
    void SetupButtons();
    void SetupGSTT();
    
    // Functions for UI elements
    void LoadFonts();
    void LoadMicSounds();
    void LoadMediaControlImages();
    
    // Function for drawing images and buttons
    void DrawImagesAndButtons();
    
public:
    
    // Function for one time setup
    void setup();
    
    // Function for updating before every draw
    void update();
    
    // Function for drawing on the user interface
    void draw();
    
    // Functions for key openFrameworks methods
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    // Functions for media control actions
    void SkipButtonPressed();
    void PreviousButtonPressed();
    void MicButtonPressed();
    void ShuffleCommand();
    
    // Functions that occur based on events
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void gsttResponse(ofxGSTTResponseArgs& response);
};
