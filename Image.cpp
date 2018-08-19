/**
 * Image.cpp - This is an implementation of the Image class which
 *             provides a container for shapes representing an
 *             image.
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: april 19 2018
 */

#include "Image.h"

/* This is default constructor for creating an Image object.
 * 
 * Parameters:
 *      none
 */
Image::Image(){}

/* This is a copy constructor for the image class. This will create deep copies of all
 * shapes in the image class
 * 
 * Parameters:
 * 	im - reference to an image object.
 */
Image::Image(const Image& im){
    std::vector<Shape*> temp;

    for(std::vector<Shape*>::const_iterator iter(im.shapes.begin()); iter != im.shapes.end(); ++iter){
        temp.push_back(&(*iter)->clone());
    }

    shapes = temp;
}

/* This is a destructor for an Image object. This will call destructors for all
 * shapes in an object.
 * 
 * Parameters:
 * 	none
 */
Image::~Image(){
    erase();
}

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
Image& Image::operator=(const Image& im){
    for(std::vector<Shape*>::const_iterator iter(shapes.begin()); iter != shapes.end(); ++iter){
        delete *iter;
    }

    for(std::vector<Shape*>::const_iterator iter(im.shapes.begin()); iter != im.shapes.end(); ++iter){
        shapes.push_back(&(*iter)->clone());
    }

    return *this;
}

/* 
 * Adds a shape to the Image container.
 * 
 * Parameters:
 * 	shape - pointer to shape object.
 * 
 * Returns
 *   void
 */
void Image::add(Shape * shape){
    shapes.push_back(&shape->clone());
}

/* 
 * This method will iterate through the Image container and draw each image.
 * 
 * Parameters:
 * 	gc - pointer to a graphics context object.
 * 
 * Returns: 
 *  void
 */
void Image::draw(GraphicsContext* gc, ViewContext* vc){
    gc->clear();
    for(std::vector<Shape*>::const_iterator iter(shapes.begin()); iter != shapes.end(); ++iter){
        (*iter)->draw(gc, vc);
    }
}

/* 
 * This method will print the properties of the image to an output stream
 * 
 * Parameters:
 * 	os - reference to the output stream
 * 
 * Returns:
 *  output stream being passed in
 */
std::ostream& Image::out(std::ostream& os){
    os << "Begin Image" << std::endl;
    os << "Begin Shapes" << std::endl;
    for(std::vector<Shape*>::const_iterator iter(shapes.begin()); iter != shapes.end(); ++iter){
        (*iter)->out(os);
    }
    os << "End Shapes" << std::endl;
    os << "End Image" << std::endl;
    
    return os;
}

/* 
 * Reas in image from file and instantiates a Image object with shapes found in file.
 * 
 * Parameters:
 * 	iStream - reference to input file
 * 
 * Returns:
 *  pointer to image object
 */
Image* Image::in(std::istream& iStream){
    Image * image;
    while(!iStream.eof()){
        std::string line;

        std::getline(iStream, line);


        if(line.find("Begin Image") != std::string::npos){
            image = new Image();
            image->shapes = readShapesFromFile(iStream);
        } else if(line.find("End Image") != std::string::npos){
            return image;
        }
    }
    return image;
}

/* 
 * This method will erase all shapes in the Image container.
 * 
 * Parameters:
 * 	none
 * 
 * Returns:
 *   void
 */
void Image::erase(){
    for(std::vector<Shape*>::const_iterator iter(shapes.begin()); iter != shapes.end(); ++iter){
        delete *iter;
    }

    shapes.erase(shapes.begin(), shapes.end());
}



