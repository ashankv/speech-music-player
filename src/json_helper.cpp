//
//  json_helper.cpp
//  SpeechMusicPlayer
//
//  Created by Ashank Verma on 4/20/18.
//

#include "json_helper.hpp"

// JSON For Modern C++
using json = nlohmann::json;

// Creates a vector of songs given a JSON file name
std::vector<Song> JSONHelper::GetSongsFromJSONFile(std::string& file_name) {

    std::vector<Song> songs;
    std::ifstream input(file_name);
    
    // Empty file edge case
    if (input.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File Does Not Exist" << std::endl;
        std::vector<Song> empty_list;
        return empty_list;
    }
    
    // All JSON in one object
    json billboard_json = json::parse(input);
    
    // Iterate through each JSON object in array
    for (json song_json : billboard_json["songs"]) {
        
        // Get attributes of song
        std::string name = song_json["name"].get<std::string>();
        std::string artist = song_json["artist"].get<std::string>();
        std::string image_name = song_json["image_name"].get<std::string>();
        std::string audio_file_name = song_json["audio_file_name"].get<std::string>();
        
        // Create song from JSON values
        Song song(name, artist, image_name, audio_file_name);
        
        songs.push_back(song);
    }
    
    return songs;
}
