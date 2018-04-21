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

class JSONHelper {
  
public:
    std::vector<Song> GetSongsFromJSONFile(std::string& file_name);
};

#endif /* json_helper_hpp */
