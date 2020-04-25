#include "Annotation.h"
#include "highfive/H5File.hpp"
#include "highfive/H5DataSet.hpp"
#include "highfive/H5DataSpace.hpp"

using namespace HighFive;

const std::string FILE_NAME("save.annotations");
const std::string DATASET_NAME("dset");

void Annotation::save(std::vector<std::vector<int>> &shapes) {
    std::vector<int> flat;
    for (int x = 0; x < shapes.size(); x++) { //flatten out vector
        for (int y = 0; y < shapes[x].size(); y++) {
            flat.push_back(shapes[x][y]);
        }
        flat.push_back(-1); //denote new shape (assumes -ve is safe to use)
    }
    File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);
    DataSet dataset = file.createDataSet<int>(DATASET_NAME, DataSpace::From(flat));
    dataset.write(flat);
}

std::vector<std::vector<int>> Annotation::open(std::string path) {
    File file(path, File::ReadOnly);
    std::vector<int> readData;
    DataSet dataset = file.getDataSet(DATASET_NAME);
    dataset.read(readData);
    std::vector<std::vector<int>> unflat;
    std::vector<int> points;
    for (int i = 0; i < readData.size(); i++) { //un-flatten vector
        if (readData[i] == -1) {
            unflat.push_back(points);
            points.clear();
        }
        else {
            points.push_back(readData[i]);
        }
    }
    return unflat;
}