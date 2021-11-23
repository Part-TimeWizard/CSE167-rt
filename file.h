
void matransform (stack<glm::mat4> &transfstack, GLfloat * values) ;
void rightmultiply (const glm::mat4 & M, stack<glm::mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, GLfloat * values) ;
void readfile (const char * filename) ;
void saveimg(std::vector<BYTE> pixels, int width, int height, const char* filename);