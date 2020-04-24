#include "Annotation.h"
#include "highfive/H5File.hpp"
#include "highfive/H5DataSet.hpp"
#include "highfive/H5DataSpace.hpp"

using namespace HighFive;

const std::string FILE_NAME("save.annotations");
const std::string DATASET_NAME("dset");
const size_t size_dataset = 20;

const int imageNamePos = 0;
const int noShapesPos = 1;

void Annotation::save(std::string imageName) {
    //temp
    int noShapes = 3;
    std::string type = "square";
    int noPoints = 4;
    int point = 300;
    //
    File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);
    std::vector<std::string> image;
    image.push_back(imageName);
    image.push_back(std::to_string(noShapes));
    for (int i = 0; i < noShapes; i++) {
        image.push_back(type);
        for (int j = 0; j < noPoints; j++) {
            image.push_back(std::to_string(point));
        }
        image.push_back(";"); //identify separate shapes
    }
    DataSet dataset = file.createDataSet<std::string>(DATASET_NAME, DataSpace::From(image));
    dataset.write(image);
}

void Annotation::open(std::string path) {
    File file(path, File::ReadOnly);
    std::vector<std::string> readData;
    DataSet dataset = file.getDataSet(DATASET_NAME);
    dataset.read(readData);

    std::string imageName = readData.at(imageNamePos);
    int noShapes = std::stoi(readData.at(noShapesPos));
    for (int i = 2; i < readData.size(); i++) {
        
    }
}