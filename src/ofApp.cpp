#include "ofApp.h"



// Setup method
void mediaPlayer::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("Speech Recognition Media Player");
    
    // Load all data, buttons, and songs
    PopulateSongs();
    PopulateImagesAndSongMap();
    LoadSoundPlayers();
    SetupButtons();
    
    // Font loading
    name_font_.load("arial.ttf", 18);
    artist_font_.load("arial.ttf", 13);
    
    // Loading media control images
    play_button_.load("images/play-button.png");
    pause_button_.load("images/pause.png");
    skip_button_.load("images/skip.png");
    previous_button_.load("images/previous.png");
}

//--------------------------------------------------------------
void mediaPlayer::update(){
    
    for (auto button : song_buttons_) {
        button->update();
    }
}

//--------------------------------------------------------------
void mediaPlayer::draw(){
    
    DrawImagesAndButtons();
    
    // Draw image of current song on the right with play/pause button and corresponding information
    if (has_clicked_song_) {
        song_images_[current_song_index_].draw(CURRENT_SONG_IMG_X, CURRENT_SONG_IMG_Y, CURRENT_SONG_IMG_DIM, CURRENT_SONG_IMG_DIM);
        string current_song_name = songs_[current_song_index_].GetName();
        string current_song_artist = songs_[current_song_index_].GetArtist();
        
        name_font_.drawString(current_song_name, CURRENT_SONG_INFO_X, CURRENT_SONG_NAME_Y);
        artist_font_.drawString(current_song_artist, CURRENT_SONG_INFO_X, CURRENT_SONG_ARTIST_Y);
        
        if (is_paused_) {
            play_button_.draw(PLAY_BTN_X, PLAY_BTN_Y, PLAY_BTN_DIM, PLAY_BTN_DIM);
        } else {
            pause_button_.draw(PLAY_BTN_X, PLAY_BTN_Y, PLAY_BTN_DIM, PLAY_BTN_DIM);
        }
        
        skip_button_.draw(SKIP_BTN_X, SKIP_CTRL_BTNS_Y, SKIP_CTRL_BTNS_DIM, SKIP_CTRL_BTNS_DIM);
        previous_button_.draw(PREVIOUS_BTN_X, SKIP_CTRL_BTNS_Y, SKIP_CTRL_BTNS_DIM, SKIP_CTRL_BTNS_DIM);
        
    }
}

//--------------------------------------------------------------
void mediaPlayer::keyPressed(int key){

}

//--------------------------------------------------------------
void mediaPlayer::keyReleased(int key){

}

//--------------------------------------------------------------
void mediaPlayer::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void mediaPlayer::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void mediaPlayer::mousePressed(int x, int y, int button){
    
    // Check to see if play/pause button is clicked
    if ((x >= PLAY_BTN_X && x <= PLAY_BTN_X + PLAY_BTN_DIM)
        && (y >= PLAY_BTN_Y && y <= PLAY_BTN_Y + PLAY_BTN_DIM) && current_song_index_ != -1) {
        
        is_paused_ = !is_paused_;
        song_players_[current_song_index_].setPaused(is_paused_);
        std::cout << "PLAY BUTTON PRESSED" << std::endl;
    }
    
    if ((x >= SKIP_BTN_X && x <= SKIP_BTN_X + SKIP_CTRL_BTNS_DIM)
        && (y >= SKIP_CTRL_BTNS_Y && y <= SKIP_CTRL_BTNS_Y + SKIP_CTRL_BTNS_DIM) && current_song_index_ != -1) {
        
        if (is_paused_) {
            is_paused_ = false;
        }
        
        song_players_[current_song_index_].stop();
        
        if (current_song_index_ != songs_.size() - 1) {
            ++current_song_index_;
            song_players_[current_song_index_].play();
        } else {
            current_song_index_ = 0;
            song_players_[0].play();
        }
        
        std::cout << "SKIP BUTTON PRESSED" << std::endl;
    }
    
    if ((x >= PREVIOUS_BTN_X && x <= PREVIOUS_BTN_X + SKIP_CTRL_BTNS_DIM)
        && (y >= SKIP_CTRL_BTNS_Y && y <= SKIP_CTRL_BTNS_Y + SKIP_CTRL_BTNS_DIM) && current_song_index_ != -1) {
        
        if (is_paused_) {
            is_paused_ = false;
        }
    
        song_players_[current_song_index_].stop();
        
        if (current_song_index_ != 0) {
            current_song_index_--;
            song_players_[current_song_index_].play();
        } else {
            current_song_index_ = songs_.size() - 1;
            song_players_[current_song_index_].play();
        }
        
        std::cout << "PREVIOUS BUTTON PRESSED" << std::endl;
    }

}

//--------------------------------------------------------------
void mediaPlayer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void mediaPlayer::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void mediaPlayer::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void mediaPlayer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void mediaPlayer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void mediaPlayer::dragEvent(ofDragInfo dragInfo){

}

void mediaPlayer::PopulateSongs() {
    std::string file_name = "/Users/ashank/Documents/of_v0.9.8_osx_release/apps/myApps/SpeechMusicPlayer/bin/data/billboard_songs.json";
    songs_ = helper_.GetSongsFromJSONFile(file_name);
}

void mediaPlayer::PopulateImagesAndSongMap() {
    
    // Iterate through each song and load the corresponding image to the image vector
    for (int i = 0; i < songs_.size(); i++) {
        
        // Add entry to map of name and index
        song_indeces_[songs_[i].GetName()] = i;
        
        ofImage image;
        string image_name = "images/" + songs_[i].GetImageName();
        image.load(image_name);
        
        song_images_.push_back(image);
    }
}

void mediaPlayer::DrawImagesAndButtons() {
    
    int current_img_y_val = INITIAL_IMG_Y_VAL;
    int current_text_y_val = INITIAL_TEXT_Y_VAL;
    int current_btn_y_val = INITIAL_BTN_Y_VAL;
    
    int current_img_x_val = INITIAL_IMG_X_VAL;
    int current_text_x_val = INITIAL_TEXT_X_VAL;
    int current_btn_x_val = INITIAL_BTN_X_VAL;
    
    // Draw/format buttons and text
    for (int i = 0; i < songs_.size(); i++) {
        song_images_[i].draw(current_img_x_val, current_img_y_val, IMG_SIZE_SCALER, IMG_SIZE_SCALER);
        
        string song_name = songs_[i].GetName();
        string song_description = "\n" + songs_[i].GetArtist();
        
        song_buttons_.at(i)->draw();
        
        ofDrawBitmapString(song_description, current_text_x_val, current_text_y_val);
        
        current_btn_y_val += BTN_SPACE_VAL;
        current_img_y_val += IMAGE_SPACE_VAL;
        current_text_y_val += TEXT_SPACE_VAL;
        
        if (i == (songs_.size() / 2) - 1) {
            current_img_x_val = IMG_X_OFFSET;
            current_text_x_val = TEXT_X_OFFSET;
            current_btn_x_val = BTN_X_OFFSET;
            
            current_btn_y_val = INITIAL_BTN_Y_VAL;
            current_img_y_val = INITIAL_IMG_Y_VAL;
            current_text_y_val = INITIAL_TEXT_Y_VAL;
        }
    }
}

void mediaPlayer::SetupButtons() {
    
    int current_btn_y_val = INITIAL_BTN_Y_VAL;
    int current_btn_x_val = INITIAL_BTN_X_VAL;
    
    for (int i = 0; i < songs_.size(); i++) {
        
        string song_name = songs_[i].GetName();
        
        ofxDatGuiButton* button = new ofxDatGuiButton(song_name);
        button->setPosition(current_btn_x_val, current_btn_y_val);
        button->setTheme(new ofxDatGuiThemeAqua());
        button->setWidth(BTN_WIDTH);
        button->onButtonEvent(this, &mediaPlayer::onButtonEvent);
        song_buttons_.push_back(button);
        
        current_btn_y_val += BTN_SPACE_VAL;
        
        if (i == (songs_.size() / 2) - 1) {
            current_btn_x_val = BTN_X_OFFSET;
            current_btn_y_val = INITIAL_BTN_Y_VAL;
        }
    }
}

void mediaPlayer::onButtonEvent(ofxDatGuiButtonEvent e) {
    cout << e.target->getLabel() << " was clicked!"  << endl;
    
    if (has_clicked_song_) {
        song_players_[current_song_index_].stop();
    }
    
    // Retrieve current song index from the button name
    std::string clicked_song_name = e.target->getLabel();
    current_song_index_ = song_indeces_[clicked_song_name];
    has_clicked_song_ = true;
    
    song_players_[current_song_index_].play();
  
    std::cout << current_song_index_ << std::endl;
}

void mediaPlayer::LoadSoundPlayers() {
    
    // Load sound players into sound player vector
    for (int i = 0; i < songs_.size(); i++) {
        string audio_file_name = "audio/" + songs_[i].GetAudioFileName();
        ofSoundPlayer sound_player;
        sound_player.load(audio_file_name);
        song_players_.push_back(sound_player);
    }
}
