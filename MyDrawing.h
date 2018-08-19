/**
 * MyDrawing.h - Interface for MyDrawing window event handler implementation.
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: may 3 2018
 */
#ifndef MYDRAWING_H
#define MYDRAWING_H

#include "drawbase.h"
#include "Image.h"
#include "matrix.h"
#include "Shape.h"
#include "ViewContext.h"

//forward reference
class GraphicsContext;

class MyDrawing : public DrawingBase {
    public:
        /* 
        * This is a constructor for a MyDrawing object
        * Inputs:
        *      vc - ViewContext object for applying transformations.
        */
        MyDrawing(ViewContext*);

        /* 
        * This is a Destructor for a MyDrawing object
        * Inputs:
        *      none
        */
        ~MyDrawing();

        /* 
        * This function handles the exposure event. When this happens, the image on the screen is 
        * erased and then redrawn.
        * Inputs:
        *      gc - GraphicsContext object
        * Outputs:
        *      none
        */
        virtual void paint(GraphicsContext* gc);

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
        virtual void mouseButtonDown(GraphicsContext* gc, unsigned int button, int x, int y);

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
        virtual void mouseButtonUp(GraphicsContext* gc, unsigned int button, int x, int y);

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
        virtual void mouseMove(GraphicsContext* gc, int x, int y);

        /* 
        * This function handles the key down alert. This involves switching on the keycode and
        * performing the appropriate actions, which can be viewed by displaying the help menu.
        * Inputs:
        *      gc - GraphicsContext object
        *      keycode - integer value for key that was pressed
        * Outputs:
        *      none
        */
        virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
    private:
        int x0;
        int y0;
        int x1;
        int y1;

        enum class Mode {POINT, LINE, TRIANGLE, CIRCLE};
        enum class Mouse {CLICKED, DRAGGING, RELEASED};

        ViewContext* vc;

        Image* image;
        
        Mode mode;

        matrix* m1;

        unsigned int color;

        unsigned int clicks;

        Mouse mouseState;

        bool rubberBandMode;

        /* 
        * This is a helper function for printing the help menu.
        * Inputs:
        *      none
        * Outputs:
        *      none
        */
        void printHelp();

        /* 
        * This is a helper function for recreating a matrix to store verticies after a shape has finished being drawn.
        * Inputs:
        *      none
        * Outputs:
        *      none
        */
        void remakeMatrix();

        /* 
        * This is a helper function defining the logic that determines if a shape is finished being drawn.
        * Inputs:
        *      none
        * Outputs:
        *      bool - true if current shape is done being drawn
        */
        bool isShapeDrawn();

        /* 
        * This is a helper function for saving an image to file. This function requres no inputs as it
        * uses the file scoped state variables.
        * Inputs:
        *      none
        * Outputs:
        *      none
        */
        void saveToFile();

        /* 
        * This is a helper function for loading an image to file. This function requres no inputs as it
        * uses the file scoped state variables.
        * Inputs:
        *      none
        * Outputs:
        *      none
        */
        void loadFromFile();

        /* 
        * This is a helper function for creating a shape based on the current shape's verticies. The 
        * verticies are first converted into model verticies before creating the shape to undo any
        * previous transformations to the shapes on the screen.
        * Inputs:
        *      none
        * Outputs:
        *      none
        */
        Shape* createShape();

};

#endif