#pragma once
#include <string>
#include <filesystem>
#include <vector>

/// Class for getting image names from a filepath.
class imageFolder {
public:
	std::vector <std::string> loadImages(std::string); //Gets all the names of the folder files in a given filepath.
	std::string fullPath(std::string, std::string);
private:
	bool validImage(std::string); // Checks if a given file is an image file.
};
