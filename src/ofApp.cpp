#include "ofApp.h"

// Setup method
void mediaPlayer::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("Speech Recognition Media Player");
    ofSetBackgroundColorHex(BACKGROUND_HEX_COLOR);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Load all data, buttons, and songs
    PopulateSongsAndMap();
    PopulateImagesAndSoundPlayers();
    
    // Setup UI / Speech elements
    SetupButtons();
    SetupGSTT();
    
    // Load fonts, mic sounds, and media control images
    LoadFonts();
    LoadMicSounds();
    LoadMediaControlImages();
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
    
    info_font_.drawString("* Press 'P' to play or pause the current song!\n* Press 'T' to toggle push to talk!", KEY_INFO_X, KEY_INFO_Y);
    
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
        
        info_font_.drawString("Push to Talk! Once you are\ndone, click this button again.\nCommands: play [song name],\npause, skip, previous, shuffle.", TALK_INFO_X, TALK_INFO_Y);
    }
}

/*
 Executes function based on key pressed:
 1. If 'P' is pressed, pause or play playback accordingly.
 2. If 'T' is prssed, toggle push to talk.
 */
void mediaPlayer::keyPressed(int key) {
    
    int upper_key = toupper(key);
    
    if (upper_key == 'P' && has_clicked_song_) {
        
        // Change the pause boolean to it's opposite and set the corresponding player to that boolean
        is_paused_ = !is_paused_;
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
        
    } else if (upper_key == 'T') {
        MicButtonPressed();
    }
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
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
        
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
        
        MicButtonPressed();
    }
    
}

// Method that populates song vector using JSON helper
void mediaPlayer::PopulateSongsAndMap() {
    
    std::string file_name = ABS_PATH + "billboard_songs.json";
    songs_ = helper_.GetSongsFromJSONFile(file_name);
    
    for (int i = 0; i < songs_.size(); i++) {
        // Add entry to map of name and index
        song_indeces_[songs_[i].GetName()] = i;
    }
}

// Populate images and map of song name to index
void mediaPlayer::PopulateImagesAndSoundPlayers() {
    
    // Iterate through each song and load the corresponding image to the image vector
    for (int i = 0; i < songs_.size(); i++) {
        
        ofImage image;
        std::string image_name = "images/" + songs_[i].GetImageName();
        image.load(image_name);
        
        ofSoundPlayer sound_player;
        std::string audio_file_name = "audio/" + songs_[i].GetAudioFileName();
        sound_player.load(audio_file_name);
        
        songs_[i].SetSoundPlayer(sound_player);
        song_images_.push_back(image);
    }
}

// Button setup for each song in the song vector
void mediaPlayer::SetupButtons() {
    
    int current_btn_y_val = INITIAL_BTN_Y_VAL;
    int current_btn_x_val = INITIAL_BTN_X_VAL;
    
    for (int i = 0; i < songs_.size(); i++) {
        
        std::string song_name = songs_[i].GetName();
        
        ofxDatGuiButton* button = new ofxDatGuiButton(song_name);
        
        button->setPosition(current_btn_x_val, current_btn_y_val);
        button->setTheme(new ofxDatGuiThemeAqua());
        button->setWidth(BTN_WIDTH);
        button->onButtonEvent(this, &mediaPlayer::onButtonEvent);
        
        song_buttons_.push_back(button);
        
        current_btn_y_val += VERT_SPACE_VAL;
        
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
        
        songs_[current_song_index_].GetSoundPlayer().stop();
    }
    
    // Retrieve current song index from the button name
    std::string clicked_song_name = e.target->getLabel();
    current_song_index_ = song_indeces_[clicked_song_name];
    has_clicked_song_ = true;
    
    songs_[current_song_index_].GetSoundPlayer().play();
    songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
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
        
        std::string song_name = songs_[i].GetName();
        std::string song_description = "\n" + songs_[i].GetArtist();
        
        song_buttons_.at(i)->draw();
        
        ofDrawBitmapString(song_description, current_text_x_val, current_text_y_val);
        
        current_btn_y_val += VERT_SPACE_VAL;
        current_img_y_val += VERT_SPACE_VAL;
        current_text_y_val += VERT_SPACE_VAL;
        
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

// GSTT Response method for processing speech
void mediaPlayer::gsttResponse(ofxGSTTResponseArgs& response){
    
    // Print out response details
    cout << "Response: " << response.msg << endl;
    cout << "With Confidence: " << ofToString(response.confidence) << endl;
    float processing_time = (response.tReceived - response.tSend) / TIME_SCALER;
    cout << "Processing Time (seconds): " << ofToString(processing_time) << endl;
    
    
    std::string speech_input = response.msg; // Speech input
    std::string command = ""; // First word spoken in input
    
    // Get the first command
    for (char& c : speech_input) {
        if (c == ' ') {
            break;
        }
        command += c;
    }
    
    // Convert command to lowercase
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    
    if (command == "play") {
        
        // Resume playback if the command is play
        if (speech_input.size() == PLAY_TXT_SIZE) {
            
            is_paused_ = false;
            songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
            
        } else {
            
            // Get the song to be played, convert to lowercase, and remove punctuation
            std::string song_to_play = speech_input.substr(PLAY_PARAMETER_INDEX);
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
                    
                    if (has_clicked_song_) {
                        songs_[current_song_index_].GetSoundPlayer().stop();
                    } else {
                        has_clicked_song_ = true;
                    }
                    
                    current_song_index_ = song_indeces_[song.GetName()];
                    
                    is_paused_ = false;
                    
                    songs_[current_song_index_].GetSoundPlayer().play();
                    songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
                }
            }
        }
    } else if (command == "pause") {
        is_paused_ = true;
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
    } else if (command == "skip") {
        SkipButtonPressed();
    } else if (command == "previous") {
        PreviousButtonPressed();
    } else if (command == "shuffle") {
        ShuffleCommand();
    }
}

// Setup method for GSTT
void mediaPlayer::SetupGSTT() {
    
    // Initialize ofSoundstream
    sound_stream_.printDeviceList();
    sound_stream_.setup(0, CHANNELS, SAMPLE_RATE, BUFFER_SIZE, NUM_BUFFERS);
    
    // Initialize ofxGSTT with generated Google Speech API key
    gstt_.setup(SAMPLE_RATE, CHANNELS,"en-us","AIzaSyBKIGETtjhXWjXyjq78LB6bbWX0cPR4478");
    gstt_.setAutoRecording(false);
    gstt_.setVolumeThreshold(VOLUME_THRESHOLD);
    
    sound_stream_.setInput(gstt_);
    
    // Add listener to OF
    ofAddListener(ofxGSTTTranscriptionThread::gsttApiResponseEvent, this, &mediaPlayer::gsttResponse);
}

void mediaPlayer::MicButtonPressed() {
    
    // Change the mic turned on boolean to it's opposite
    is_mic_on_ = !is_mic_on_;
    
    if (has_clicked_song_) {
        is_paused_ = true;
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
    }
    
    // Start recording if the mic is on, stop otherwise
    if (is_mic_on_) {
        mic_open_.play();
        gstt_.startRecording();
    } else {
        gstt_.stopRecording();
        mic_close_.play();
    }
    
    std::cout << "MIC BUTTON PRESSED" << std::endl;
}

// Method for performing skip action
void mediaPlayer::SkipButtonPressed() {
    
    // If playback is currently paused, set it to unpaused
    if (is_paused_) {
        is_paused_ = false;
    }
    
    songs_[current_song_index_].GetSoundPlayer().stop();
    
    // If the current song isn't the last song, play the next song, otherwise play the 1st song
    if (current_song_index_ != songs_.size() - 1) {
        ++current_song_index_;
        songs_[current_song_index_].GetSoundPlayer().play();
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
        
    } else {
        current_song_index_ = 0;
        songs_[current_song_index_].GetSoundPlayer().play();
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
    }
    
    std::cout << "SKIP BUTTON PRESSED" << std::endl;
}

// Method for performing previous action
void mediaPlayer::PreviousButtonPressed() {
    
    // If playback is currently paused, set it to unpaused
    if (is_paused_) {
        is_paused_ = false;
    }
    
    songs_[current_song_index_].GetSoundPlayer().stop();
    
    // If the current song isn't the first song, play the previous song, otherwise play the last song
    if (current_song_index_ != 0) {
        --current_song_index_;
        songs_[current_song_index_].GetSoundPlayer().play();
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
    } else {
        current_song_index_ = songs_.size() - 1;
        songs_[current_song_index_].GetSoundPlayer().play();
        songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
        
    }
    
    std::cout << "PREVIOUS BUTTON PRESSED" << std::endl;
}

// Method for performing shuffle action
void mediaPlayer::ShuffleCommand() {
    
    songs_[current_song_index_].GetSoundPlayer().stop();
    
    // Get random index
    int random_index = rand() % songs_.size();
    current_song_index_ = random_index;
    is_paused_ = false;
    
    // Play the random song
    songs_[current_song_index_].GetSoundPlayer().play();
    songs_[current_song_index_].GetSoundPlayer().setPaused(is_paused_);
}

// Function for loading all the fonts of the application
void mediaPlayer::LoadFonts() {
    name_font_.load(ABS_PATH + "AlegreyaSans-Bold.ttf", NAME_FONT_SIZE);
    artist_font_.load(ABS_PATH + "AlegreyaSans-BoldItalic.ttf", ARTIST_FONT_SIZE);
    info_font_.load(ABS_PATH + "RobotoCondensed-Regular.ttf", INFO_FONT_SIZE);
}

// Function for loading the mic sounds
void mediaPlayer::LoadMicSounds() {
    mic_open_.load(ABS_PATH + "audio/Open Siri.mp3");
    mic_close_.load(ABS_PATH + "audio/Close Siri.mp3");
}

// Function for loading media control images
void mediaPlayer::LoadMediaControlImages() {
    play_button_.load("images/play-button.png");
    pause_button_.load("images/pause.png");
    skip_button_.load("images/skip.png");
    previous_button_.load("images/previous.png");
    mic_button_.load(ABS_PATH + "images/mic-button.png");
}
