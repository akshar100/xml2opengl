#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

const double PI = 3.141592653589793;
const double deg_to_rad = 180.0/PI;
const double rad_to_deg = PI/180.0;


void axPoint(float x, float y, float layer)
{
		glBegin(GL_POINTS);
		glVertex3f(x,y,layer);
		glEnd( );


}

void axLine(float x1,float y1, float x2, float y2,float layer)
{
	// next code will draw a line at starting and ending coordinates specified by glVertex3f
	glBegin(GL_LINES);
	glVertex3f(x1, y1,layer); // origin of the line
	glVertex3f(x2, y2,layer); // ending point of the line
	glEnd( );


}

void axArc(float x,float y, float startAngle, float endAngle, float radius,float layer) //Angles in Degrees
{
		
		glBegin(GL_POINTS);
		for(float i=startAngle;i<endAngle;i=i+0.001)
		{
			glVertex3f(radius*cos(i*rad_to_deg)+x,radius*sin(i*rad_to_deg)+y,layer); 		
		}
		glEnd();
}
 


void axPoly(float x[], float y[],int vertices, float layer)
{
		glBegin(GL_POLYGON);
		for(int i=0;i<vertices;i=i+1)
		{
			glVertex3f(x[i],y[i],layer); 		
		}
		glEnd();
}







