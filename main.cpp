/*****************************************************************************/
/* This is modified from the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/*****************************************************************************/
// IMPORTANT!!
// --------------
// If you want to use these functions,
// you need to either work this function into your object oriented approach,
// return the necessary variables as some sort of struct, or use global variables to get
// the scene info to your raytracer.
/*****************************************************************************/


/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix
// transformations for a stack (matransform) and to rightmultiply the
// top of a stack.  These functions are given to aid in setting up the
// transformations properly, and to use glm functions in the right way.
// Their use is optional in your program.


// The functions readvals and readfile do basic parsing.  You can of course
// rewrite the parser as you wish, but we think this basic form might be
// useful to you.  It is a very simple parser.

// Some parts are implementation dependent (You can use this as a guide, or
// connect this to your existing CSE 167 HW 2 skeleton.)
// *****************************************************************************/


// Basic includes to get this file to work.
#include <FreeImage.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

using namespace std;
#include "main.h"
#include "include/Scene.h"
#include "Camera.h"

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<glm::mat4> &transfstack, GLfloat* values)
{
    glm::mat4 transform = transfstack.top();
    glm::vec4 valvec = glm::vec4(values[0],values[1],values[2],values[3]);
    glm::vec4 newval = transform * valvec;
    for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const glm::mat4 & M, stack<glm::mat4> &transfstack)
{
    glm::mat4 &T = transfstack.top();
    T = T * M;
}

// Function to read the input data values
bool readvals(stringstream &s, const int numvals, GLfloat* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void readfile(const char* filename)
{
    string str, cmd;
    ifstream in;

    // YOUR CODE HERE
    // We define some variables here as guides.  You will need to either include this function in some sort of class
    // to get access to them or define the variables globally.

    int numused = 0;
    const int numLights = 10; // max 10 point lights.  You can increase this if you want to add more lights.
    float lightposn[3 * numLights]; // Point light Positions
    float lightcolor[3 * numLights]; // Point light Colors

    float ambient[3];
    float diffuse[3];
    float specular[3];
    float emission[3];
    float shininess;

    in.open(filename);
    if (in.is_open()) {
        
        // I need to implement a matrix stack to store transforms.
        // This is done using standard STL Templates
        stack <glm::mat4> transfstack;
        transfstack.push(glm::mat4(1.0));  // identity
       
        getline (in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines
                
                stringstream s(str);
                s >> cmd;
                int i;
                float values[10]; // Position and color for light, colors for others
                // Up to 10 params for cameras.
                bool validinput; // Validity of input
                
                // Process the light, add it to database.
                // Lighting Command
                if (cmd == "point") {
                    if (numused == numLights) { // No more Lights
                        cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
                    } else {
                        validinput = readvals(s, 6, values); // Position/color for lts.
                        if (validinput) {
                            
                            for(int i = 0; i < 3; i++){
                                lightposn[numused*3 + i] = values[i];
                                lightcolor[numused*3 + i] = values[i + 3];
                            }
                            ++numused;
                        }
                    }
                }
                else if (cmd == "directional") {
                    // YOUR CODE HERE.  You can use point lights as an example, or 
                    // implement both your own way.
                }
                else if (cmd == "attenuation") {
                    // YOUR CODE HERE.
       
                }

                else if (cmd == "ambient") {
                    validinput = readvals(s, 3, values); // colors
                    // YOUR CODE HERE

                }
                // Material Commands
                // Ambient, diffuse, specular, shininess properties for each object.
                // Note that no transforms/stacks are applied to the colors.
                
                  else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            diffuse[i] = values[i];
                        }
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            specular[i] = values[i];
                        }
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            emission[i] = values[i];
                        }
                    }
                } else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        shininess = values[0];
                    }
                } else if (cmd == "size") {
                    validinput = readvals(s,2,values);
                    if (validinput) {
                        // YOUR CODE HERE
                        // This the the image size, as width, height.
                        // Get these values and store them for use with your raytracer.
                    }

                }
                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    // YOUR CODE HERE
                }
                else if (cmd == "output") {
                    validinput = readvals(s, 1, values);
                    // YOUR CODE HERE
                }
                else if (cmd == "camera") {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput) {
                        
                        // YOUR CODE HERE
                        // You'll need to read these values and use them for your own
                        // camera implementation.  Keep in mind for the raytracer the camera will be static.
                        
                    }
                 }
                              
                else if (cmd == "translate") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        
                        glm::mat4 translateMatrix; 

                        // YOUR CODE HERE
                        // Implement a translation matrix.  You can just use glm built in functions
                        // if you want.
                      
                        rightmultiply(translateMatrix, transfstack);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        
                        glm::mat4 scaleMatrix;

                        // YOUR CODE HERE
                        // Implement a scale matrix.  You can just use glm built in functions
                        // if you want.

                        rightmultiply(scaleMatrix, transfstack);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s,4,values);
                    if (validinput) {
                        
                        glm::vec3 axis = glm::normalize(glm::vec3(values[0], values[1], values[2]));
                        glm::mat4 rotateMatrix;

                        // YOUR CODE HERE
                        // Implement a rotation matrix.  You can just use glm built in functions
                        // if you want.

                        rightmultiply(rotateMatrix, transfstack);
                        
                    }
                }

                else if (cmd == "maxverts") {
                    validinput = readvals(s, 1, values);
                    // YOUR CODE HERE
                }
                else if (cmd == "sphere") {
                    validinput = readvals(s, 4, values);
                    // YOUR CODE HERE
                }
                else if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    // YOUR CODE HERE
                }
                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    // YOUR CODE HERE
                }


                
                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top());
                } else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n";
                    } else {
                        transfstack.pop();
                    }
                }
                
                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline (in, str);
        }
        

    } else {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}

void saveimg(std::vector<BYTE> pixels, int width, int height, const char* filename) {

    // You need to get your image into the pixel vector.  How you do so is up to you.
    // Also, make sure you follow the directions in the writeup, and call FreeImage_Initialise() before using this function.
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels.data(), width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

    std::cout << "Saving screenshot: " << filename << std::endl;

    FreeImage_Save(FIF_PNG, img, filename, 0);
}

int main(int argc, char** argv) {

    FreeImage_Initialise();
    //initShiz
    int tempWidth = 800;
    int tempHeight = 800;
    string outName = "firstTest.png";
    Scene scene = Scene(tempWidth, tempHeight, 5, outName);
    
    glm::vec3 testV1 = glm::vec3(1,0,0);
    glm::vec3 testV2 = glm::vec3(0,1,0);
    glm::vec3 testV3 = glm::vec3(0,0,1);
    scene.addTriangle(testV1,testV2,testV3);
    
    // Temp fill array
    std::cout << "Beginning fill" <<std::endl;
    /*
    for(int i = 0; i < tempWidth*tempHeight*3; i++) {
        scene.pixelData.push_back(static_cast<BYTE>(i));
    }
    */
    for(int y = 0; y < tempHeight; y++) {
        for(int x = 0; x < tempWidth; x++) {
            scene.setPixel(x, y, glm::vec3(x,y,0));
        }
    }
    std::cout << "Fill Complete" <<std::endl;

    saveimg(scene.pixelData, tempWidth, tempHeight, outName.c_str());

    FreeImage_DeInitialise();
}