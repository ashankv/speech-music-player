#include "ofApp.h"



// Setup method
void mediaPlayer::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("Speech Recognition Media Player");
    ofSetBackgroundColorHex(0x90CAF9);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Load all data, buttons, and songs
    PopulateSongs();
    PopulateImagesAndSongMap();
    LoadSoundPlayers();
    SetupButtons();
    
    // Setup GSTT addon
    SetupGSTT();
    
    // Load fonts
    name_font_.load("arial.ttf", 18);
    artist_font_.load("arial.ttf", 13);
    
    // Loading media control images
    play_button_.load("images/play-button.png");
    pause_button_.load("images/pause.png");
    skip_button_.load("images/skip.png");
    previous_button_.load("images/previous.png");
    mic_button_.load("/Users/ashank/Documents/of_v0.9.8_osx_release/apps/myApps/SpeechMusicPlayer/bin/data/images/mic-button.png");
}


// Update method called before every draw.
void mediaPlayer::update() {
    
    // Keep buttons updated
    for (auto button : song_buttons_) {
        button->update();
    }
}

/*
Draws the current state of the music player with the following logic
1. If no song is playing, then there should be nothing drawn on the right
2. If a song is playing, it's picture an information should be drawn on the right
3. If a song is playing, it's media controls should be drawn underneath it
*/
void mediaPlayer::draw(){
    
    DrawImagesAndButtons();
    
    // Draw image of current song on the right with play/pause button and corresponding information
    if (has_clicked_song_) {
        
        // Draw current song information
        song_images_[current_song_index_].draw(CURRENT_SONG_IMG_X, CURRENT_SONG_IMG_Y, CURRENT_SONG_IMG_DIM, CURRENT_SONG_IMG_DIM);
        string current_song_name = songs_[current_song_index_].GetName();
        string current_song_artist = songs_[current_song_index_].GetArtist();
        
        name_font_.drawString(current_song_name, CURRENT_SONG_INFO_X, CURRENT_SONG_NAME_Y);
        artist_font_.drawString(current_song_artist, CURRENT_SONG_INFO_X, CURRENT_SONG_ARTIST_Y);
        
        // Logic for drawing play/pause buttons
        if (is_paused_) {
            play_button_.draw(PLAY_BTN_X, PLAY_BTN_Y, PLAY_BTN_DIM, PLAY_BTN_DIM);
        } else {
            pause_button_.draw(PLAY_BTN_X, PLAY_BTN_Y, PLAY_BTN_DIM, PLAY_BTN_DIM);
        }
        
        // Draw media control buttons
        skip_button_.draw(SKIP_BTN_X, SKIP_CTRL_BTNS_Y, SKIP_CTRL_BTNS_DIM, SKIP_CTRL_BTNS_DIM);
        previous_button_.draw(PREVIOUS_BTN_X, SKIP_CTRL_BTNS_Y, SKIP_CTRL_BTNS_DIM, SKIP_CTRL_BTNS_DIM);
        mic_button_.draw(MIC_BTN_X, MIC_BTN_Y, MIC_BTN_DIM, MIC_BTN_DIM);
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

/*
Mouse pressed method based on pixel location
1. If the play button is presesd, play/pause the song accordingly
2. If the skip button is pressed, skip to the next song
3. If the previous button is pressed, go to the previous song
4. If the mic button is pressed, start the speech recognition
*/
void mediaPlayer::mousePressed(int x, int y, int button){
    
    // Check to see if play/pause button is clicked
    if ((x >= PLAY_BTN_X && x <= PLAY_BTN_X + PLAY_BTN_DIM)
        && (y >= PLAY_BTN_Y && y <= PLAY_BTN_Y + PLAY_BTN_DIM) && current_song_index_ != -1) {
        
        // Change the pause boolean to it's opposite and set the corresponding player to that boolean
        is_paused_ = !is_paused_;
        song_players_[current_song_index_].setPaused(is_paused_);
        
        std::cout << "PLAY BUTTON PRESSED" << std::endl;
    }
    
    // Check to see if skip button is clicked
    if ((x >= SKIP_BTN_X && x <= SKIP_BTN_X + SKIP_CTRL_BTNS_DIM)
        && (y >= SKIP_CTRL_BTNS_Y && y <= SKIP_CTRL_BTNS_Y + SKIP_CTRL_BTNS_DIM) && current_song_index_ != -1) {
        
        SkipButtonPressed();
    }
    
    // Check to see if previous button is clicked
    if ((x >= PREVIOUS_BTN_X && x <= PREVIOUS_BTN_X + SKIP_CTRL_BTNS_DIM)
        && (y >= SKIP_CTRL_BTNS_Y && y <= SKIP_CTRL_BTNS_Y + SKIP_CTRL_BTNS_DIM) && current_song_index_ != -1) {
        
        PreviousButtonPressed();
    }
    
    // Check to see if mic button is clicked
    if ((x >= MIC_BTN_X && x <= MIC_BTN_X + MIC_BTN_DIM)
        && (y >= MIC_BTN_Y && y <= MIC_BTN_Y + MIC_BTN_DIM) && current_song_index_ != -1) {
        
        // Change the mic turned on boolean to it's opposite
        is_mic_on_ = !is_mic_on_;
        
        is_paused_ = true;
        song_players_[current_song_index_].setPaused(is_paused_);
        
        // Start recording if the mic is on, stop otherwise
        if (is_mic_on_) {
            gstt_.startRecording();
        } else {
            gstt_.stopRecording();
        }
    
        std::cout << "MIC BUTTON PRESSED" << std::endl;
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

// Method that populates song vector using JSON helper
void mediaPlayer::PopulateSongs() {
    std::string file_name = "/Users/ashank/Documents/of_v0.9.8_osx_release/apps/myApps/SpeechMusicPlayer/bin/data/billboard_songs.json";
    songs_ = helper_.GetSongsFromJSONFile(file_name);
}

// Populate images and map of song name to index
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

// Helper draw method for buttons and images
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

// Button setup for each song in the song vector
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
        
        // Start new column if we reach 10 songs
        if (i == (songs_.size() / 2) - 1) {
            current_btn_x_val = BTN_X_OFFSET;
            current_btn_y_val = INITIAL_BTN_Y_VAL;
        }
    }
}

// On Button Click method for all the buttons
void mediaPlayer::onButtonEvent(ofxDatGuiButtonEvent e) {
    
    std::cout << e.target->getLabel() << " was clicked!"  << std::endl;
    
    // If a current song is playing, stop that song
    if (has_clicked_song_) {
        
        if (is_paused_) {
            is_paused_ = false;
        }
        
        song_players_[current_song_index_].stop();
    }
    
    // Retrieve current song index from the button name
    std::string clicked_song_name = e.target->getLabel();
    current_song_index_ = song_indeces_[clicked_song_name];
    has_clicked_song_ = true;
    
    song_players_[current_song_index_].play();
    song_players_[current_song_index_].setPaused(is_paused_);
}

// Loading sound players for each sound file method
void mediaPlayer::LoadSoundPlayers() {
    
    // Load sound players into sound player vector
    for (int i = 0; i < songs_.size(); i++) {
        string audio_file_name = "audio/" + songs_[i].GetAudioFileName();
        ofSoundPlayer sound_player;
        sound_player.load(audio_file_name);
        song_players_.push_back(sound_player);
    }
}

// GSTT Response method for processing speech
void mediaPlayer::gsttResponse(ofxGSTTResponseArgs& response){
    cout << "Response: " << response.msg << endl;
    cout << "With confidence: " << ofToString(response.confidence) << endl;
    float tProcessingTime = (response.tReceived - response.tSend)/1000.f;
    cout << "processing time(seconds): " << ofToString(tProcessingTime) << endl;
 
    std::string response_str = response.msg;
    std::string command = "";
    
    // Get the first command
    for (char& c : response_str) {
        if (c == ' ') {
            break;
        }
        command += c;
    }
    
    // Convert command to lowercase
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    
    if (command == "play") {
        
        // Resume playback if the command is play
        if (response_str.size() == 4) {
            
            is_paused_ = false;
            song_players_[current_song_index_].setPaused(is_paused_);
            
        } else {
            
            // Get the song to be played and convert to lowercase
            std::string song_to_play = response_str.substr(5);
            std::transform(song_to_play.begin(), song_to_play.end(), song_to_play.begin(), ::tolower);
            song_to_play.erase(remove_if(song_to_play.begin(), song_to_play.end(), ::ispunct), song_to_play.end());

            // Iterate through songs to see if any names match up
            for (Song song : songs_) {
                
                // Convert song names to lowercase and remove any punctuation
                std::string song_name = song.GetName();
                std::transform(song_name.begin(), song_name.end(), song_name.begin(), ::tolower);
                song_name.erase(remove_if(song_name.begin(), song_name.end(), ::ispunct), song_name.end());
                
                // Play the song to play if it matches with any of the songs
                if (song_to_play == song_name) {
                    song_players_[current_song_index_].stop();
                    current_song_index_ = song_indeces_[song.GetName()];
                    
                    is_paused_ = false;
                    
                    song_players_[current_song_index_].play();
                    song_players_[current_song_index_].setPaused(is_paused_);
                 }
            }
        }
    } else if (command == "pause") {
        is_paused_ = true;
        song_players_[current_song_index_].setPaused(is_paused_);
    } else if (command == "skip") {
        SkipButtonPressed();
    } else if (command == "previous") {
        PreviousButtonPressed();
    } else if (command == "shuffle") {
        ShuffleCommand();
    }
}

// Method for performing skip action
void mediaPlayer::SkipButtonPressed() {
    
    // If playback is currently paused, set it to unpaused
    if (is_paused_) {
        is_paused_ = false;
    }
    
    song_players_[current_song_index_].stop();
    
    // If the current song isn't the last song, play the next song, otherwise play the 1st song
    if (current_song_index_ != songs_.size() - 1) {
        ++current_song_index_;
        song_players_[current_song_index_].play();
        song_players_[current_song_index_].setPaused(is_paused_);
        
    } else {
        current_song_index_ = 0;
        song_players_[0].play();
        song_players_[current_song_index_].setPaused(is_paused_);
        
    }
    
    std::cout << "SKIP BUTTON PRESSED" << std::endl;
}

// Method for performing previous action
void mediaPlayer::PreviousButtonPressed() {
    
    // If playback is currently paused, set it to unpaused
    if (is_paused_) {
        is_paused_ = false;
    }
    
    song_players_[current_song_index_].stop();
    
    // If the current song isn't the first song, play the previous song, otherwise play the last song
    if (current_song_index_ != 0) {
        --current_song_index_;
        song_players_[current_song_index_].play();
        song_players_[current_song_index_].setPaused(is_paused_);
    } else {
        current_song_index_ = songs_.size() - 1;
        song_players_[current_song_index_].play();
        song_players_[current_song_index_].setPaused(is_paused_);
        
    }
    
    std::cout << "PREVIOUS BUTTON PRESSED" << std::endl;
}

// Method for performing shuffle action
void mediaPlayer::ShuffleCommand() {
    
    song_players_[current_song_index_].stop();
    
    // Get random index
    int random_index = rand() % songs_.size();
    current_song_index_ = random_index;
    is_paused_ = false;
    
    // Play the random song
    song_players_[current_song_index_].play();
    song_players_[current_song_index_].setPaused(is_paused_);
}

// Setup method for GSTT
void mediaPlayer::SetupGSTT() {
    
    // Initialize ofSoundstream
    int sampleRate = 44100;
    int bufferSize = 256;
    int nChannels = 1;

    sound_stream_.printDeviceList();
    sound_stream_.setup(0, nChannels, sampleRate, bufferSize, 4);
    
    // Initialize ofxGSTT
    gstt_.setup(sampleRate,nChannels,"en-us","AIzaSyBKIGETtjhXWjXyjq78LB6bbWX0cPR4478");//check the README for generating an API key
    gstt_.setAutoRecording(is_auto_recording_);
    gstt_.setVolumeThreshold(volume_threshold_);

    sound_stream_.setInput(gstt_);
    
    // Add listener to OF
    ofAddListener(ofxGSTTTranscriptionThread::gsttApiResponseEvent, this, &mediaPlayer::gsttResponse);
    
}
