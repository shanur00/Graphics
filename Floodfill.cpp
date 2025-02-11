#include <GL/glut.h>
#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
int ww=600, wh=600;
int scale=20;
const double PI=3.14159;
float bgCol[3]={1.0,1.0,1.0};
float iniCol[3]={1.0,0.0,0.0};  // red
float fillCol[3] = {1.0,1.0,1.0};   

void plotPoints(int x, int y, float f[3]){
  glBegin(GL_POINTS);
  glColor3fv(f);
  glVertex2i(x, y);
  glEnd();
  glFlush();
}

void getPixel(int x, int y, float pixels[3]){
  glReadPixels(x,y,  // Starting coordinates to read from
    1.0,1.0,  // Width and height of pixels to read (here just 1x1 pixel)
    GL_RGB,   // Format of the pixel data (RGB color model)
    GL_FLOAT, // Data type of each component
    pixels);  // Array where the pixel data will be stored
}

void floodFill(int x, int y, float oldColor[3], float newColor[3]){
  float color[3];
  getPixel(x*scale, y*scale, color);
  if((color[0]==oldColor[0]) && (color[1]==oldColor[1]) && (color[2]==oldColor[2])){
    plotPoints(x*scale, y*scale, newColor);
    floodFill(x+1, y, oldColor, newColor);
    floodFill(x-1, y, oldColor, newColor);
    floodFill(x, y+1, oldColor, newColor);
    floodFill(x, y-1, oldColor, newColor);
    floodFill(x-1, y-1, oldColor, newColor);
    floodFill(x+1, y+1, oldColor, newColor);
    floodFill(x-1, y+1, oldColor, newColor);
    floodFill(x+1, y-1, oldColor, newColor);
  }
}

void drawShape(int n, int m, float color[3]){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
      plotPoints(i*scale,(i+j)*scale,color);
    }
  }
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawShape(5,10,iniCol);
  floodFill(2,3,iniCol,fillCol);
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
  glutCreateWindow("FloodFill");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}