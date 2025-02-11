#include <GL/glut.h>
#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>
const double PI=3.14159;

void plotPoints(double x, double y, double h, double k){
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POINTS);

  glVertex2f(h, k);

  double rotation=45*PI/180.0;
  double xr1 = x * cos(rotation) - y * sin(rotation) + h;
  double yr1 = x * sin(rotation) + y * cos(rotation) + k;
  glVertex2f(xr1, yr1);

  double xr2 = x * cos(rotation) - (-y) * sin(rotation) + h;
  double yr2 = x * sin(rotation) + (-y) * cos(rotation) + k;
  glVertex2f (xr2, yr2);

  double xr3 = (-x) * cos(rotation) - y * sin(rotation) + h;
  double yr3 = (-x) * sin(rotation) + y * cos(rotation) + k;
  glVertex2f (xr3, yr3);

  double xr4 = (-x) * cos(rotation) - (-y) * sin(rotation) + h;
  double yr4 = (-x) * sin(rotation) + (-y) * cos(rotation) + k;
  glVertex2f (xr4, yr4);
  glEnd();
}

void drawEclipse(double h, double k, double a, double b){
  double x=0, y=b;
  double p=b*b-a*a*b+(a*a)/4;
  double fx=0, fy=2*a*a*b;
  while (fx<fy) {
    plotPoints(x,y,h,k);  // <-- ISSUE: Should be (x,y,h,k)
    ++x;
    fx=fx+2*b*b;
    if(p<0){
      p+=fx+b*b;
    }
    else{
      --y;
      fy-=2*a*a;
      p+=fx+b*b-fy;
    }
  }
  plotPoints(x,y,h,k);
  p=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-(a*a*b*b);
  while(y>0){
    --y;
    fy-=2*a*a;
    if(p>=0){
      p=p-fy+a*a;
    }
    else{
      ++x;
      fx+=2*b*b;
      p+=fx-fy+a*a;
    }
    plotPoints(x,y,h,k);
  }
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawEclipse(-9.0,9.0,10.0,5.0);
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
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("BresenhamCircle");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}