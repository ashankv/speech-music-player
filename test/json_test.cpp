//
//  json_test.cpp
//  SpeechMusicPlayer
//
//  Created by Ashank Verma on 4/30/18.
//

#include "catch.hpp"

// Tests for JSONHelper class
// JSONHelper is the only class without UI integration to be tested

TEST_CASE("Parse JSON From Non-Existent File Path Test") {
    
    JSONHelper helper;
    std::vector<Song> songs = helper.GetSongsFromJSONFile("asdf");
    
    REQUIRE(0 == songs.size());
}

TEST_CASE("Parse JSON From Incorrect File Path Test") {
    
    JSONHelper helper;
    std::vector<Song> songs = helper.GetSongsFromJSONFile("bin/billboard_songs.json");
    
    REQUIRE(0 == songs.size());
}

TEST_CASE("Parse JSON From Correct File Path Test") {
    
    std::string file_path = "/Users/ashank/Documents/of_v0.9.8_osx_release/apps/myApps/SpeechMusicPlayer/bin/data/billboard_songs.json";
    JSONHelper helper;
    std::vector<Song> songs = helper.GetSongsFromJSONFile(file_path);
    
    REQUIRE(20 == songs.size());
    
    REQUIRE("Nice For What" == songs[0].GetName());
    REQUIRE("Drake" == songs[0].GetArtist());
    REQUIRE("NiceForWhat.png" == songs[0].GetImageName());
    REQUIRE("Nice For What.mp3" == songs[0].GetAudioFileName());
}
