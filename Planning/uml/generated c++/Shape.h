/**
 * Project Untitled
 */


#ifndef _SHAPE_H
#define _SHAPE_H

#include "Polygon.h"
#include "Trapezium.h"
#include "Quadrilateral.h"
#include "Triangle.h"
#include "Class.h"


class Shape {
public: 
    void string type;
    void float size_x;
    void float size_y;
    void vector float points;
    void float rotation;
    void string name;
    void vector string shapes;
    void vector string classes;
    void int shape_count;
    Polygon 0..*;
    Trapezium 0..*;
    Quadrilateral 0..*;
    Triangle 0..*;
    Class 1..*;
    
/**
 * @param float x
 * @param float y
 * @param string name
 */
void move(void float x, void float y, void string name);
    
/**
 * @param string name
 */
void visualise(void string name);
    
/**
 * @param float x
 * @param float y
 * @param string name
 */
void resize(void float x, void float y, void string name);
    
/**
 * @param string name
 */
void copy(void string name);
    
/**
 * @param string name
 */
void paste(void string name);
    
/**
 * @param string name
 */
void delete(void string name);
    
/**
 * @param float x
 * @param float y
 */
void select(void float x, void float y);
    
/**
 * @param string image
 */
void countSapes(void string image);
};

#endif //_SHAPE_H