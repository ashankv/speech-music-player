//
//  json_helper.hpp
//  SpeechMusicPlayer
//
//  Created by Ashank Verma on 4/20/18.
//

#ifndef json_helper_hpp
#define json_helper_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "song.hpp"

// Helper class for parsing JSON file
class JSONHelper {
  
public:
    
    // JSON helper method
    std::vector<Song> GetSongsFromJSONFile(std::string& file_name);
};

#endif /* json_helper_hpp */
