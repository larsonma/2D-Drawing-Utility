/**
 * Line.cpp - This is an implementation of the Line class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: april 19 2018
 */

#include "Line.h"

/* 
 * This is a constructor for a Line object.
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  x1 - x coordinate of second point
 *  y2 - y coordinate of second point
 */
Line::Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1){
    matrix endPoints(4,2);
    (endPoints)[0][0] = x0;
    (endPoints)[1][0] = y0;
    (endPoints)[0][1] = x1;
    (endPoints)[1][1] = y1;

    (endPoints)[3][0] = 1;
    (endPoints)[3][1] = 1;

    *verticies = endPoints;
}

/* 
 * This is a constructor for a Line object.
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  x1 - x coordinate of second point
 *  y2 - y coordinate of second point
 *  red - color value for red
 *  green - color value for green
 *  blue - color value for blue
 */
Line::Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,int red, int green, int blue)
:Shape(red,green,blue)
{
    matrix endPoints(4,2);
    (endPoints)[0][0] = x0;
    (endPoints)[1][0] = y0;
    (endPoints)[0][1] = x1;
    (endPoints)[1][1] = y1;

    (endPoints)[3][0] = 1;
    (endPoints)[3][1] = 1;

    *verticies = endPoints;
}

/* 
 * This is a constructor for a Line object.
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  x1 - x coordinate of second point
 *  y2 - y coordinate of second point
 *  color - integer color value.
 */
Line::Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
:Shape(color)
{
    matrix endPoints(4,2);
    (endPoints)[0][0] = x0;
    (endPoints)[1][0] = y0;
    (endPoints)[0][1] = x1;
    (endPoints)[1][1] = y1;

    (endPoints)[3][0] = 1;
    (endPoints)[3][1] = 1;

    *verticies = endPoints;
}

/* 
 * This is a copy constructor for a Line object.
 * 
 * Parameters:
 * 	from - reference to line that will be copied.
 */
Line::Line(const Line& from)
:Shape(from)
{}

/* 
 * This is a destructor for a Line object.
 * 
 * Parameters:
 * 	none
 */
Line::~Line(){}

/* 
 * This method will draw the line object
 * 
 * Parameters:
 * 	gc - pointer to graphics context object
 * 
 * Returns:
 *  none
 */
void Line::draw(GraphicsContext* gc, ViewContext* vc){
    gc->setColor(color->color);

    // std::cout << "Model" << std::endl;
    // verticies->out(std::cout);

    matrix* deviceCoord = vc->modelToDevice(this->verticies);

    // std::cout << "Device" << std::endl;
    // deviceCoord->out(std::cout);

    gc->drawLine((*deviceCoord)[0][0], (*deviceCoord)[1][0], (*deviceCoord)[0][1], (*deviceCoord)[1][1]);
    delete deviceCoord;
}

/* 
 * This method will print the properties of the line to an output stream
 * 
 * Parameters:
 * 	os - reference to the output stream
 * 
 * Returns:
 *  output stream being passed in
 */
std::ostream& Line::out(std::ostream& os) const {
    os << "Begin Line" << std::endl;
    os << "Begin Line Properties" << std::endl;
    os << "\tBegin Verticies" << std::endl;
    os << "\t\tv1: " << (*verticies)[0][0] << "," << (*verticies)[1][0] << std::endl;
    os << "\t\tv2: " << (*verticies)[0][1] << "," << (*verticies)[1][1] << std::endl;
    os << "\tEnd Verticies" << std::endl;
    os << "End Line Properties" << std::endl;
    Shape::out(os);
    os << "End Line" << std::endl;

    return os;
}

/* 
 * Reads in a line from file and instantiates and returns the line object
 * 
 * Parameters:
 * 	iStream - reference to input file
 * 
 * Returns:
 *  pointer to line object
 */
Line* Line::in(std::istream& iStream){
    std::string v1, v2;
    Line * lineObj;
    while(!iStream.eof()){
        std::string line;

        std::getline(iStream, line);

        if(line.compare("Begin Shape Properties") == 0){
            lineObj->Shape::in(iStream);
        } else if(line.compare("\tBegin Verticies") == 0){
            std::getline(iStream, v1);
            std::getline(iStream, v2);

            int x0 = std::stoi(v1.substr(6,v1.find(",")-6));
            int y0 = std::stoi(v1.substr(v1.find(",")+1,v1.length()));
            int x1 = std::stoi(v2.substr(6,v2.find(",")-6));
            int y1 = std::stoi(v2.substr(v2.find(",")+1,v2.length()));

            lineObj = new Line(x0,y0,x1,y1);
        } else if(line.compare("End Line") == 0){
            return lineObj;
        }
    }
    return lineObj;
}

/* 
 * Creates a copy of a line object, but returns a refernce to the line as a shape reference
 * 
 * Parameters:
 * 	none
 * 
 * Returns:
 *  line object as a shape reference
 */
Shape& Line::clone(){
    return *(new Line(*this));
}

/* 
 * Overrides default = operator for easy assignment of line objects
 * 
 * Parameters:
 * 	from - reference to line that will be copied
 * 
 * Returns:
 *  reference to line object
 */
Line& Line::operator=(const Line& from){
    delete verticies;
    verticies = new matrix(*from.verticies);

    Shape::operator=(from);
    return *this;
}
