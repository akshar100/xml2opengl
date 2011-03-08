#include <iostream>
#include <stdio.h>
#include <math.h>
#include "aGLX.h"

struct point_group1 {
		float x[3];
		float y[3];
};

struct point_group1 axPoints1(){
	struct point_group1 temp;
	
	temp.x[0] = 0.0;
	temp.x[1] = 1.0;
	temp.x[2] = -1.0;
	
	temp.y[0] = 0.0;
	temp.y[1] = 1.0;
	temp.y[2] = 1.0;
	
	return temp;	
}


void setup() { 

		 glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void display() { 
	
		glMatrixMode (GL_MODELVIEW);
		

		
		while(1)
		{
				
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen	
			glLoadIdentity(); //Load identity view matrix
			
			//Code goes here.
			glColor3f(0.0f, 0.0f, 1.0f);	
			
			
			axArc(0.0,0.0,0,180,0.6,0.0);
			axArc(0.0,0.0,0,180,0.8,0.0);
			axLine(0.0,0.0,1.0,1.0,0.0);
			struct point_group1 points1  = axPoints1();
			axPoly(points1.x, points1.y ,3, 0.0);
			
			
			glutSwapBuffers();

			

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
