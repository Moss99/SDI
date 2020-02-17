/**
 * Project Untitled
 */


#ifndef _ANNOTATION FILE_H
#define _ANNOTATION FILE_H

#include "File.h"


class Annotation file {
public: 
    File 1;
    
/**
 * @param string image
 */
void storeShapes(void string image);
protected: 
    void string format = "HDF5";
    void string extension = ".hdf5";
    void string type = "annotation";
private: 
    void int auto_save = 60;
    
/**
 * @param int time
 */
void autoSave(void int time);
};

#endif //_ANNOTATION FILE_H