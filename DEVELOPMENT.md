# Development

**Problem 1:**
After importing the JSON for Modern C++ library into the project, I kept getting a file not found error when I tried to include the json.hpp file from the library.

**Solution:**
I went to the Build Settings fo the project where I added a path to the Header Search Paths. This path was: _$(OF_PATH)/addons/JsonModernCpp_. After adding this path, I found that the include for the json.hpp file was still not working, and this was because I was including _"../addons/JsonModernCpp/json.hpp", when I just had to include json.hpp only. This fixed the problem.
