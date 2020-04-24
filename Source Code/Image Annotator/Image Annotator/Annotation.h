#pragma once
#include <string>
#include <vector>

class Annotation {
public:
	void save(std::vector<int> &);
	std::vector<int> open(std::string);
};