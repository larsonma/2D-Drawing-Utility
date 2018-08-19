/**
 * Image.h- Interface for Image class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: April 12 2018
 */

#ifndef _IMAGE_H
#define _IMAGE_H

#include <vector>

#include "matrix.h"
#include "gcontext.h"
#include "Colors.h"
#include "Shape.h"
#include "ViewContext.h"

class Image{

    public:
        /* This is default constructor for creating an Image object.
        * 
        * Parameters:
        *      none
        */
        Image();

        /* This is a copy constructor for the image class. This will create deep copies of all
        * shapes in the image class
        * 
        * Parameters:
        * 	im - reference to an image object.
        */
        Image(const Image& from);

        /* This is a destructor for an Image object. This will call destructors for all
        * shapes in an object.
        * 
        * Parameters:
        * 	none
        */
        ~Image();

        /* 
        * This is an override of the equal operator which allows for easy assignment of Image objects.
        * This will return a copy of the image to the right of the operand.
        * 
        * Parameters:
        * 	im - reference to image that will be copied
        * 
        * Returns:
        *  a reference to an Image.
        */
        Image& operator=(const Image& from);

        /* 
        * Adds a shape to the Image container.
        * 
        * Parameters:
        * 	shape - pointer to shape object.
        * 
        * Returns
        *   void
        */
        void add(Shape* shape);

        /* 
        * This method will iterate through the Image container and draw each image.
        * 
        * Parameters:
        * 	gc - pointer to a graphics context object.
        * 
        * Returns: 
        *  void
        */
        void draw(GraphicsContext* gc, ViewContext* vc);

        /* 
        * This method will print the properties of the image to an output stream
        * 
        * Parameters:
        * 	os - reference to the output stream
        * 
        * Returns:
        *  output stream being passed in
        */
        std::ostream& out(std::ostream& os);

        /* 
        * Reas in image from file and instantiates a Image object with shapes found in file.
        * 
        * Parameters:
        * 	iStream - reference to input file
        * 
        * Returns:
        *  pointer to image object
        */
        static Image* in(std::istream& iStream);

        /* 
        * This method will erase all shapes in the Image container.
        * 
        * Parameters:
        * 	none
        * 
        * Returns:
        *   void
        */
        void erase();

    private:
        std::vector<Shape*> shapes;

};

#endif
