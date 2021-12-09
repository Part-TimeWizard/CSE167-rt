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
//#include "main.h"
#include "include/Scene.h"
#include "include/Camera.h"

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

Scene* readfile(const char* filename)
{
    string str, cmd;
    ifstream in;

    int numused = 0;
    const int numLights = 10; // max 10 point lights.  You can increase this if you want to add more lights.
    float lightposn[3 * numLights]; // Point light Positions
    float lightcolor[3 * numLights]; // Point light Colors

    /*float ambient[3];
    float diffuse[3];
    float specular[3];
    float emission[3];*/
    glm::vec3 ambient = glm::vec3(0,0,0);
    glm::vec3 diffuse = glm::vec3(0,0,0);
    glm::vec3 specular = glm::vec3(0,0,0);
    glm::vec3 emission = glm::vec3(0,0,0);
    float shininess = 0.0f;

    int maxVerts = 0;
    vector<glm::vec3> vertexList;

    Scene* scene = nullptr;

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
                    if (validinput) {
                        ambient = glm::vec3(values[0],values[1],values[2]);
                    }

                }
                // Material Commands
                // Ambient, diffuse, specular, shininess properties for each object.
                // Note that no transforms/stacks are applied to the colors.
                
                  else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        /*for (i = 0; i < 3; i++) {
                            diffuse[i] = values[i];
                        }*/
                        diffuse = glm::vec3(values[0],values[1],values[2]);
                    }
                } else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        /*for (i = 0; i < 3; i++) {
                            specular[i] = values[i];
                        }*/
                        specular = glm::vec3(values[0],values[1],values[2]);
                    }
                } else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        /*for (i = 0; i < 3; i++) {
                            emission[i] = values[i];
                        }*/
                        emission = glm::vec3(values[0],values[1],values[2]);
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
                        std::cout<<"Generating Scene..."<<std::endl;
                        scene = new Scene(values[0],values[1]);
                    }

                }
                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    scene->setDepth(values[0]);
                }
                else if (cmd == "output") {
                    string outName;
                    s >> outName;
                    scene->setName(outName);
                }
                else if (cmd == "camera") {
                    validinput = readvals(s,10,values); // 10 values eye cen up fov
                    if (validinput) {
                        // May need to mult by transform stack
                        glm::vec3 eye = glm::vec3(values[0],values[1],values[2]);
                        glm::vec3 target = glm::vec3(values[3],values[4],values[5]);
                        glm::vec3 up = glm::vec3(values[6],values[7],values[8]);
                        float fov = values[9];
                        std::cout << "Generating Camera..."<<std::endl;
                        for (int i = 0; i < 10; i++){
                            std::cout<< values[i]<< " ";
                        }
                        std::cout<<"\n";
                        scene->camera = new Camera(eye, target, up, fov, scene->imageHeight, scene->imageWidth);
                    }
                 }
                              
                else if (cmd == "translate") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        
                        glm::mat4 translateMatrix; 
                        translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(values[0],values[1],values[2]));
                        rightmultiply(translateMatrix, transfstack);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s,3,values);
                    if (validinput) {
                        
                        glm::mat4 scaleMatrix;
                        scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(values[0],values[1],values[2]));
                        rightmultiply(scaleMatrix, transfstack);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s,4,values);
                    if (validinput) {
                        
                        glm::vec3 axis = glm::normalize(glm::vec3(values[0], values[1], values[2]));
                        glm::mat4 rotateMatrix;
                        rotateMatrix = glm::rotate(glm::mat4(1.0f),values[3],axis);
                        rightmultiply(rotateMatrix, transfstack);   
                    }
                }

                else if (cmd == "maxverts") {
                    validinput = readvals(s, 1, values);
                    maxVerts = values[0];
                }
                else if (cmd == "sphere") {
                    validinput = readvals(s, 4, values);
                    // YOUR CODE HERE
                }
                else if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    // Make new obj, right mult by transfstack
                    glm::vec3 v1 = vertexList[values[0]];
                    glm::vec3 v2 = vertexList[values[1]];
                    glm::vec3 v3 = vertexList[values[2]];
                    glm::mat4 T = transfstack.top();
                    v1 = glm::vec3(T * glm::vec4(v1,1));
                    v2 = glm::vec3(T * glm::vec4(v2,1));
                    v3 = glm::vec3(T * glm::vec4(v3,1));
                    std::cout<<"Creating Triangle ("<<v1[0]<<","<<v1[1]<<","<<v1[2]<<v2[0]<<","<<v2[1]<<","<<v2[2]<<v3[0]<<","<<v3[1]<<","<<v3[2]<<")"<<std::endl;
                    scene->addTriangle(v1,v2,v3,ambient,specular,diffuse,emission,shininess);
                }
                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if (vertexList.size() < maxVerts){
                        vertexList.push_back(glm::vec3(values[0],values[1],values[2]));
                    } else {
                        cerr << "Max vertices reach, unable to add more\n";
                    }
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
    return scene;
}

void saveimg(std::vector<BYTE> pixels, int width, int height, const char* filename) {

    // You need to get your image into the pixel vector.  How you do so is up to you.
    // Also, make sure you follow the directions in the writeup, and call FreeImage_Initialise() before using this function.
    FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels.data(), width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

    std::cout << "Saving screenshot: " << filename << std::endl;

    FreeImage_Save(FIF_PNG, img, filename, 0);
}

int main(int argc, char** argv) {
    
    Scene* scene = readfile(argv[1]);
    
    // Find the colors for each pixel
    std::cout << "Beginning fill" <<std::endl;
    /*
    for(int i = 0; i < tempWidth*tempHeight*3; i++) {
        scene.pixelData.push_back(static_cast<BYTE>(i));
    }
    */
    for(int y = 0; y < scene->imageHeight; y++) {
        for(int x = 0; x < scene->imageWidth; x++) {
            Ray ray = scene->camera->RayThruPixel(x, y); 
            
            RayHit intObj = scene->raycast(ray); 
            // Can access intObj.ray to use for FindColor() 
            if(intObj.solid == nullptr) {
                scene->setPixel(x, y, glm::vec3(0,0,0));
            } else {
                scene->setPixel(x,y,glm::vec3(0,255,0));
            }
            //scene.setPixel(x, y, glm::vec3(x,y,0));
        }
    }
    std::cout << "Fill Complete" <<std::endl;

    // Export Image
    FreeImage_Initialise();
    saveimg(scene->pixelData, scene->imageWidth, scene->imageHeight, scene->outFileName.c_str());
    FreeImage_DeInitialise();

    // Deinitialize all the objects?
}