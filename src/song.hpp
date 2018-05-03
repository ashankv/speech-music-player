//
//  song.hpp
//  SpeechMusicPlayer
//
//  Created by Ashank Verma on 4/20/18.
//

#ifndef song_hpp
#define song_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "ofMain.h"

// Song class, which has a name, artist, image name, and audio file name
class Song {
    
private:
    
    // Song metadata
    std::string name_;
    std::string artist_;
    std::string image_name_;
    std::string audio_file_name_;
    
    // Sound player associated with each song
    ofSoundPlayer sound_player_;
    
public:
    
    // Constructor for Song object
    Song(std::string& name, std::string& artist, std::string& image_name, std::string& audio_file_name):name_(name), artist_(artist), image_name_(image_name), audio_file_name_(audio_file_name) {};
    
    // Getters for metadata and sound player
    std::string GetName();
    std::string GetArtist();
    std::string GetImageName();
    std::string GetAudioFileName();
    ofSoundPlayer GetSoundPlayer();
    
    // Setter for sound player
    void SetSoundPlayer(ofSoundPlayer& sound_player);
};

#endif /* song_hpp */
