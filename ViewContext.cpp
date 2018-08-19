/**
 * ViewContext.cpp - This is an implementation of a class for performing transformations.
 * Transformations are tracked in this class with the ability to undo them.
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: may 3 2018
 */

#include "ViewContext.h"

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
ViewContext::ViewContext(int x, int y, int z){
    toModelCoordinates = new matrix(4,4);
    toDeviceCoordinates = new matrix(4,4);
    translateToOrigin = new matrix(4,4);
    translateFromOrigin = new matrix(4,4);

    for(int i = 0; i < 4; i++){
        (*toModelCoordinates)[i][i] = 1.0;
        (*toDeviceCoordinates)[i][i] = 1.0;
        (*translateToOrigin)[i][i] = 1.0;
        (*translateFromOrigin)[i][i] = 1.0;
    }

    (*translateToOrigin)[0][3] = -x;
    (*translateToOrigin)[1][3] = -y;
    (*translateFromOrigin)[0][3] = x;
    (*translateFromOrigin)[1][3] = y;
}

/* 
 * This function handles destroying the ViewContext object, with its underyling data structures.
 * Inputs:
 *      gc - GraphicsContext object
 * Outputs:
 *      none
 */
ViewContext::~ViewContext(){
    delete toModelCoordinates;
    delete toDeviceCoordinates;
    delete translateToOrigin;
    delete translateFromOrigin;
}

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
matrix* ViewContext::deviceToModel(matrix* shapeVerticies){
    matrix* deviceCoordinates = new matrix(4,3);

    *deviceCoordinates = (*toModelCoordinates * *shapeVerticies);

    return deviceCoordinates;
}

/* 
 * This function converts the model coorinates of a shape to the device coordinates that will be displayed
 * on the screen. This applies the transformation matrix to the shape.
 * 
 * Inputs:
 *      shapeVerticies - matrix containing the verticies of the shape.
 * Outputs:
 *      matrix* - pointer to transformed matrix object
 */
matrix* ViewContext::modelToDevice(matrix* shapeVerticies){
    matrix* deviceCoordinates = new matrix(4,3);

    *deviceCoordinates = (*toDeviceCoordinates * *shapeVerticies);

    return deviceCoordinates;
}

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
void ViewContext::scale(double a, double b){
    matrix scale(4,4);
    matrix undoScale(4,4);

    scale[0][0] = a;
    scale[1][1] = b;
    scale[2][2] = 1;
    scale[3][3] = 1;

    undoScale[0][0] = 1/a;
    undoScale[1][1] = 1/b;
    undoScale[2][2] = 1;
    undoScale[3][3] = 1;

    *toDeviceCoordinates = *translateFromOrigin * scale * *translateToOrigin * *toDeviceCoordinates;
    *toModelCoordinates = *toModelCoordinates * *translateFromOrigin * undoScale * *translateToOrigin;
}

/* 
 * This function applies a rotate matrix to the exisiting transformation matrix, while simultaneously updating the 
 * inverse transformation matrix.
 * 
 * Inputs:
 *      deg - degrees to rotate
 * Outputs:
 *      none
 */
void ViewContext::rotate(double theta_deg){
    matrix rotate(4,4);
    matrix undoRotate(4,4);

    double theta = theta_deg * (PI/180.0);

    rotate[0][0] = std::cos(theta);
    rotate[0][1] = -1 * std::sin(theta);
    rotate[1][0] = std::sin(theta);
    rotate[1][1] = std::cos(theta);
    rotate[2][2] = 1;
    rotate[3][3] = 1;

    undoRotate[0][0] = std::cos(-theta);
    undoRotate[0][1] = -1 * std::sin(-theta);
    undoRotate[1][0] = std::sin(-theta);
    undoRotate[1][1] = std::cos(-theta);
    undoRotate[2][2] = 1;
    undoRotate[3][3] = 1;

    *toDeviceCoordinates = (*translateFromOrigin * rotate * *translateToOrigin * *toDeviceCoordinates);
    *toModelCoordinates = (*toModelCoordinates * *translateFromOrigin * undoRotate * *translateToOrigin);  
}

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
void ViewContext::translate(int x, int y){
    matrix translate = matrix::identity(4);
    matrix undoTranslate = matrix::identity(4);

    translate[0][3] = x;
    translate[1][3] = y;

    undoTranslate[0][3] = -x;
    undoTranslate[1][3] = -y;

    *toDeviceCoordinates = (*translateFromOrigin * translate * *translateToOrigin * *toDeviceCoordinates);
    *toModelCoordinates = (*toModelCoordinates * *translateFromOrigin * undoTranslate * *translateToOrigin);
}

/* 
 * This function resets the transformation matricies so that the view is in its original form
 * 
 * Inputs:
 *      none
 * Outputs:
 *      none
 */
void ViewContext::reset(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            (*toModelCoordinates)[i][j] = 0.0;
            (*toDeviceCoordinates)[i][j] = 0.0;
        }
        (*toModelCoordinates)[i][i] = 1.0;
        (*toDeviceCoordinates)[i][i] = 1.0;
    }
}
