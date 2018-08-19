/**
 * main.cpp - This is test driver for the Shapes classes
 * Author: larsonma@msoe.edu <Mitchell Larson>
 * Date: april 19 2018
 */

#include "x11context.h"
#include "Line.h"
#include "Triangle.h"
#include "Image.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include "MyDrawing.h"
#include "ViewContext.h"

#include <fenv.h>

static GraphicsContext* gc;
static ViewContext* vc;

static void initialize();
static void testLine();
static void testTriangle();
static void testImage();
static void testFileWrite();
static void testFileRead();
static void demo();
static void lab5();

using namespace std;

/* 
 * This is a driver for testing the Shapes functionality
 * 
 * Parameters:
 * 	none
 * 
 * Returns:
 *  0 if successful
 */
int main(){
    int mode = 6;

    initialize();
    if(mode==0) testLine();
    if(mode==1) testTriangle();
    if(mode==2) testImage();
    if(mode==3) testFileWrite();
    if(mode==4) testFileRead();
    if(mode==5) demo();
    if(mode==6) lab5();

    delete gc;
    delete vc;
    return 0;
}

static void initialize(){
    gc = new X11Context(800,600,GraphicsContext::BLACK);
    vc = new ViewContext(gc->getWindowWidth()/2, gc->getWindowHeight()/2,0);
}

static void lab5(){
    gc->setColor(GraphicsContext::WHITE);

    MyDrawing md(vc);

    gc->runLoop(&md);
}

static void demo(){
    Line line1(0, 0, 700, 500, 150, 30, 150);

    matrix t2V(4,3);
    t2V[0][0] = 100;    t2V[1][0] = 100;
    t2V[0][1] = 600;    t2V[1][1] = 200;
    t2V[0][2] = 350;    t2V[1][2] = 350;

    Triangle t1(&t2V, 200, 200, 40);

    Image * img = new Image();
    img->add(&line1);
    img->add(&t1);

    img->draw(gc,vc);
    sleep(5);

    ofstream myfile;
    myfile.open("demo.txt");
    img->out(myfile);
    myfile.close();

    Image * imgCopy = new Image(*img);

    delete img;
    delete imgCopy;

    gc->clear();
    sleep(3);

    ifstream infile;
    infile.open("demo.txt");
    Image * loadImage = Image::in(infile);

    loadImage->draw(gc,vc);
    sleep(5);

    loadImage->erase();

    infile.close();
    delete loadImage;
}

static void testFileRead(){
    ifstream myfile;
    myfile.open("test.txt");

    Image * image = Image::in(myfile);
    
    //image->out(cout);


    image->draw(gc,vc);

    sleep(5);

    image->erase();

    delete image;

    myfile.close();


}

static void testFileWrite(){
    ofstream myfile;
    myfile.open("test.txt");

    Line line1(5, 5, 10, 10);
    Line line2(0, 0, 30, 80, 150, 30, 150);
    Line line3(line1);
    Shape * line4 = new Line(50,60,70,80);

    matrix t1V(4,3);
    t1V[0][0] = 100;    t1V[1][0] = 100;
    t1V[0][1] = 500;    t1V[1][1] = 200;
    t1V[0][2] = 150;    t1V[1][2] = 150;

    matrix t2V(4,3);
    t2V[0][0] = 100;    t2V[1][0] = 100;
    t2V[0][1] = 600;    t2V[1][1] = 200;
    t2V[0][2] = 350;    t2V[1][2] = 350;

    Triangle t1(&t1V);
    Triangle t2(&t2V, 200, 200, 40);

    Triangle t4(5,10,700,75,245,230);
    Triangle t3(0,0,60,100,300,150,80,0,80);

    Image * image = new Image();
    image->add(&line1);
    image->add(&line2);
    image->add(&line3);
    image->add(line4);
    image->add(&t1);
    image->add(&t2);
    image->add(&t3);
    image->add(&t4);

    image->out(myfile);

    myfile.close();

}

static void testImage(){
    //Setup shapes
    Line line1(5, 5, 10, 10);
    Line line2(0, 0, 30, 80, 150, 30, 150);
    Line line3(line1);
    Shape * line4 = new Line(50,60,70,80);

    matrix t1V(4,3);
    t1V[0][0] = 100;    t1V[1][0] = 100;
    t1V[0][1] = 500;    t1V[1][1] = 200;
    t1V[0][2] = 150;    t1V[1][2] = 150;

    matrix t2V(4,3);
    t2V[0][0] = 100;    t2V[1][0] = 100;
    t2V[0][1] = 600;    t2V[1][1] = 200;
    t2V[0][2] = 350;    t2V[1][2] = 350;

    Triangle t1(&t1V);
    Triangle t2(&t2V, 200, 200, 40);

    Triangle t4(5,10,700,75,245,230);
    Triangle t3(0,0,60,100,300,150,80,0,80);

    Image * image = new Image();
    image->add(&line1);
    image->add(&line2);
    image->add(&line3);
    image->add(line4);
    image->add(&t1);
    image->add(&t2);
    image->add(&t3);
    image->add(&t4);

    Image * imageCopy = new Image(*image);

    image->draw(gc,vc);

    sleep(5);

    image->out(cout);

    image->erase();

    gc->clear();
    sleep(1);

    cout << "Drawing copy of image" << endl;

    imageCopy->draw(gc,vc);

    sleep(5);

    imageCopy->erase();

}

static void testLine(){
    //Test Constructors
    cout << ">>Testing Constructors" << endl;
    Line line1(5, 5, 10, 10);
    Line line2(0, 0, 30, 80, 150, 30, 150);
    Line line3(line1);

    //Test Draw
    cout << ">>Testing Draw methods for lines" << endl;
    line1.draw(gc,vc);
    line2.draw(gc,vc);
    line3.draw(gc,vc);

    //Test Print
    cout << ">>Testing out methods" << endl;
    line1.out(cout);
    line2.out(cout);
    line3.out(cout);

    Line* lineX = new Line(6,6,6,6);
    delete lineX;

    //Test Clone
    cout << ">>Testing Clone functionality" << endl;
    Shape * line4 = new Line(50,60,70,80);
    Shape * line5 = &line4->clone();

    line4->out(cout);
    line5->out(cout);

    //Test = operator
    cout << ">>Testing = operator" << endl;
    Line line6(0,0,1,1);
    line6 = line2;
    line6.out(cout);

    sleep(5);

    delete line4;
    delete line5;
    cout << ">>Done with tests" << endl;
}

static void testTriangle(){
    cout << ">>Testing Triangle constructors" << endl;
    matrix t1V(4,3);
    t1V[0][0] = 100;    t1V[1][0] = 100;
    t1V[0][1] = 500;    t1V[1][1] = 200;
    t1V[0][2] = 150;    t1V[1][2] = 150;

    matrix t2V(4,3);
    t2V[0][0] = 100;    t2V[1][0] = 100;
    t2V[0][1] = 600;    t2V[1][1] = 200;
    t2V[0][2] = 350;    t2V[1][2] = 350;

    Triangle t1(&t1V);
    Triangle t2(&t2V, 200, 200, 40);

    Triangle t4(5,10,700,75,245,230);
    Triangle t3(0,0,60,100,300,150,80,0,80);

    Triangle * temp = new Triangle(&t1V);
    delete temp;

    cout << ">>Testing Draw methods for Triangle" << endl;
    t1.draw(gc,vc);
    t2.draw(gc,vc);
    t3.draw(gc,vc);
    t4.draw(gc,vc);

    cout << ">>Testing out methods for Triangle" << endl;
    t1.out(cout);
    t2.out(cout);
    t3.out(cout);
    t4.out(cout);

    cout << ">>Testing clone method for Triangle" << endl;
    Shape * t3Clone = &t3.clone();
    cout << ">>>>The following triangles should have the same properties" << endl;
    t3.out(cout);
    t3Clone->out(cout);

    cout << ">>Testing = operator for Triangle" << endl;
    t3 = t1;
    cout << ">>>>The following triangles should have the same properties" << endl;
    t3.out(cout);
    t1.out(cout);

    cout << ">>Triangle tests finished" << endl;

    sleep(5);
}