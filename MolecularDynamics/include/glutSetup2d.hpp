#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#define sprintf_s snprintf

float* colorHue(float h);
void draw();
void keyboard(unsigned char key, int mx, int my);
void step(int k);
void reshape(int w, int h);
int glutStuff(void(*timeStep)(int), void(*drawWindow)(), void(*reshapeWindow)(int, int),
		void(*keyboard)(unsigned char, int, int), int* argc_, char** argv_,
		void* windowData, const char* title);

