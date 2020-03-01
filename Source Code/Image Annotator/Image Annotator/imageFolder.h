#pragma once
#include <string>
#include <filesystem>
#include <vector>

class imageFolder {
public:
	std::vector <std::string> loadImages(std::string);
private:
	bool validImage(std::string);
};
