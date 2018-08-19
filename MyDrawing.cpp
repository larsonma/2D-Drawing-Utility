/**
 * MyDrawing.cpp - Implementation of event handler for sceen events
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: may 3 2018
 */

#include "MyDrawing.h"
#include "gcontext.h"
#include "Line.h"
#include "Triangle.h"

#include <iostream>
#include <string>

const std::string filename = "image.txt";

/* 
 * This is a constructor for a MyDrawing object
 * Inputs:
 *      vc - ViewContext object for applying transformations.
 */
MyDrawing::MyDrawing(ViewContext* vc){
    this->vc = vc;
    mouseState = Mouse::RELEASED;
    mode = Mode::POINT;
    color = GraphicsContext::WHITE;
    rubberBandMode = false;
    image = new Image();
    x0 = x1 = y0 = y1 = 0;
    m1 = new matrix(4,3);
    (*m1)[3][0] = 1;
    (*m1)[3][1] = 1;
    (*m1)[3][2] = 1;
    clicks = 0;
    return;
}

/* 
 * This is a Destructor for a MyDrawing object
 * Inputs:
 *      none
 */
MyDrawing::~MyDrawing(){
    delete image;
    delete m1;
}

/* 
 * This function handles the exposure event. When this happens, the image on the screen is 
 * erased and then redrawn.
 * Inputs:
 *      gc - GraphicsContext object
 * Outputs:
 *      none
 */
void MyDrawing::paint(GraphicsContext* gc){
    gc->clear();
    image->draw(gc,vc);
}

/* 
 * This function handles the button down event. When this happens, a pixel is added to the 
 * screen and the state of the drawing process is updated.
 * Inputs:
 *      gc - GraphicsContext object
 *      button - integer key for the button pressed
 *      x - x coordinate of button press
 *      y - y coordinate of button press
 * Outputs:
 *      none
 */
void MyDrawing::mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y){
    if(clicks == 0){
        (*m1)[0][clicks] = x0 = x1 = x;
        (*m1)[1][clicks] = y0 = y1 = y;
    }else{
        (*m1)[0][clicks] = x;
        (*m1)[1][clicks] = y;
    }

    gc->setPixel(x,y);

    clicks++;
    
    if(rubberBandMode){
        gc->setMode(GraphicsContext::MODE_XOR);
    }
    
    mouseState = Mouse::CLICKED;
}

/* 
 * This function handles the button up event. When this happens, the drawing state is checked and
 * a shape is drawn if complete.
 * Inputs:
 *      gc - GraphicsContext object
 *      button - integer key for the button pressed
 *      x - x coordinate of button press
 *      y - y coordinate of button press
 * Outputs:
 *      none
 */
void MyDrawing::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y){
    if(rubberBandMode){
        if(mode == Mode::LINE || (mode == Mode::TRIANGLE && clicks==1)){
            //old line undraw
            gc->drawLine(x0,y0,x1,y1);

            (*m1)[0][clicks] = x;
            (*m1)[1][clicks] = y;
            clicks++;
        }else if(mode==Mode::TRIANGLE && clicks == 3){
            //undraw old lines
            gc->drawLine((*m1)[0][0], (*m1)[1][0], x1, y1);
            gc->drawLine((*m1)[0][1], (*m1)[1][1], x1, y1);
        }

        if(!(mode == Mode::TRIANGLE && clicks==2)){
            gc->setMode(GraphicsContext::MODE_NORMAL);
        }

    }

    if(isShapeDrawn()){
        std::cout << "Shape drawn!" << std::endl;
        Shape* s = createShape();
        image->add(s);
        s->draw(gc,vc);
        remakeMatrix();
        clicks=0;
    }

    mouseState = Mouse::RELEASED;
}

/* 
 * This function handles the mouse move event. When this happens, if rubberband mode is enabled, it
 * performs the necessary XOR drawing that produces the rubberband effect. This behavior is different
 * for lines and triangles, and both are handled in this function.
 * Inputs:
 *      gc - GraphicsContext object
 *      x - x coordinate of button press
 *      y - y coordinate of button press
 * Outputs:
 *      none
 */
void MyDrawing::mouseMove(GraphicsContext* gc, int x, int y){
    if(rubberBandMode){
        if((mouseState == Mouse::CLICKED || mouseState == Mouse::DRAGGING)){
                mouseState = Mouse::DRAGGING;

                //old line undraw
                gc->drawLine(x0,y0,x1,y1);

                //update
                x1 = x;
                y1 = y;

                //draw new line
                gc->drawLine(x0,y0,x1,y1);
        } else if(mouseState == Mouse::RELEASED && mode == Mode::TRIANGLE && clicks == 2){
            //undraw old lines
            gc->drawLine((*m1)[0][0], (*m1)[1][0], x1, y1);
            gc->drawLine((*m1)[0][1], (*m1)[1][1], x1, y1);

            //draw new lines
            gc->drawLine((*m1)[0][0], (*m1)[1][0], x, y);
            gc->drawLine((*m1)[0][1], (*m1)[1][1], x, y);

            //update
            x1 = x;
            y1 = y;
        }
    }
    
}

/* 
 * This function handles the key down alert. This involves switching on the keycode and
 * performing the appropriate actions, which can be viewed by displaying the help menu.
 * Inputs:
 *      gc - GraphicsContext object
 *      keycode - integer value for key that was pressed
 * Outputs:
 *      none
 */
void MyDrawing::keyDown(GraphicsContext* gc, unsigned int keycode){
    Mode newMode = mode;
    unsigned int oldColor = color;
    switch(keycode){
        case 'p':
        case 'P':
            newMode = Mode::POINT;
            break;
        case 'l':
        case 'L':
            newMode = Mode::LINE;
            break;
        case 't':
        case 'T':
            newMode = Mode::TRIANGLE;
            break;
        case 'c':
        case 'C':
            newMode = Mode::CIRCLE;
            break;
        case 'r':
        case 'R':
            rubberBandMode = !rubberBandMode;
            break;
        case 's':
        case 'S':
            saveToFile();
        case 'f':
        case 'F':
            loadFromFile();
            image->draw(gc,vc);
        case '0':
            color = GraphicsContext::WHITE;
            break;
        case '1':
            color = GraphicsContext::BLACK;
            break;
        case '2':
            color = GraphicsContext::GREEN;
            break;
        case '3':
            color = GraphicsContext::RED;
            break;
        case '4':
            color = GraphicsContext::CYAN;
            break;
        case '5':
            color = GraphicsContext::MAGENTA;
            break;
        case '6':
            color = GraphicsContext::YELLOW;
            break;
        case '7':
            color = GraphicsContext::GRAY;
            break;
        case '8':
            color = GraphicsContext::BLUE;
            break;
        case '9':
            color = GraphicsContext::BROWN;
            break;
        case 65361:
            vc->translate(-20,0);
            image->draw(gc,vc);
            break;
        case 65362:
            vc->translate(0,20);
            image->draw(gc,vc);
            break;
        case 65363:
            vc->translate(20,0);
            image->draw(gc,vc);
            break;
        case 65364:
            vc->translate(0,-20);
            image->draw(gc,vc);
            break;
        case '+':
            vc->scale(2,2);
            image->draw(gc,vc);
            break;
        case '-':
            vc->scale(0.5,0.5);
            image->draw(gc,vc);
            break;
        case ',':
            vc->rotate(-10);
            image->draw(gc,vc);
            break;
        case '.':
            vc->rotate(10);
            image->draw(gc,vc);
            break;
        case 'e':
            vc->reset();
            image->draw(gc,vc);
            break;
        default:
            printHelp();
    }

    if(newMode != mode){
        mode = newMode;
        remakeMatrix();
        clicks = 0;
        mouseState = Mouse::RELEASED;
    }

    if(color != oldColor){
        gc->setColor(color);
    }
}

/* 
 * This is a helper function for saving an image to file. This function requres no inputs as it
 * uses the file scoped state variables.
 * Inputs:
 *      none
 * Outputs:
 *      none
 */
void MyDrawing::saveToFile(){
    std::ofstream myfile;
    myfile.open(filename);
    image->out(myfile);
    myfile.close();
}

/* 
 * This is a helper function for loading an image to file. This function requres no inputs as it
 * uses the file scoped state variables.
 * Inputs:
 *      none
 * Outputs:
 *      none
 */
void MyDrawing::loadFromFile(){
    std::ifstream myfile;
    myfile.open(filename);
    image = Image::in(myfile);
    myfile.close();
}

/* 
 * This is a helper function defining the logic that determines if a shape is finished being drawn.
 * Inputs:
 *      none
 * Outputs:
 *      bool - true if current shape is done being drawn
 */
bool MyDrawing::isShapeDrawn(){
    if(mode == Mode::POINT && clicks == 1) return true;
    if(mode == Mode::LINE && clicks == 2) return true;
    if(mode == Mode::TRIANGLE && clicks==3) return true;
    return false;
}

/* 
 * This is a helper function for creating a shape based on the current shape's verticies. The 
 * verticies are first converted into model verticies before creating the shape to undo any
 * previous transformations to the shapes on the screen.
 * Inputs:
 *      none
 * Outputs:
 *      none
 */
Shape* MyDrawing::createShape(){
    matrix * mtemp = vc->deviceToModel(m1);
    if(mode == Mode::POINT) return new Line((*mtemp)[0][0],(*mtemp)[1][0],(*mtemp)[0][0],(*mtemp)[1][0], color);
    if(mode == Mode::LINE) return new Line((*mtemp)[0][0],(*mtemp)[1][0],(*mtemp)[0][1],(*mtemp)[1][1], color);
    if(mode == Mode::TRIANGLE) return new Triangle(mtemp,color);
    if(mode == Mode::CIRCLE) return NULL;   //todo
    delete mtemp;

    return NULL;
}

/* 
 * This is a helper function for recreating a matrix to store verticies after a shape has finished being drawn.
 * Inputs:
 *      none
 * Outputs:
 *      none
 */
void MyDrawing::remakeMatrix(){
    delete m1;
    
    switch(mode){
        case Mode::POINT:
        case Mode::CIRCLE:
            m1 = new matrix(4,1);
            break;
        case Mode::LINE:
            m1 = new matrix(4,2);
            (*m1)[3][0] = 1;
            (*m1)[3][1] = 1;
            break;
        case Mode::TRIANGLE:
            m1 = new matrix(4,3);
            (*m1)[3][0] = 1;
            (*m1)[3][1] = 1;
            (*m1)[3][2] = 1;
            break;
        default:
            break;
    }
}

/* 
 * This is a helper function for printing the help menu.
 * Inputs:
 *      none
 * Outputs:
 *      none
 */
void MyDrawing::printHelp(){
    std::cout << "Usage:\n"
                 "\tDrawing mode:\n"
                 "\t\tp-point\tl-line\tt-triangle\tc-circle\n"
                 "\tRubber band mode:\n"
                 "\t\tr - toggle rubber band mode\n"
                 "\tSaving and loading to file:\n"
                 "\t\ts - save to image.txt\tf - load image.txt from file\n"
                 "\tSwitch Color:\n"
                 "\t\t0 - White\t1 - Black\t2 - Green\t3 - Red\n"
                 "\t\t4 - Cyan\t5 - Magenta\t6 - Yellow\t7 - Gray\n"
                 "\t\t8 - Blue\t9 - Brown\n"
                 "\tImage Transformations:\n"
                 "\t\tup - translate up\tdown - translate down\n"
                 "\t\tleft - translate left\tright - translate right\n"
                 "\t\t+ - scale by 2\t- - scale by 0.5\n"
                 "\t\t. - rotate by 10 deg\t, - rotate by -10 deg\n"
                 "\t\tr - reset transformations" << std::endl;
}
