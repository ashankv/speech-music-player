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

**Problem 4:**
Only 10/20 images are being displayed on the screen. I need to figure out how to make a scroll view on the left side of the view.

**Solution:**
I found that implementing a scroll view on the left side would be extremely difficult, as libraries dont allow for different UI elements to go into the scroll view. Instead, I put 10 songs in 2 columns in a clean fashion that displays all the information correctly.

**Problem 5:**
I need an efficient way of implementing image buttons. Either I can make my own custom image button class that allows me to click on the image to play the song, or I can specify pixel regions where when mousePressed is called, it should play the song.

**Solution:**
Instead of implementing image buttons, I made the title of the song into buttons using the ofxDatGui library. These have yet to be formatted correctly.

**Problem 6:**
To make a cleaner looking UI, I added ofxDatGui to my project. However, whenever I made a button, the text of the button was not showing up.

**Solution:**
I found out that the font assets from ofxDatGui weren't being compiled by the project. After following the steps at this [StackOverFlow post](https://stackoverflow.com/questions/4882572/how-to-bundle-an-openframeworks-application-in-xcode-relative-resource-linking/17159123#17159123), I was able to fix this issue.

**Updates as of 4/28:**
The hardest issues I have encountered thus far are Problem 4, 5, and 6, which were all UI related. Formatting everything using ofxDatGui was the most challenging part for me thus far. Implementing the functions of the buttons to play the songs have been fairly straightforward. As of now, all the buttons and song information are being displayed correctly, and each button is linked to a specific player which plays the song. I have also implemented play/pause/skip/previous buttons that plays, pauses, and skips correctly.

**Problem 7:**
The ofxSpeech library that I originally planned to use was abandoned and last used 5 years ago. I found another library called ofxGSTT, which uses ofxSSL and ofxJSON to perform an API request to Google's Speech Recognition API. However, these libraries were last updated around 3 years ago. There are a lot of errors with these libraries that I need to update based on the current openFrameworks settings.

**Solution:**
There were several steps involved in getting the ofxGSTT library to correctly perform API requests and get the correct response. They are listed below.
    1. I had to find a new version of the curlbuild.h file in the ofxSSL library. After hours of researching, I found an online [Gist](https://gist.github.com/deltheil/7fe3da9c7074fffa81cf) to have a curlbuild.h file that compiles with modern settings.
    2. I then had to import the libcurl library into my Xcode project. I did this by following the steps of this [Apple forum post]( https://discussions.apple.com/thread/4740717).
    3. Next, I had to import the libsndfile library which I downloaded using brew install. Since this wasn't a library that I specifically had the files downloaded for, I had to navigate to the /usr/local/Cellar/libsndfile/ path on my computer and find the files there to manually import.
    4. Finally, while making the API request, it kept saying that I did not have permission to use the certificate file cacert.pem. I went into the ofxSSL library and changed the path of this file to the absolute path. This finally allowed me to make successful requests.
This part of the project took up the majority of my time in the last phase.

**Updates as of 4/29:**
After fixing problem 7, I was able to successfully get a response translated from my voice, which I then parsed and executed the following commands:
    1. _play [song_name]_, plays the song name that was spoken.
    2. _play_, resumes playback.
    3. _pause_, pauses playback.
    4. _skip_, skips to the next song.
    5. _previous_, goes to the previous song.
    6. _shuffle_, plays a random song.
These are all controlled on click of the mic button in the UI.
    
