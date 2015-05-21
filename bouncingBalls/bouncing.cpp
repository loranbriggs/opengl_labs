//Computer Graphics Lab : Drawing an object and changing world view

#include "bouncing.h"


void myInit(void)
{
    srand((unsigned)time(0));        // initialize the srand

    addBall();

    left.x = 1; left.y = 0;
    top.x = 0; top.y = -1;
    right.x = -1; right.y = 0;
    bottom.x = 0; bottom.y = 1;
    glClearColor(0.9,0.9,0.9,0.0);       // background color is white
    setWindow(0, worldWidth, 0, worldHeight);
}

void myMouse(int button, int state, int x, int y)
{
    y = screenHeight - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        leftDown = true;
        mouseStart.x = x;
        mouseStart.y = y;
        for (int i = 0; i < ballCnt; i++)
        {
            float dist = sqrt( pow(balls[i].center.x - x, 2) + pow(balls[i].center.y - y, 2) );
            if (dist < balls[i].radius)
            {
                // we have clicked in a ball
                std::cout << "you clicked ball " << i+1 << std::endl;
                mouseSelected = i;
            }
        }
    } else
    {
        leftDown = false;
        mouseSelected = -1;
    }
}

void myMotion(int x, int y)
{
    if (leftDown && mouseSelected >= 0)
    {
        float dx = (mouseStart.x - x)*worldWidth/screenWidth;
        float dy = (mouseStart.y - y)*worldHeight/screenHeight;
        mouseStart.x = x;
        mouseStart.y = y;
        if (dx > 5) dx = 5;
        if (dx < -5) dx = -5;
        if (dy > 5) dy = 5;
        if (dy < -5) dy = -5;
        balls[mouseSelected].velocity.x = -dx;
        balls[mouseSelected].velocity.y = dy;
        if (balls[mouseSelected].freeze) balls[mouseSelected].freeze = false;
    }
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case ' ':
            break;
        case 'a':
            addBall();
            break;
        case 'r':
            removeBall();
            break;
        case 's':
            for (int i = 0; i < ballCnt; i++)
            {
                if (balls[i].freeze)
                {
                    unFreeze(balls[i]);
                } else
                {
                    balls[i].freeze = true;
                }
            }
            break;
        case '1':
            selectedBall = 0;
            break;
        case '2':
            selectedBall = 1;
            break;
        case '3':
            selectedBall = 2;
            break;
        case '4':
            selectedBall = 3;
            break;
        case '5':
            selectedBall = 4;
            break;
        case 'p':
            balls[selectedBall].filled = !balls[selectedBall].filled;
            break;
        case 'n':
            std::cout << "Restart!" << std::endl;
            ballCnt = 0;
            addBall();
            break;
        case 'q':
            std::cout << "Goodbye!" << std::endl;
            exit(0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey) {
        case GLUT_KEY_UP:
            balls[selectedBall].velocity.x *= 1.1;
            balls[selectedBall].velocity.y *= 1.1;
            break;
        case GLUT_KEY_DOWN:
            balls[selectedBall].velocity.x *= 0.9;
            balls[selectedBall].velocity.y *= 0.9;
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_PAGE_UP:
            balls[selectedBall].radius += 1;
            break;
        case GLUT_KEY_PAGE_DOWN:
            balls[selectedBall].radius -= 1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void myIdle()
{

    for (int i = 0; i < ballCnt; i++)
    {
        // check collision with boundries
        if (balls[i].center.x > worldWidth)
        {
            reflect(balls[i].velocity,right);
        }
        if (balls[i].center.x < 0)
        {
            reflect(balls[i].velocity,left);
        }
        if (balls[i].center.y > worldHeight)
        {
            reflect(balls[i].velocity,bottom);
        }
        if (balls[i].center.y < 0)
        {
            reflect(balls[i].velocity,top);
        }
        if (!balls[i].freeze)
        {
            balls[i].center.x += balls[i].velocity.x;
            balls[i].center.y += balls[i].velocity.y;
        }

        // check collision with other balls
        for (int j = i+1; j < ballCnt; j++)
        {
            checkCollision(balls[i], balls[j]);
        }
        glutPostRedisplay();
    }
}

void checkCollision(Ball &a, Ball &b)
{
    float dist = sqrt( pow(b.center.x - a.center.x, 2) + pow(b.center.y - a.center.y, 2) );
    if (dist < (a.radius + b.radius))
    {
        // Houston we have a collision
        if (a.freeze)
        {
            unFreeze(a);
        } else
        {
            a.velocity.x = -a.velocity.x;
            a.velocity.y = -a.velocity.y;
        }
        if (b.freeze)
        {
            unFreeze(a);
        } else
        {
            b.velocity.x = -b.velocity.x;
            b.velocity.y = -b.velocity.y;
        }
    }
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    mySleep(1);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    
    for (int b = 0; b < ballCnt; b++)
    {
        switch (b)
        {
            case 0:
                glColor3f(0.0f, 1.0f, 0.0f);         // drawing color
                break;
            case 1:
                glColor3f(1.0f, 1.0f, 0.0f);         // drawing color
                break;
            case 2:
                glColor3f(0.0f, 1.0f, 1.0f);         // drawing color
                break;
            case 3:
                glColor3f(1.0f, 0.0f, 1.0f);         // drawing color
                break;
            default:
                glColor3f(0.0f, 0.0f, 1.0f);         // drawing color
                break;
        }
        if (balls[b].filled)
            glBegin(GL_POLYGON);
        else
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 100; i += 1)
            {
                float t = i*1.0/100;
                GLfloat bx = balls[b].center.x + balls[b].radius*cos(2*PI*t);
                GLfloat by = balls[b].center.y + balls[b].radius*sin(2*PI*t);
                glVertex2f(bx,by);
            }
        glEnd();

        drawLabel(b, balls[b].center.x, balls[b].center.y);
    }


    //glFlush();
    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Bouncing Balls"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutIdleFunc(myIdle);			// register idle callback function

    myInit();

    glutMainLoop(); 		     // go into a perpetual loop
    return 0;
}

//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

float randFloat(float a, float b)
{
  float random = (float)rand()/RAND_MAX;
  return a + random*(b - a);
}

float randFloat()
{
    return randFloat(0,1);
}

void addBall()
{
    if (ballCnt == 0)
    {
        addBall(8, worldWidth/2, worldHeight/2, 0, 0);
        balls[0].freeze = true;
    } else if (ballCnt < MAX_BALLS)
    {
        float radius = randFloat(5,20);
        float      x = randFloat(0,worldWidth);
        float      y = randFloat(0,worldHeight);
        float     dx = randFloat(-20,20)/radius;  // larger balls move slower
        float     dy = randFloat(-20,20)/radius;  // than smaller balls
        addBall(radius, x,y,dx,dy);
    }
}

void addBall(float r, float x, float y, float dx, float dy)
{
    balls[ballCnt].radius = r;
    balls[ballCnt].center.x = x;
    balls[ballCnt].center.y = y;
    balls[ballCnt].velocity.x = dx;
    balls[ballCnt].velocity.y = dy;
    balls[ballCnt].freeze = false;
    balls[ballCnt].filled = true;
    ballCnt++;
}

void removeBall()
{
    if (ballCnt > MIN_BALLS)
    {
        ballCnt--;
    }
}

void unFreeze(Ball &ball)
{
    // if frozen, give it new velocity
    float dx = randFloat(-20,20)/ball.radius;  // larger balls move slower
    float dy = randFloat(-20,20)/ball.radius;  // than smaller balls
    ball.velocity.x = dx;
    ball.velocity.y = dy;
    ball.freeze = false;
}


int dot(GLintVec2 a, GLintVec2 b)
{
    return a.x*b.x + a.y*b.y;
}

float dot(GLfloatVec2 a, GLfloatVec2 b)
{
    return a.x*b.x + a.y*b.y;
}

void reflect(GLfloatVec2 &a, GLfloatVec2 b)
{
    float dx = -2*dot(a,b)*b.x + a.x;
    float dy = -2*dot(a,b)*b.y + a.y;
    a.x = dx;
    a.y = dy;
}

void drawLabel(int i, float x, float y)
{
    char c = x;
    switch (i)
    {
        case 0:
            c = '1';
            break;
        case 1:
            c = '2';
            break;
        case 2:
            c = '3';
            break;
        case 3:
            c = '4';
            break;
        case 4:
            c = '5';
            break;
    }
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color
    glPointSize(1.0);
    glPushMatrix();
        glTranslatef(x-3, y-3, 0);
        glScalef(0.1, 0.1, 0.1);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    glPopMatrix();
}

void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef WINDOWS
    Sleep(sleepMs);
#endif
}
