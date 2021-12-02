#include <GLUT.h>
#include<iostream>
#include<cstdlib>

#include <cmath>
#include <cstdio>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = -0.02f;
GLfloat zSpeed = 0.02f;
int refreshMillis = 30;
GLfloat radius = 0.5f;
GLfloat angle;



bool time_to_move = false;    //триггер на разъезд граней
bool textures_enable = false; //триггер на включение текстур

GLfloat xMove = 0.0f;
GLfloat yMove = 0.0f;
GLfloat zMove = -4.0f;
GLfloat zMoveBack = -4.0f;
GLfloat zMoveFront = -4.0f;


int go_back = -1;
int i = 0;

//textures
GLuint textures[9];
int picture = 0;
int is_texture = 0;

//alpha chanel
float alpha = 1;

void initGL() 
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   
}

void Texture_Init()
{
    int w, h;
    int count;

    unsigned char* data = NULL;
    glGenTextures(9, textures);

    for (picture; picture < 9; picture++)
    {
        switch (picture)
        {
            case 0:
                data = stbi_load("stone.jpg", &w, &h, &count, 0);
                break;
            case 1:
                data = stbi_load("metal.jpg", &w, &h, &count, 0);
                break;
            case 2:
                data = stbi_load("tkan.jpg", &w, &h, &count, 0);
                break;
            case 3:
                data = stbi_load("texture_tree_2.jpg", &w, &h, &count, 0);
                break;
            case 4:
                data = stbi_load("dod.jpg", &w, &h, &count, 0);
                break;
            case 5:
                data = stbi_load("glass-texture.jpg", &w, &h, &count, 0);
                break;
            case 6:
                data = stbi_load("galka.jpg", &w, &h, &count, 0);
                break;
            case 7:
                data = stbi_load("krasivo.jpg", &w, &h, &count, 0);
                break;
            default:
                stbi_image_free(data);
                return;
        }

        glBindTexture(GL_TEXTURE_2D, textures[picture]);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, count == 4 ? GL_RGBA : GL_RGB, w, h,
                                        0, count == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    stbi_image_free(data);
    picture = 0;
}


float texCoord[] = { 1,1, 1,0, 0,0, 0,1 };

void Draw(float angle_1, int x, int y, int z, 
    int is_right, int is_back, int is_lower)
{
    //бокова€ дальн€€
    GLfloat panel[3][3] =
    {
        {0, 0, 1},
        {0, 1, 0},
        {1, 0, 0}
    };


    if(is_back == -1)
        glTranslatef(is_right * xMove, -is_lower * yMove, zMoveBack);
    else
        glTranslatef(is_right * xMove, -is_lower * yMove, zMoveFront);
    glNormal3f(is_right, -is_lower, is_back);

    glRotatef(angle_1, x, y, z);
    if (is_lower == 1)
        glRotatef(90, 1, 0, 0); //нижние панели
    
    glEnable(GL_TEXTURE_2D);
  
    if (!textures_enable)
        picture = 8;

    glBindTexture(GL_TEXTURE_2D, textures[picture]);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glColor4f(1, is_texture, 1, alpha);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, panel);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    picture++;
}

void Draw_quadrat()
{
    GLfloat quadrat[4][3] =
    {
        {0,0,0},
        {0.5, 0.5, 0},
        {1, 0, 0}
    };

   
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[picture]);

    glNormal3f(0, 0, 1);
    
    glColor3f(1, 1, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, quadrat);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void display()
{
    picture = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLUquadricObj* quadObj;
    quadObj = gluNewQuadric();

    //draw sphere
    glPushMatrix();
    int numSegments = 400;
    if (i == numSegments)
        i = 0;

    angle = i * 2.0f * PI / numSegments;
    glTranslatef(cos(angle) * radius * 4, 0, sin(angle) * radius * 4 - 3.5); //2 - 3
    i++;

    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat back_diffuse[] = { 1.0, 1.0, 1.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_BACK, GL_DIFFUSE, back_diffuse);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);


    glColor4f(1, 0, 1, alpha);
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluSphere(quadObj, radius, 25, 25);
    glPopMatrix();
    gluDeleteQuadric(quadObj);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //draw okto //is_right is_back is_lower
    //нижние
    Draw(0, 0, 0, 0, 1, -1, 1);         //права€ передн€€ нижн€€
    glLoadIdentity();
    Draw(-90, 0, 1, 0, -1, -1, 1);      //лева€ передн€€ нижн€€
    glLoadIdentity();
    Draw(180, 0, 1, 0, -1, 1, 1);       //лева€ задн€€ нижн€€
    glLoadIdentity();
    Draw(90, 0, 1, 0, 1, 1, 1);         //права€ задн€€ нижн€€
    glLoadIdentity();

    //верхние
    Draw(90, 0, 1, 0, 1, 1, -1);         //права€ задн€€ верхн€€
    glLoadIdentity();
    Draw(180, 0, 1, 0, -1, 1, -1);       //лева€ задн€€ верхн€€
    glLoadIdentity();
    Draw(0, 0, 0, 0, 1, -1, -1);         //права€ передн€€ верхн€€
    glLoadIdentity();
    Draw(-90, 0, 1, 0, -1, -1, -1);      //лева€ передн€€ верхн€€
    glLoadIdentity();
   

    
    /*glTranslatef(0,0,-1);
    Draw_quadrat();
    glLoadIdentity();*/



    
    glutSwapBuffers();


    //glLoadIdentity();
    xPos += xSpeed;
    yPos += ySpeed;
    zPos += zSpeed;


    if (time_to_move)
    {
        xMove += go_back * 0.01;
        yMove += go_back * 0.01;
        zMoveBack += go_back * 0.01;
        zMoveFront -= go_back * 0.01;
    }
    if (xMove > 0.2)
    {
        time_to_move = false;
    }

    if (xMove == 0 || xMove < 0)
    {
        time_to_move = false;
    }
    if (xPos > xRight || xPos < xLeft)
    {
        xSpeed *= -1;
        ySpeed *= -1;
    }
    if ((xPos > 0 && zSpeed > 0) || (xPos < 0 && zSpeed < 0))
        zSpeed *= -1;
    glDisable(GL_BLEND);
}

void mouseButton(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON) 
    {
        if (state == GLUT_UP && time_to_move == false) 
        {
            time_to_move = true; 
            go_back *= -1;
        }
        else if (state == GLUT_UP && time_to_move == true)
        {
            time_to_move = false;
            go_back *= -1;
        }
    }
}

void processSpecialKeys(int key, int x, int y) 
{
    //textures
    if (key == GLUT_KEY_DOWN)
    {
        textures_enable = true;
        is_texture = 1;
    }
    if (key == GLUT_KEY_UP)
    {
        textures_enable = false;
        is_texture = 0;
    }

    //alpha chanel
    if (key == GLUT_KEY_LEFT)
        alpha = 1;
    if (key == GLUT_KEY_RIGHT)
        alpha = 0.5;
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
    //glOrtho(xLeft, xRight, yBottom, yTop, 1,20);
    glFrustum(xLeft, xRight, yBottom, yTop, 0.7, 20);
    //gluPerspective(120, (GLdouble)weight / height, 0.1, 5.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    xPosMin = xLeft + radius;
    xPosMax = xRight - radius;
    yPosMin = yBottom + radius;
    yPosMax = yTop - radius;

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
    glutMouseFunc(mouseButton);
    glutSpecialFunc(processSpecialKeys);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, Timer, 0);
    initGL();
    Texture_Init();
    glutMainLoop();
    glDisable(GL_LIGHT0);
    return 0;
}