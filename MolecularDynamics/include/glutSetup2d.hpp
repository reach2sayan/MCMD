#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#define sprintf_s snprintf
const double SQR_2_5 = std::pow(2.0, 0.2);
const double SIGMA_6 = std::pow(0.025, 6.0);
float* colorHue(float h);
template<int D>
void draw();
template<int D>
void keyboard(unsigned char key, int mx, int my);
template<int D>
void step(int k);
void reshape(int w, int h);
int glutStuff(void(*timeStep)(int), void(*drawWindow)(), void(*reshapeWindow)(int, int),
		void(*keyboard)(unsigned char, int, int), int* argc_, char** argv_,
		void* windowData, const char* title);

