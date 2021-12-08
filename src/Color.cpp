#include <include/Color.h> 

Color::Color() {} 

Color::~Color() {} 

Color::Color(float red, float green, float blue) {
    r = red; 
    g = green; 
    b = blue; 
}

Color Color::add(Color other) {
    // rgb values range from 0.0f to 1.0f (0 - 256) 
    return new Color(min(r + other.r, 1), min(g + other.g, 1), min(b + other.b, 1));
}

Color Color::multiply(Color other) { 
    // rgb value range does not matter for component wise multiplication 
    return new Color(r * other.r, g * other.g, b * other.b);
}

static Color Color::average(vector<Color> colors) {
    int numCol = colors.size(); 
    float rSum; 
    float gSum; 
    float bSum; 

    for (auto color : colors) {
        rSum += color.r; 
        gSum += color.g; 
        bSum += color.b; 
    }

    return new Color(rSum / numCol, gSum / numCol, bSum / numCol); 
}