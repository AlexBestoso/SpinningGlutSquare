typedef enum {false, true}bool;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "kss.h"
#include "renderHeader.h"

int main(int argc, char *argv[]){
	square_default_init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	
	glutInitWindowSize(700,700);
	glutInitWindowPosition(200,0);

	glutCreateWindow("Spinning Square");
	
	glClearColor(0.5, 0.5, 0.5, .1);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	glutDisplayFunc(render);
	glutKeyboardUpFunc(keyboard_up);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard_down);
	glutReshapeFunc(resized);
	glutMainLoop();
	
	return 0;
}
