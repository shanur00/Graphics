#include <GL/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

int r=5;

void plotPoints(int x, int y, int h, int k, int n){
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POINTS);
  glVertex2f(10.0,-6.0);
  glVertex2f(0.0, 0.0);
  if(n==1){
    glVertex2i(x+h,y+k);
    glVertex2i(y+h,x+k);
  }
  if(n==2){
    glVertex2i(-x+h,y+k);
    glVertex2i(-y+h,x+k);
  }
  if(n==3){
    glVertex2i(x+h,-y+k);
    glVertex2i(y+h,-x+k);
  }
  if(n==4){
    glVertex2i(-x+h,-y+k);
    glVertex2i(-y+h,-x+k);  
  }
  glEnd();
}

void drawCircle(int h, int k, int n){
  int x=0,y=r,d=3-2*r;
  while(x<=y){
    plotPoints(x,y,h,k,n);
    if(d<0){
      d+=4*x+6;
    }
    else{
      d+=4*(x-y)+10;
      --y;
    }
    ++x;
  }
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawCircle(5,-11, 1);
  drawCircle(15, -11, 2);
  drawCircle(5, -1, 3);
  drawCircle(15, -1, 4);
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