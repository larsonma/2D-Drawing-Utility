/**
 * Triangle.cpp - This is an implementation of the Triangle class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: april 19 2018
 */
#include "Triangle.h"

/* 
 * This is a constructor for a Triangle object using a matrix as verticies.
 * 
 * Parameters:
 * 	verticies - pointer to the verticies object to be used as triangle coordinates
 */
Triangle::Triangle(matrix* verticies){
    (*verticies)[3][0] = 1;
    (*verticies)[3][1] = 1;
    (*verticies)[3][2] = 1;
    
    *this->verticies = *verticies;
}

/* 
 * This is a constructor for a Triangle object created with a matrix and rgb colors
 * 
 * Parameters:
 * 	verticies - pointer to the verticies object to be used as triangle coordinates
 *  red - color value for red
 *  green - color value for green
 *  blue - color value for blue
 */
Triangle::Triangle(matrix* verticies, int red, int green, int blue)
:Shape(red,green,blue)
{
    (*verticies)[3][0] = 1;
    (*verticies)[3][1] = 1;
    (*verticies)[3][2] = 1;

    *this->verticies = *verticies;
}

Triangle::Triangle(matrix* verticies, unsigned int color)
:Shape(color)
{
    (*verticies)[3][0] = 1;
    (*verticies)[3][1] = 1;
    (*verticies)[3][2] = 1;

    *this->verticies = *verticies;

}

/* 
 * This is a constructor for a Triangle object with points specified by coordinates
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  x1 - x coordinate of second point
 *  y1 - y coordinate of second point
 *  x2 - x coordinate of thrid point
 *  y2 - y coordinate of third point
 */
Triangle::Triangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
    initTriangleVerticies(x0,y0,x1,y1,x2,y2);
}

/* 
 * This is a constructor for a Triangle object with points specified by coordinates and color specified by rgb
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  x1 - x coordinate of second point
 *  y1 - y coordinate of second point
 *  x2 - x coordinate of thrid point
 *  y2 - y coordinate of third point
 *  red - color value for red
 *  green - color value for green
 *  blue - color value for blue
 */
Triangle::Triangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, int red, int green, int blue)
:Shape(red,green,blue)
{    
    initTriangleVerticies(x0,y0,x1,y1,x2,y2);
}

/* 
 * This is a copy constructor for a Triangle object.
 * 
 * Parameters:
 * 	from - reference to Triangle that will be copied.
 */
Triangle::Triangle(const Triangle& from)
:Shape(from)
{}

/* 
 * This is a destructor for a Triangle object.
 * 
 * Parameters:
 * 	none
 */
Triangle::~Triangle(){}

/* 
 * This method will draw the Triangle object
 * 
 * Parameters:
 * 	gc - pointer to graphics context object
 * 
 * Returns:
 *  none
 */
void Triangle::draw(GraphicsContext* gc, ViewContext* vc){
    gc->setColor(color->color);
    matrix* deviceCoord = vc->modelToDevice(this->verticies);
    gc->drawLine((*deviceCoord)[0][0], (*deviceCoord)[1][0], (*deviceCoord)[0][1], (*deviceCoord)[1][1]);
    gc->drawLine((*deviceCoord)[0][1], (*deviceCoord)[1][1], (*deviceCoord)[0][2], (*deviceCoord)[1][2]);
    gc->drawLine((*deviceCoord)[0][2], (*deviceCoord)[1][2], (*deviceCoord)[0][0], (*deviceCoord)[1][0]);
    delete deviceCoord;
}

/* 
 * This method will print the properties of the Triangle to an output stream
 * 
 * Parameters:
 * 	os - reference to the output stream
 * 
 * Returns:
 *  output stream being passed in
 */
std::ostream& Triangle::out(std::ostream& os) const{
    os << "Begin Triangle" << std::endl;
    os << "Begin Triangle Properties" << std::endl;
    os << "\tBegin Verticies" << std::endl;
    os << "\t\tv1: " << (*verticies)[0][0] << "," << (*verticies)[1][0] << std::endl;
    os << "\t\tv2: " << (*verticies)[0][1] << "," << (*verticies)[1][1] << std::endl;
    os << "\t\tv3: " << (*verticies)[0][2] << "," << (*verticies)[1][2] << std::endl;
    os << "\tEnd Verticies" << std::endl;
    os << "End Triangle Properties" << std::endl;
    Shape::out(os);
    os << "End Triangle" << std::endl;

    return os;
}

/* 
 * Reads in a Triangle from file and instantiates and returns the Triangle object
 * 
 * Parameters:
 * 	iStream - reference to input file
 * 
 * Returns:
 *  pointer to Triangle object
 */
Triangle* Triangle::in(std::istream& iStream){
    std::string v1, v2, v3;
    Triangle * triangleObj;
    while(!iStream.eof()){
        std::string line;

        std::getline(iStream, line);

        if(line.compare("Begin Shape Properties") == 0){
            triangleObj->Shape::in(iStream);
        } else if(line.compare("\tBegin Verticies") == 0){
            std::getline(iStream, v1);
            std::getline(iStream, v2);
            std::getline(iStream, v3);

            int x0 = std::stoi(v1.substr(6,v1.find(",")-6));
            int y0 = std::stoi(v1.substr(v1.find(",")+1,v1.length()));
            int x1 = std::stoi(v2.substr(6,v2.find(",")-6));
            int y1 = std::stoi(v2.substr(v2.find(",")+1,v2.length()));
            int x2 = std::stoi(v3.substr(6,v3.find(",")-6));
            int y2 = std::stoi(v3.substr(v3.find(",")+1,v3.length()));


            triangleObj = new Triangle(x0,y0,x1,y1,x2,y2);
        } else if(line.compare("End Triangle") == 0){
            return triangleObj;
        }
    }
    return triangleObj;
}

/* 
 * Creates a copy of a Triangle object, but returns a refernce to the Triangle as a shape reference
 * 
 * Parameters:
 * 	none
 * 
 * Returns:
 *  Triangle object as a shape reference
 */
Shape& Triangle::clone(){
    return *(new Triangle(*this));
}

/* 
 * Overrides default = operator for easy assignment of Triangle objects
 * 
 * Parameters:
 * 	from - reference to Triangle that will be copied
 * 
 * Returns:
 *  reference to Triangle object
 */
Triangle& Triangle::operator=(const Triangle& from){
    *verticies = *from.verticies;
    Shape::operator=(from);
    return *this;
}

/* 
 * Helper function for initializing verticies
 */
void Triangle::initTriangleVerticies(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2){
    matrix _verticies(4,3);
    
    _verticies[0][0] = x0;
    _verticies[1][0] = y0;
    _verticies[0][1] = x1;
    _verticies[1][1] = y1;
    _verticies[0][2] = x2;
    _verticies[1][2] = y2;

    _verticies[3][0] = 1;
    _verticies[3][1] = 1;
    _verticies[3][2] = 1;

    *verticies = _verticies;
}