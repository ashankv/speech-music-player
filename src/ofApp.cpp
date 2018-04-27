#include "ofApp.h"



//--------------------------------------------------------------
void mediaPlayer::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("Speech Recognition Media Player");
    
    PopulateSongs();
    PopulateImages();
}

//--------------------------------------------------------------
void mediaPlayer::update(){

}

//--------------------------------------------------------------
void mediaPlayer::draw(){
    DrawImagesAndButtons();
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

void mediaPlayer::PopulateImages() {
    
    for (int i = 0; i < songs_.size(); i++) {
        ofImage image;
        string image_name = "images/" + songs_[i].GetImageName();
        image.load(image_name);
        song_images_.push_back(image);
    }
}

void mediaPlayer::DrawImagesAndButtons() {
    
    int current_img_y_val = INITIAL_IMG_Y_VAL;
    int current_text_y_val = INITIAL_TEXT_Y_VAL;
    int current_img_x_val = INITIAL_IMG_X_VAL;
    int current_text_x_val = INITIAL_TEXT_X_VAL;
    
    for (int i = 0; i < songs_.size(); i++) {
        song_images_[i].draw(current_img_x_val, current_img_y_val, IMG_SIZE_SCALER, IMG_SIZE_SCALER);
        
        string song_name = songs_[i].GetName();
        string song_description = "\n" + songs_[i].GetArtist();
        
        ofxDatGuiButton* button = new ofxDatGuiButton(song_name);
        button->setWidth(200);
        button->setPosition(current_text_x_val, current_text_y_val);
        button->setTheme(new ofxDatGuiThemeAqua());
        button->draw();
        ofDrawBitmapString(song_description, current_text_x_val, current_text_y_val);
        
        
        current_img_y_val += IMAGE_SPACE_VAL;
        current_text_y_val += TEXT_SPACE_VAL;
        
        if (i == (songs_.size() / 2) - 1) {
            current_img_x_val = IMG_X_OFFSET;
            current_text_x_val = TEXT_X_OFFSET;
            current_img_y_val = INITIAL_IMG_Y_VAL;
            current_text_y_val = INITIAL_TEXT_Y_VAL;
        }
        
    }
}

void mediaPlayer::onButtonEvent(ofxDatGuiButtonEvent e) {
    cout << e.target->getLabel() << " was clicked!"  << endl;
}
