/**
 * Project Untitled
 */


#ifndef _FILE_H
#define _FILE_H

#include "Annotation file.h"
#include "Class file.h"
#include "Image.h"


class File {
public: 
    Annotation file 0..*;
    Class file 0..*;
    Image 0..*;
    
void Operation4();
protected: 
    void string file_name;
    
/**
 * @param string location
 * @param string name
 * @param string format
 * @param string extension
 */
void save(void string location, void string name, void string format, void string extension);
    
/**
 * @param string location
 * @param string type
 */
void open(void string location, void string type);
    
/**
 * @param string new_name
 */
void rename(void string new_name);
};

#endif //_FILE_H