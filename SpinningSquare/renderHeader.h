#include "shapes/square.h"

void resized(int w, int h){
	int x, y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
		x = glutGet(GLUT_WINDOW_X);
		y = glutGet(GLUT_WINDOW_Y);
		glViewport(0, 0, w, h);
		gluOrtho2D(((float)w/(float)h)*(-1), ((float)w/(float)h), -1, 1);	
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		square_render();
	glutSwapBuffers();
}

void userControls(void){
	if(square.controlMode == 0){
		square.controls_wasd = square_wasd_controls;
		square.controls_jl = square_jl_controls;
	}
	
	square.controls_wasd();
	square.controls_jl();
}

void idle(void){
	userControls();
	glutPostRedisplay();
}
