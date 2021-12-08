#pragma once 

#include <vector> 

class Color {
public: 

    // Color Attributes 
    float r; 
    float g; 
    float b; 

    // Constructors 
    Color(); 
    Color(float red, float green, float blue); 
    ~Color(); 

    // Methods 
    Color add(Color other); 
    Color multiply(Color other); 
    static Color average(vector<Color> colors); 
}