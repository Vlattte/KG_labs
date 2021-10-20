#include <GLUT.h>
#include<iostream>
#include<cstdlib>

#include <cmath>
#include <cstdio>

#define PI 3.14159265f

char title[] = "Sun Rise";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;

GLfloat ballRadius = 0.25f;
GLfloat xPos = -1.5f;
GLfloat yPos = 0.0f;
GLfloat xPosMax, xPosMin, yPosMax, yPosMin;
GLdouble xLeft, xRight, yBottom, yTop;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.02f;
int refreshMillis = 30;

int day_mode = 1;
float n = 1.0f;


void initGL() {
   glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    
   /* verticies[0][0] = xLeft;
    verticies[0][1] = yBottom;

    verticies[1][0] = xLeft;
    verticies[1][0] = 0.0f;

    verticies[2][0] = xRight;
    verticies[2][1] = 0.0f;

    verticies[3][0] = xRight;
    verticies[3][1] = yBottom;*/
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    //GLfloat light2_diffuse[] = { 0.4, 0.7, 0.2 };
    //GLfloat light2_position[] = { xPos, yPos, 1.0, 1.0 };

    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT2);

    //glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    //glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    //glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
    //glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
    //glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4);
    //yPos = yTop - 2 * ballRadius;

    
   


   
    //circle
    glTranslatef(xPos, sin(yPos), 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        if(day_mode == 1)
            glColor3f(0.9f, 0.9f, 0.0f);
        else
            glColor3f(0.9f, 0.9f, 0.9f);
        glVertex2f(0.0f, 0.0f);
        int numSegments = 100;
        GLfloat angle;
        for (int i = 0; i <= numSegments; i++)
        {
            angle = i * 2.0f * PI / numSegments;
            glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
        }
    glEnd();

    glLoadIdentity();


    //grass
    GLfloat grass_verties[4][2] =
    {
        {xLeft, yBottom},
        {xLeft, 0.0f},
        {xRight, 0.0f},
        {xRight, yBottom}
    };

    glVertexPointer(2, GL_FLOAT, 0, grass_verties);
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.0f, n, 0.0f);
        glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);


    /*glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(xLeft, yBottom);
        glVertex2f(xLeft, 0);
        glVertex2f(xRight, 0);
        glVertex2f(xRight, yBottom);
    glEnd();*/

//HOUSE LEFT

    //house
    GLfloat lHouseVert[4][2] =
    {
        {xLeft * 0.6, 0},
        {xLeft * 0.6, yTop * 0.2},
        {xLeft * 0.8, yTop * 0.2},
        {xLeft * 0.8, 0}
    };

    glVertexPointer(2, GL_FLOAT, 0, lHouseVert);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.64f, 0.4f, 0.4f);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    //glBegin(GL_TRIANGLE_FAN);
    //    glColor3f(0.64f, 0.4f, 0.4f);
    //    glVertex2f(xLeft * 0.6, 0);
    //    glVertex2f(xLeft * 0.6, yTop * 0.2);
    //    glVertex2f(xLeft * 0.8, yTop * 0.2);
    //    glVertex2f(xLeft * 0.8, 0);
    //glEnd();

    //roof
    GLfloat lRoofVert[3][2] =
    {
        {xLeft * 0.55, yTop * 0.2},
        {xLeft * 0.7, yTop * 0.4},
        {xLeft * 0.85, yTop * 0.2}
    };

    glVertexPointer(2, GL_FLOAT, 0, lRoofVert);
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.64f, 0.16f, 0.16f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);


    /*glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.64f, 0.16f, 0.16f);
        glVertex2f(xLeft * 0.55, yTop * 0.2);
        glVertex2f(xLeft * 0.7, yTop * 0.4);
        glVertex2f(xLeft * 0.85, yTop * 0.2);
    glEnd();*/

    //door
    GLfloat lDoorVert[4][2] =
    {
        {xLeft * 0.71, 0},
        {xLeft * 0.71, yTop * 0.1},
        {xLeft * 0.75, yTop * 0.1},
        {xLeft * 0.75, 0}
    };

    glVertexPointer(2, GL_FLOAT, 0, lDoorVert);
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.0f, 0.0f, 0.0f);
        glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    
    /*glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(xLeft * 0.71, 0);
        glVertex2f(xLeft * 0.71, yTop * 0.1);
        glVertex2f(xLeft * 0.75, yTop * 0.1);
        glVertex2f(xLeft * 0.75, 0);
    glEnd();*/


//HOUSE RIGHT

    //house
    GLfloat rHouseVert[4][2] =
    {
        {xRight * 0.6, 0},
        {xRight * 0.6, yTop * 0.2},
        {xRight * 0.8, yTop * 0.2},
        {xRight * 0.8, 0}
    };

    glVertexPointer(2, GL_FLOAT, 0, rHouseVert);
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.64f, 0.4f, 0.4f);
        glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    /*glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.64f, 0.4f, 0.4f);
        glVertex2f(xRight * 0.6, 0);
        glVertex2f(xRight * 0.6, yTop * 0.2);
        glVertex2f(xRight * 0.8, yTop * 0.2);
        glVertex2f(xRight * 0.8, 0);
    glEnd();*/

    //roof
    GLfloat rRoofVert[3][2] =
    {
        {xRight * 0.55, yTop * 0.2},
        {xRight * 0.7, yTop * 0.4},
        {xRight * 0.85, yTop * 0.2}
    };

    glVertexPointer(2, GL_FLOAT, 0, rRoofVert);
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.64f, 0.16f, 0.16f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    /*glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.64f, 0.16f, 0.16f);
        glVertex2f(xRight * 0.55, yTop * 0.2);
        glVertex2f(xRight * 0.7, yTop * 0.4);
        glVertex2f(xRight * 0.85, yTop * 0.2);
    glEnd();*/

    //door
    GLfloat rDoorVert[4][2] =
    {
        {xRight * 0.71, 0},
        {xRight * 0.71, yTop * 0.1},
        {xRight * 0.75, yTop * 0.1},
        {xRight * 0.75, 0}
    };

    glVertexPointer(2, GL_FLOAT, 0, rDoorVert);
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.0f, 0.0f, 0.0f);
        glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    /*glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(xRight * 0.71, 0);
        glVertex2f(xRight * 0.71, yTop * 0.1);
        glVertex2f(xRight * 0.75, yTop * 0.1);
        glVertex2f(xRight * 0.75, 0);
    glEnd();*/

    glutSwapBuffers();

    xPos += xSpeed;
        yPos += ySpeed;
    if (xPos > xRight * 1.7)
    {
        xPos = xLeft;
        yPos = 0;
        day_mode *= -1;



        if (day_mode == 1)
        {
            glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
            n = 0.8f;
        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.8f, 0.0f);
            n = 0.5f;
        }

    }
  
   /* glDisable(GL_LIGHTING);

    glDisable(GL_LIGHT1);*/
}


void reshape(GLsizei weight, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)weight / height;

    glViewport(0, 0, weight, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (weight <= height) {
        xLeft = -1.0;
        xRight = 1.0;
        yBottom = -1.0 / aspect;
        yTop = 1.0 / aspect;
    }
    else {
        xLeft = -1.0 * aspect;
        xRight = 1.0 * aspect;
        yBottom = -1.0;
        yTop = 1.0;
    }
    gluOrtho2D(xLeft, xRight, yBottom, yTop);
    xPosMin = xLeft + ballRadius;
    xPosMax = xRight - ballRadius;
    yPosMin = yBottom + ballRadius;
    yPosMax = yTop - ballRadius;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(refreshMillis, Timer, 0);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutCreateWindow(title);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, Timer, 0);
    initGL();
    glutMainLoop();
    return 0;
}