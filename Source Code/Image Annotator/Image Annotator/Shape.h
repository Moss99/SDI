#pragma once

/// Creates a new shape used for drawing onto the main form
class shape{
private:
	std::vector<int> points;
public:
	void addPoints(int, int); ///< Sets the initial point of the shape 
							  ///<
	std::vector<int> getPoints();
};

inline void shape::addPoints(int x, int y) {
	points.push_back(x);
	points.push_back(y);
}

inline std::vector<int> shape::getPoints() {
	return points;
}
