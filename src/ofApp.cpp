#include "ofApp.h"



//--------------------------------------------------------------
void mediaPlayer::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("Speech Recognition Media Player");
    
    PopulateSongs();
    PopulateImagesAndSongMap();
    LoadSoundPlayers();
    SetupButtons();

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
    
    if (has_clicked_song_) {
        song_images_[current_song_index_].draw(CURRENT_SONG_IMG_X, CURRENT_SONG_IMG_Y, CURRENT_SONG_IMG_DIM, CURRENT_SONG_IMG_DIM);
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
    
    for (int i = 0; i < songs_.size(); i++) {
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

    std::string clicked_song_name = e.target->getLabel();
    current_song_index_ = song_indeces_[clicked_song_name];
    has_clicked_song_ = true;
    
    song_players_[current_song_index_].play();

    
    std::cout << current_song_index_ << std::endl;
    
}

void mediaPlayer::LoadSoundPlayers() {
    
    for (int i = 0; i < songs_.size(); i++) {
        string audio_file_name = "audio/" + songs_[i].GetAudioFileName();
        ofSoundPlayer sound_player;
        sound_player.load(audio_file_name);
        song_players_.push_back(sound_player);
    }
}
