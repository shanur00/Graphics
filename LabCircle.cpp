#include <GL/glut.h>
#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>
double a1=5.0,b1=-1.0,a2=15.0,b2=-1.0,a3=5.0,b3=-11.0,a4=15.0,b4=-11.0; 
const double r=5.0;

void plotPoints(double x, double y, double h, double k, int n){
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POINTS);
  glVertex2f(10.0,-6.0);
  glVertex2f(0.0, 0.0);
  if(n==1){
    glVertex2f(x+h,y+k);
    glVertex2f(y+h,x+k);
  }
  if(n==2){
    glVertex2f(-x+h,y+k);
    glVertex2f(-y+h,x+k);
  }
  if(n==3){
    glVertex2f(x+h,-y+k);
    glVertex2f(y+h,-x+k);
  }
  if(n==4){
    glVertex2f(-x+h,-y+k);
    glVertex2f(-y+h,-x+k);  
  }
  glEnd();
}

void drawCircle(double h, double k, int n){

  for(double x=0; x<=r; x+=1.0){
    double y=sqrt(r*r-x*x);
    plotPoints(x,y,h,k,n);
  }

  /*for(double x=0; x<=r; x+=1.0){
    double y=sqrt(r*r-x*x);
    plotPoints(x+h, y+k);
  }
  for(double x=0; x<=r; x+=1.0){
    double y=sqrt(r*r-x*x);
    plotPoints(x+h, -y+k);
  }
  for(double x=0; x>=-r; x-=1.0){
    double y=sqrt(r*r-x*x);
    plotPoints(x+h, y+k);
  }
  for(double x=0; x>=-r; x-=1.0){
    double y=sqrt(r*r-x*x);
    plotPoints(x+h, -y+k);
  }*/
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawCircle(5.0,-11.0,1);
  drawCircle(15.0,-11.0,2);
  drawCircle(5.0,-1.0,3);
  drawCircle(15.0,-1.0,4);
  glFlush();
}

void init(){
  glClearColor(0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-40,40,-40,40);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(600,600);
  glutInitWindowPosition(100,100);
  glutCreateWindow("Circle");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}