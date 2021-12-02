#include <GLUT.h>
#include<iostream>
#include<cstdlib>

#include <cmath>
#include <cstdio>
#include <string>

#define PI 3.14159265f

char title[] = "Sphere and Okto";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;

GLfloat xPos = -1.0f;
GLfloat yPos = 0.0f;
GLfloat zPos = -3.0f;
GLfloat xPosMax, xPosMin, yPosMax, yPosMin;
GLdouble xLeft, xRight, yBottom, yTop;
int refreshMillis = 30;
GLfloat radius = 0.5f;
GLfloat angle;

bool time_to_move = false;    //триггер на разъезд граней

GLfloat xMove = 0.0f;
GLfloat yMove = 0.0f;
GLfloat zMove = -4.0f;
GLfloat zMoveBack = -4.0f;
GLfloat zMoveFront = -4.0f;


int go_back = -1;
int i = 0;

GLuint okto[8];

void Draw(int angle_1, int x, int y, int z,
    int is_right, int is_back, int is_lower, int da)
{
    GLfloat triangle[3][3] =
    {
        {0, 0.1, 0},
        {0.1, 0, 0},
        {0, 0, 0.1}
    };

    float x_t = 0.1, y_t = 0, z_t = 0.1;
    glScalef(3, 3, 3);

    glRotatef(angle_1, x, y, z);
    if (is_lower == 1)
        glRotatef(90, 1, 0, 0); //нижние панели



    if (da == 1)
    {
        glRotatef(180, 1, 0, 0);
        glTranslatef(0, 0.8, 0);
    }
    glColor3f(1, 0, 1);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, triangle);
    glDrawArrays(GL_LINE_LOOP, 0, 3);


    for (int i = 0; i < 2; i++)
    {    
        x_t += 0.1;
        y_t -= 0.1;
        z_t += 0.1;
        GLfloat trap_1[4][3] =
        {
            {x_t - 0.1, y_t + 0.1, 0},
            {0, y_t + 0.1, z_t - 0.1},
            {0, y_t, z_t},
            {x_t, y_t, 0}
        };

        glVertexPointer(3, GL_FLOAT, 0, trap_1);
        glDrawArrays(GL_QUADS, 0, 4);

        GLfloat trap_2[4][3] =
        {
            {0, y_t, z_t},
            {x_t, y_t, 0},
            {x_t + 0.1, y_t - 0.1, 0},
            {0, y_t - 0.1, z_t + 0.1}
        };

        glVertexPointer(3, GL_FLOAT, 0, trap_2);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        x_t += 0.1;
        y_t -= 0.1;
        z_t += 0.1;
    }

    GLfloat big_triangle[3][3] = 
    {
        {0, 0.1, 0},
        {0, y_t, z_t},
        {x_t, y_t, 0}
    };
    

    glVertexPointer(3, GL_FLOAT, 0, big_triangle);
    glDrawArrays(GL_LINE_LOOP, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int pos[4][7] = {
    {0, 0, 0, 0, 1, -1, -1},
    {90, 0, 1, 0, 1, 1, -1},
    {180, 0, 1, 0, -1, 1, -1},
    {-90, 0, 1, 0, -1, -1, -1}
    /*{0, 0, 0, 0, 1, -1, 1},
    {-90, 0, 1, 0, -1, -1, 1},
    {180, 0, 1, 0, -1, 1, 1},
    {90, 0, 1, 0, 1, 1, 1}*/
};

void initGL()
{
    GLfloat panel[3][3] =
    {
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };

    for (int i = 0; i < 4; i++)
    {
        okto[i] = glGenLists(1);

        glNewList(okto[i], GL_COMPILE);
            Draw(pos[i][0], pos[i][1], pos[i][2], pos[i][3], 
                 pos[i][4], pos[i][5], pos[i][6], 0);
        glEndList();
    }


    for (int k = 4, i = 0; k < 8; i++, k++)
    {
        okto[k] = glGenLists(1);
        glNewList(okto[k], GL_COMPILE);
        Draw(pos[i][0], pos[i][1], pos[i][2], pos[i][3],
            pos[i][4], pos[i][5], pos[i][6], 1);
        glEndList();
    }

    glLoadIdentity();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Draw_quadrat()
{
    float x_t = 0.1, y_t = 0, z_t = 0.1;

    glNormal3f(0, 0, 1);

    glColor3f(1, 0, 1);
    glLineWidth(1.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    
    for (int i = 0; i < 3; i++)
    {
        GLfloat triangle[3][3] =
        {
            {0, 0.1, 0},
            {x_t, y_t, 0},
            {0, y_t, z_t}
        };
       
        glVertexPointer(3, GL_FLOAT, 0, triangle);
        glDrawArrays(GL_LINE_LOOP, 0, 3);
        x_t += 0.1;
        y_t -= 0.1;
        z_t += 0.1;
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw okto
    for (int i = 0; i < 8; i++)
    {
        if (pos[i][5] == -1)
            glTranslatef(pos[i][4] * xMove, -pos[i][6] * yMove, zMoveBack);
        else
            glTranslatef(pos[i][4] * xMove, -pos[i][6] * yMove, zMoveFront);

        glCallList(okto[i]);
        glLoadIdentity();
    }

    glutSwapBuffers();
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

    glLoadIdentity();
    glFrustum(xLeft, xRight, yBottom, yTop, 0.7, 20);

    glEnable(GL_DEPTH_TEST);


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
    initGL();
    glutMainLoop();
    glDisable(GL_LIGHT0);
    return 0;
}