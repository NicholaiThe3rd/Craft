#include "loadSaveMenu.h"
#include <GL/glut.h>
#include <GL/freeglut.h>

void renderLoadButtonBackground(void)
{
glColor3f (0.5, 0.5, 0.5);
glBegin(GL_POLYGON);
glVertex3f (0.30, 0.60, 0.0);
glVertex3f (0.65, 0.60, 0.0);
glVertex3f (0.65, 0.75, 0.0);
glVertex3f (0.30, 0.75, 0.0);
glEnd();
}

void renderLoadSaveMenu(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glutSwapBuffers();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //creates the title
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.42, 0.90);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Choose Save To Load");
    glPopMatrix();

//back button
    glPushMatrix();
    glTranslatef(-0.2, 0.3, 0.0);
    glColor3f (0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f (0.25, 0.60, 0.0);
    glVertex3f (0.35, 0.60, 0.0);
    glVertex3f (0.35, 0.65, 0.0);
    glVertex3f (0.25, 0.65, 0.0);
    glEnd();
    glPopMatrix();

//back button text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.09, 0.92);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Back");
    glPopMatrix();

//first button
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    renderLoadButtonBackground();
    glPopMatrix();

//first button text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.45, 0.76);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "World 1");
    glPopMatrix();

//second button
    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    renderLoadButtonBackground();
    glPopMatrix();

//second button text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.45, 0.46);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "World 2");
    glPopMatrix();

//third button
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    renderLoadButtonBackground();
    glPopMatrix();

//third buton text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.45, 0.16);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "World 3");
    glPopMatrix();

    glutSwapBuffers();
}