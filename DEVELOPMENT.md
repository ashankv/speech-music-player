# Development

**Problem 1:**
After importing the JSON for Modern C++ library into the project, I kept getting a file not found error when I tried to include the json.hpp file from the library.

**Solution:**
I went to the Build Settings fo the project where I added a path to the Header Search Paths. This path was: _$(OF_PATH)/addons/JsonModernCpp_. After adding this path, I found that the include for the json.hpp file was still not working, and this was because I was including _"../addons/JsonModernCpp/json.hpp", when I just had to include json.hpp only. This fixed the problem.

**Problem 2:**
I wiped my old directory and created a new project folder, but for some reason Git was not working with this new directory, and when I pushed something, it deleted everything from my repository.

**Solution:**
I realized I was still in my old directory in Terminal, so I had to reinitialize everything in the new project folder. It unfortunately wiped 2 of my previous commits for the project.

**Problem 3:**
For some reason, "../bin/data/billboard_songs.json" wasn't working as a viable path for std::ifstream, although I had done the same in NaiveBayes when reading from the file.

**Solution:**
After a long time, I ended up using the absolute path of the JSON file for the std::ifstream, and this finally worked.

**Problem 4:** _(Unresolved)_
Only 10/20 images are being displayed on the screen. I need to figure out how to make a scroll view on the left side of the view.

**Problem 5:** _(Unresolved)_
I need an efficient way of implementing image buttons. Either I can make my own custom image button class that allows me to click on the image to play the song, or I can specify pixel regions where when mousePressed is called, it should play the song.
