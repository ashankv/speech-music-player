#include "ofApp.h"


//--------------------------------------------------------------
void mediaPlayer::setup(){
    ofSetWindowTitle("Speech Recognition Media Player");
    
    PopulateSongs();
    PopulateImages();
    
    
}

//--------------------------------------------------------------
void mediaPlayer::update(){

}

//--------------------------------------------------------------
void mediaPlayer::draw(){
    song_images_[0].draw(30, 30, 50, 50);
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
