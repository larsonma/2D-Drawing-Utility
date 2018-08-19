/**
 * ViewContext.h - This is an interfece for the ViewContext class performing transformations.
 * Transformations are tracked in this class with the ability to undo them.
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: may 3 2018
 */

#ifndef VIEWCONTEXT_H
#define VIEWCONTEXT_H

#include <cmath>

#include "matrix.h"
#include "Shape.h"

#define PI 3.14159265359

class Shape;

class ViewContext {
    public:

        /* 
        * This is a constructor for the ViewContext object. The ViewContext object requires that the origin
        * be specified so that transformations can be made around it.
        * Inputs:
        *      x - x coordinate of origin
        *      y - y coordinate of origin
        *      z - z coordinate of origin
        * Outputs:
        *      Pointer to ViewContext Object
        */
        ViewContext(int x, int y, int z);

        /* 
        * This function handles destroying the ViewContext object, with its underyling data structures.
        * Inputs:
        *      gc - GraphicsContext object
        * Outputs:
        *      none
        */        
        ~ViewContext();

        /* 
        * This function converts the device coordinates observed on the screen into model coordinates. Essentially,
        * this undoes the transformations that have been applied to the screen so that the shape can be properly
        * created with its correct coordinates.
        * 
        * Inputs:
        *      shapeVerticies - matrix containing the verticies of the shape.
        * Outputs:
        *      matrix* - pointer to transformed matrix object
        */
        matrix* deviceToModel(matrix*);

        /* 
        * This function converts the model coorinates of a shape to the device coordinates that will be displayed
        * on the screen. This applies the transformation matrix to the shape.
        * 
        * Inputs:
        *      shapeVerticies - matrix containing the verticies of the shape.
        * Outputs:
        *      matrix* - pointer to transformed matrix object
        */
        matrix* modelToDevice(matrix*);

        /* 
        * This function applies a scale to the exisiting transformation matrix, while simultaneously updating the 
        * inverse transformation matrix.
        * 
        * Inputs:
        *      a - scale factor in x direction
        *      b - scale factor in y direction
        * Outputs:
        *      none
        */
        void scale(double a, double b);

        /* 
        * This function applies a rotate matrix to the exisiting transformation matrix, while simultaneously updating the 
        * inverse transformation matrix.
        * 
        * Inputs:
        *      deg - degrees to rotate
        * Outputs:
        *      none
        */
        void rotate(double theta);

        /* 
        * This function applies a translation matrix to the exisiting transformation matrix, while simultaneously updating the 
        * inverse transformation matrix.
        * 
        * Inputs:
        *      x - translation in the x direction
        *      y - translation in the y direction
        * Outputs:
        *      none
        */
        void translate(int x, int y);

        /* 
        * This function resets the transformation matricies so that the view is in its original form
        * 
        * Inputs:
        *      none
        * Outputs:
        *      none
        */
        void reset();

    private:
        matrix* toModelCoordinates;
        matrix* toDeviceCoordinates;

        matrix* translateToOrigin;
        matrix* translateFromOrigin;
};

#endif