//
//  json_helper.cpp
//  SpeechMusicPlayer
//
//  Created by Ashank Verma on 4/20/18.
//

#include "json_helper.hpp"

using json = nlohmann::json;

std::vector<Song> JSONHelper::GetSongsFromJSONFile(std::string& file_name) {

    std::vector<Song> songs;
    std::ifstream input(file_name);
    
    if (input.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File Does Not Exist" << std::endl;
        std::vector<Song> empty_list;
        return empty_list;
    }
    
    json billboard_json = json::parse(input);
    
    for (json song_json : billboard_json["songs"]) {
        
        std::string name = song_json["name"].get<std::string>();
        std::string artist = song_json["artist"].get<std::string>();
        std::string image_name = song_json["image_name"].get<std::string>();
        std::string audio_file_name = song_json["audio_file_name"].get<std::string>();
        
        Song song(name, artist, image_name, audio_file_name);
        
        songs.push_back(song);
    }
    
    return songs;
}
