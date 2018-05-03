//
//  song.cpp
//  SpeechMusicPlayer
//
//  Created by Ashank Verma on 4/20/18.
//

#include "song.hpp"

std::string Song::GetName() {
    return name_;
}

std::string Song::GetArtist() {
    return artist_;
}

std::string Song::GetImageName() {
    return image_name_;
}

std::string Song::GetAudioFileName() {
    return audio_file_name_;
}

ofSoundPlayer Song::GetSoundPlayer() {
    return sound_player_;
}

void Song::SetSoundPlayer(ofSoundPlayer& sound_player) {
    sound_player_ = sound_player;
}
