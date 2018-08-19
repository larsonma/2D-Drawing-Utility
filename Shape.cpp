/**
 * Shape.cpp - This is an implementation of the Shape class
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: april 19 2018
 */

#include "Shape.h"
#include "Line.h"
#include "Triangle.h"

/* 
 * This is a constructor for a Shape object. A default shape is created.
 * 
 * Parameters:
 * 	none
 */
Shape::Shape(){
    color = new Color();
    verticies = new matrix(4,1);
}

/* 
 * This is a constructor for a Shape object with location specified
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 */
Shape::Shape(unsigned int x0, unsigned int y0)
:Shape()
{
    (*verticies)[0][0] = x0;
    (*verticies)[1][0] = y0;
}

/* 
 * This is a constructor for a Line object in which color is specified
 * 
 * Parameters:
 *  red - color value for red
 *  green - color value for green
 *  blue - color value for blue
 */
Shape::Shape(int red, int green, int blue)
{
    color = new Color(red, green, blue);
    verticies = new matrix(4,1);
}

/* 
 * This is a constructor for a Line object in which color is specified as a single integer
 * 
 * Parameters:
 *  color - integer value for color
 */
Shape::Shape(unsigned int color){
    this->color = new Color(color);
    verticies = new matrix(4,1);
}

/* 
 * This is a constructor for a Shape object with location specified and a color specified as
 * a single integer value.
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  color - integer value of color
 */
Shape::Shape(unsigned int x0, unsigned int y0, unsigned int color)
:Shape()
{
    this->color = new Color(color);
}


/* 
 * This is a constructor for a Shape object with location and color specified
 * 
 * Parameters:
 * 	x0 - x coordinate of first point
 *  y0 - y coordinate of first point
 *  red - color value for red
 *  green - color value for green
 *  blue - color value for blue
 */
Shape::Shape(unsigned int x0, unsigned int y0, int red, int green, int blue)
:Shape()
{
    color = new Color(red, green, blue);
}

/* 
 * This is a copy constructor for a Shape object.
 * 
 * Parameters:
 * 	from - reference to line that will be copied.
 */
Shape::Shape(const Shape& from){
    color = new Color((*from.color).getRed(), (*from.color).getGreen(), (*from.color).getBlue());
    verticies = new matrix(*from.verticies);
}

/* 
 * This is a destructor for a Shape object.
 * 
 * Parameters:
 * 	none
 */
Shape::~Shape(){
    delete color;
    delete verticies;
}

/* 
 * This method will print the properties of the Shape to an output stream
 * 
 * Parameters:
 * 	os - reference to the output stream
 * 
 * Returns:
 *  output stream being passed in
 */
std::ostream& Shape::out(std::ostream& os) const {
    os << "Begin Shape Properties" << std::endl;
    os << "\tColor: " << color->color << std::endl;
    os << "\tLocation: " << (*verticies)[0][0] << "," << (*verticies)[1][0] << std::endl;
    os << "End Shape Properties" << std::endl;

    return os;
}

/* 
 * Reads in a Shape from file and assigns the shape properties. A shape object will already
 * be instantiated when this is called, so a shape object is not returned.
 * 
 * Parameters:
 * 	iStream - reference to input file
 * 
 * Returns:
 *  void
 */
void Shape::in(std::istream& iStream){
    while(!iStream.eof()){
        std::string line;

        std::getline(iStream, line);

        if(line.find("Color:") != std::string::npos){
            color->color = std::stoi(line.substr(8,line.length()));
        } else if(line.find("End Shape Properties") != std::string::npos){
            return;
        }
    }
}

/* 
 * Overrides default = operator for easy assignment of shape properties
 * 
 * Parameters:
 * 	from - reference to shape that will be copied
 * 
 * Returns:
 *  void
 */
void Shape::operator=(const Shape& from){
    delete color;
    delete verticies;

    color = new Color((*from.color).color);
    verticies = new matrix(*from.verticies);
}

/* 
 * Returns a copy of the shape verticies. A copy is returned to prevent manipulation of the
 * shape properties.
 * 
 * Parameters:
 * 	none
 * 
 * Returns:
 *  pointer to matrix object holding the shape verticies.
 */
matrix* Shape::getVerticies(){
    return new matrix(*verticies);
}

/* 
 * This is a default constructor for a Color object. Color becomes white
 * 
 * Parameters:
 *  noen
 */
Shape::Color::Color(){
    color = 0xFFFFFF;
}

/* 
 * This is a constructor for a Line object in which color is specified as hex or an integer.
 * 
 * Parameters:
 *  color - integer value of color
 */
Shape::Color::Color(unsigned int color){
    this->color = color;
}

/* 
 * This is a constructor for a Line object in which color is specified as rgb
 * 
 * Parameters:
 *  red - color value for red
 *  green - color value for green
 *  blue - color value for blue
 */
Shape::Color::Color(int red, int green, int blue){
    if(red > 255 || green > 255 || blue > 255) return;
    color = (red<<16) + (green<<8) + blue;
}

/* 
 * Returns red value of color
 * 
 * Parameters:
 *  none
 * 
 * Returns:
 *  red value as integer
 */
int Shape::Color::getRed(){
    return (color&0xFF0000) >> 16;
}

/* 
 * Returns green value of color
 * 
 * Parameters:
 *  none
 * 
 * Returns:
 *  green color as integer
 */
int Shape::Color::getGreen(){
    return (color&0x00FF00) >> 8;
}

/* 
 * Returns blue value of color
 * 
 * Parameters:
 *  none
 * 
 * Returns:
 *  blue color as integer
 */
int Shape::Color::getBlue(){
    return (color&0x0000FF);
}

/* 
 * This is a global function not associated with a class which allows shapes to be read from
 * file and instantiated.
 * 
 * Parameters:
 *  in - reference to input stream
 * 
 * Returns:
 *  vector of shape objects
 */
std::vector<Shape*> readShapesFromFile(std::istream& in){
    std::vector<Shape*> shapes;

    while(!in.eof()){
        std::string line;

        std::getline(in, line);

        if(line.find("Begin Line") != std::string::npos){
            shapes.push_back(Line::in(in));
        }else if(line.find("Begin Triangle") != std::string::npos){
            shapes.push_back(Triangle::in(in));
        }else if(line.find("End Shapes") != std::string::npos){
            return shapes;
        }
    }
    return shapes;
}


