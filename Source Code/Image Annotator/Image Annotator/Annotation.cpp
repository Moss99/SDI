#include "Annotation.h"
#include "highfive/H5File.hpp"
#include "highfive/H5DataSet.hpp"
#include "highfive/H5DataSpace.hpp"

using namespace HighFive;

const std::string FILE_NAME("save.annotations");
const std::string DATASET_NAME("dset");

void Annotation::save(std::vector<int> &shapes) {
    File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);
    DataSet dataset = file.createDataSet<int>(DATASET_NAME, DataSpace::From(shapes));
    dataset.write(shapes);
}

std::vector<int> Annotation::open(std::string path) {
    File file(path, File::ReadOnly);
    std::vector<int> readData;
    DataSet dataset = file.getDataSet(DATASET_NAME);
    dataset.read(readData);
    return readData;
}