#include "Annotation.h"
#include "highfive/H5File.hpp"
#include "highfive/H5DataSet.hpp"
#include "highfive/H5DataSpace.hpp"

using namespace HighFive;

const std::string FILE_NAME("save.annotations");
const std::string DATASET_NAME("dset");
const size_t size_dataset = 20;

void Annotation::save(std::vector<int> image) {
    File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);
    DataSet dataset = file.createDataSet<std::string>(DATASET_NAME, DataSpace::From(image));
    dataset.write(image);
}

void Annotation::open(std::string path) {
    File file(path, File::ReadOnly);
    std::vector<std::string> readData;
    DataSet dataset = file.getDataSet(DATASET_NAME);
    dataset.read(readData);
}