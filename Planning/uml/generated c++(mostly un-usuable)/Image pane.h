/**
 * Project Untitled
 */


#ifndef _IMAGE PANE_H
#define _IMAGE PANE_H

class Image pane {
public: 
    void float mouse_x;
    void float mouse_y;
    void string image;
    void vector string annotations;
    
/**
 * @param string image
 */
void displayImage(void string image);
    
/**
 * @param annotations
 */
void displayAnnotations(void annotations);
};

#endif //_IMAGE PANE_H