
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "aGLX.h"


int [][] axpoints1() { int[][] temp= { {0.0,0.0},{1.0,1.0},{-1.0,1.0} }; return temp;}


void display() { 
	
		float Rotate =-20.0f;
		glMatrixMode (GL_MODELVIEW);
		

		
		float i =0;
		int flag = 0;
		while(1)
		{
			
			axArc(0.0,0.0,0,180,0.6,0.0);
			axArc(0.0,0.0,0,180,0.8,0.0);
			axLine(0.0,0.0,0.0,0.0,0.0);
			axPoly(axpoints1(),3,0.0);
			
			
		}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("Building API");
	
	setup();
	glutDisplayFunc(display);
	glutMainLoop();
	getchar();
	return 0;

}

