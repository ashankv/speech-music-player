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

class Song {
    
private:
    std::string name_;
    std::string artist_;
    std::string image_name_;
    
public:
    std::string GetName();
    std::string GetArtist();
    std::string GetImageName();
    
};

#endif /* song_hpp */
