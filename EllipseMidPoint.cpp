#include <GL/glut.h>
#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>
const double PI=3.14159;
int r=5;
int h = 7, k = 5;  // Center (h, k)
int a = 5, b = 7; 

int rad(int deg){
  return deg*PI/180.0;
}

void plotPoints(int x, int y, int h, int k){
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POINTS);
  glVertex2i(x+h, y+k);
  glVertex2i(x+h, -y+k);
  glVertex2i(-x+h, y+k);
  glVertex2i(-x+h, -y+k);
  glEnd();
}

void drawEclipse(int h, int k, int a, int b){
  int x=0, y=b;
  int p=b*b-a*a*b+(a*a)/4;
  int fx=0, fy=2*a*a*b;
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
  drawEclipse(7.0,5.0,5.0,7.0);
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