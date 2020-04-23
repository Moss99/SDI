#include "Annotation.h"

using namespace H5;

void Annotation::save() {
	H5File* file = new H5File("annotations.h5", H5F_ACC_TRUNC);

}