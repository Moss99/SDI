#include "imageFolder.h"

std::vector <std::string> imageFolder::loadImages(std::string filepath) {
	std::vector <std::string> images;
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(filepath)) { //iterate through files in directory
		fs::path p = entry.path();
		std::string path = p.string();
		bool nameFound = false;
		int nameLen = path.length();
		std::string image;
		while(nameFound == false) {
			if (path[nameLen] == '\\') {
				nameFound = true;
			}
			else {
				image = path[nameLen] + image;
				nameLen--;
			}
		}
		if (validImage(image) == true) {
			images.push_back(image);
		}
	}
	return images;
}

bool imageFolder::validImage(std::string imageName) {
	bool valid = false;
	int extPos = 4;
	int extLen = 3;
	std::string ext = imageName.substr((imageName.length() - extPos),extLen);
	if (ext == "png" || ext == "jpg") {
		valid = true;
	}
	return valid;
}