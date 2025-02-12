#include <GL/glut.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <vector>
#include <wingdi.h>
double ww=600, wh=600;
int scale=20;
const double PI=3.14159;
float bCol[3]={1.0,1.0,1.0};  // white
float iniCol[3]={1.0,0.0,0.0};  // red
float fillCol[3] = {0.0,1.0,0.0};  //green


void plotPoints(int x, int y, float f[3]){
  glBegin(GL_POINTS);
  glColor3fv(f);
  glVertex2i(x, y);
  glEnd();
  glFlush();
}

void getPixel(int x, int y, float f[3]){
  glReadPixels(x, y, 
    1.0, 1.0, 
    GL_RGB, 
    GL_FLOAT, 
    f);
}

void bounderyFill(int x, int y, float fill[3], float b[3]){
  float color[3];
  getPixel(x*scale, y*scale, color);
  if(!((color[0]==b[0])&&(color[1]==b[1])&&(color[2]==b[2]))&&
    !((color[0]==fill[0])&&(color[1]==fill[1])&&(color[2]==fill[2]))){
    plotPoints(x*scale, y*scale, fill);
    bounderyFill(x+1, y, fill, b);
    bounderyFill(x-1, y, fill, b);
    bounderyFill(x, y+1, fill, b);
    bounderyFill(x, y-1, fill, b);
  }
}

void drawLine(int n, int m, float f1[3], float f2[3]){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      if(i==1||i==n){
        plotPoints(i*scale, (i+j)*scale, f1);
        std::cout<<i<<" "<<i+j<<"\n";
      }
      else{
        if(j==1 || j==m){
          plotPoints(i*scale,(i+j)*scale, f1);
          std::cout<<i<<" "<<i+j<<"\n";
        }
        else{
          plotPoints(i*scale,(i+j)*scale,f2);
          std::cout<<i<<" "<<i+j<<"\n";
        }
      }
    }
  }
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawLine(5,10, bCol, iniCol);
  bounderyFill(3, 5, fillCol, bCol);
  glFlush();
}

void init(){
  glClearColor(0.0,0.0,0.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(ww, wh);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("BoundaryFill");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}