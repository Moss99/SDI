#include <iostream>
#include <vector>

int bsearch(std::vector<std::string>v1, std::string target, int first, int last);
int bsearch(std::vector<std::string>v1, std::string target);


int bsearch(std::vector<std::string>v1, std::string target) {
    return bsearch(v1, target, 0, v1.size() - 1);
}

int bsearch(std::vector<std::string> v1, std::string target, int first, int last) {
    int mid;
    if (first <= last) {
        int mid = first + ((last - first) / 2);
        if (v1[mid] == target) {
            return mid;
        }
        else if (v1[mid] > target) {
            return bsearch(v1, target, first, mid - 1);
        }
        else {
            return bsearch(v1, target, mid + 1, last);
        }
        return -1;
    }
}

void printVector(std::vector<std::string>input) {
    for (int r = 0; r < input.size(); r++) {
        std::cout << input[r] << ' ';
    }
    std::cout << std::endl;
}

std::vector<std::string> insertionSort(std::vector<std::string>v1) {
    std::vector<std::string> v2;
    std::string temp;
    int e;

    for (int i = 1; i < v1.size(); i++) {
        temp = v1[i];
        e = i;
        while (e > 0 && temp < v1[e - 1]) {
            v1[e] = v1[e - 1];
            v1[e - 1] = temp;
            e--;
        }
    }

    v2 = v1;
    return v2;
}
