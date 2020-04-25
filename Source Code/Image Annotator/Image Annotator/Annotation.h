#pragma once
#include <string>
#include <vector>

class Annotation {
public:
	void save(std::vector<std::vector<int>> &);
	std::vector<std::vector<int>> open(std::string);
};