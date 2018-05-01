# Project Proposal

## Speech Recognition Media Player


### Summary:
The goal of this project is to incorporate the top 20 Billboard Chart songs into a media player that displays all the songs in the data directory of the project at the left of the window. The metadata of the 20 songs will be stored in a JSON file that will be used to create Song objects that will be displayed on the left of the GUI. The user will then be able to click on the songs on the left to play them, or use their voice to send commands to the program. There will be a specific 'push to talk' button to do this. The voice commands can include "play xyz", which would play the desired song , "shuffle" to shuffle through the songs, and other commands as well.

### Libraries:
I will be using a couple libraries for this project, including [ofxDatGui](https://github.com/braitsch/ofxDatGui), [ofxGSTT](https://github.com/fx-lange/ofxGSTT), [JSON for Modern C++](https://github.com/nlohmann/json#serialization--deserialization). Furthermore, ofxGSTT uses these additional libraries: [ofxJSON](https://github.com/jeffcrouse/ofxJSON) and [ofxSSL](https://github.com/fx-lange/ofxSSL). JSON for Modern C++ will be used to possibly store and format or read metadata as well. ofxGSTT will be used for the speech recognitions, as proposed above. This will also make use of ofxSSL and ofxJSON. More libraries may or may not be added.

### Relevant Experience:
I have previous experience in working with song metadata, and I plan on translating part of this logic to C++. Furthermore, I've had experience in designing UIs in Android, which I feel will help me while desigining my openFrameworks interface.




