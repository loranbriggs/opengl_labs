// Computer Graphics
//
// windows headers
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>

// linux headers
/*
#include <GL/freeglut.h>
#include <GL/gl.h>
*/

// other headers
#include <ctime>
#include <iostream>
#include <math.h>

const int screenWidth = 640;
const int screenHeight = 480;
GLdouble A, B, C, D;  // values used for scaling and shifting
bool filled = true;
int drawState;       // 1 for draw graph, 2 for entering point, 3 draw poly

struct GLintPoint {
  GLint x, y;
};

const int MAX_PTS = 10;
GLintPoint pts[MAX_PTS];
int NoOfPts=0;

float randFloat()
{
  float randomFloat = (float)rand()/RAND_MAX;
  return randomFloat;
}

void myInit(void)
{
  srand((unsigned)time(0));        // initialize the srand
  glClearColor(1.0,1.0,1.0,0.0);   // background color is white
  glColor3f(0.0f, 0.0f, 0.0f);     // drawing color is black
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);

  A = screenWidth / 14.0; // set values used for scaling and shifting
  B = 0.0;
  C = D = screenHeight / 2.0;
}

void myMouse(int button, int state, int x, int y)
{
  // store the mouse location into the pts[],
  // and increment # of points
  if (state == GLUT_DOWN)
  {
    std::cout << NoOfPts << ": " << x << " " << y << std::endl;
    pts[NoOfPts].x = x;
    pts[NoOfPts].y = screenHeight - y;
    NoOfPts++;
    if (button == GLUT_LEFT_BUTTON)
    {
      if (drawState == 3 || drawState == 1)
      {
        // we just drew a pollygon, lets reset buffer
        pts[MAX_PTS];
        NoOfPts=0;
      }
      drawState = 2;
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
      drawState = 3;
    }
    glutPostRedisplay();
  }
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
  switch(theKey) {
      case 'c':
        {
          // change the current foreground color into a new one 
          glColor3f( randFloat(), randFloat(), randFloat() );
          break;
        }
      case 'p':
        // indicate that the display function needs to draw a graph
        drawState = 1;
        break;
      case 's':
        // toggle the drawing mode between filled and unfilled polygon
        filled = !filled;
        break;
        default:
      break;      // do nothing
  }

  glutPostRedisplay(); // implicitly call myDisplay
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

  // draw either a cosine graph or a polygon(rectangle) using the points in pts[]
  // To access a point in pts[], use the syntax like pts[index].x or pts[index].y
  switch (drawState)
  {
    case 1:
      glBegin(GL_POINTS);
      for(GLdouble x = 0; x < 4*M_PI ; x += 0.005)
      {
        GLdouble   func = cos(x);
        glVertex2d(A * x + B, C * func + D);
      }
      glEnd();
      glFlush();		   // send all output to display 
      break;
    case 3:
      if (filled)
      {
        glBegin(GL_POLYGON);
      } else
      {
        glBegin(GL_LINE_LOOP);
      }

      for (int i = 0; i < NoOfPts; i++)
      {
        std::cout << i << ": " <<pts[i].x << " " << pts[i].y << std::endl;
        glVertex2i(pts[i].x,pts[i].y);
      }
      glEnd();
      glFlush();
      break;
  }

  glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
  glutInit(&argc, argv);          // initialize the toolkit
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
  glutInitWindowSize(screenWidth, screenHeight); // set window size
  glutInitWindowPosition(100, 150); // set window position on screen
  glutCreateWindow("Computer Graphics - Lab"); // open the screen window

  glutDisplayFunc(myDisplay);     // register redraw function
  glutMouseFunc(myMouse);
  glutKeyboardFunc(myKeyboard);

  myInit();

  glutMainLoop(); 		     // go into a perpetual loop
  return 0;
}
