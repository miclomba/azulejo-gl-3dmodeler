#include "modeler/UserInterface.h"

#include "Entities/Entity.h"

using _3dmodeler::UserInterface;
using entity::Entity;

namespace
{
    const std::string UI_KEY = "UI";
}

std::string UserInterface::UserInterfaceKey()
{
    return UI_KEY;
}

UserInterface::UserInterface() : Entity()
{
    SetKey(UI_KEY);
}

void UserInterface::Draw(GLint _w, GLint _h)
{
    w_ = _w;
    h_ = _h;
    DrawWindows();
    DrawLabelAxis();
}

void UserInterface::DrawWindows()
{
    glViewport(0, 0, w_, h_);
    glColor3f(1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w_, 0, h_);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_LINES);
    glVertex2i(w_ / 2, 0);
    glVertex2i(w_ / 2, h_);
    glVertex2i(0, h_ / 2);
    glVertex2i(w_, h_ / 2);
    glEnd();
}

void UserInterface::DrawLabelAxis()
{
    //=============== Draw labels for the "top" viewport =======================
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(15, 15);
    glVertex2i(15, 45);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(13, 50);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(15, 15);
    glVertex2i(45, 15);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2i(50, 13);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');

    //=============== Draw labels for the "front" viewport =====================
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(15 + w_ / 2, 15);
    glVertex2i(15 + w_ / 2, 45);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2i(13 + w_ / 2, 50);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(15 + w_ / 2, 15);
    glVertex2i(45 + w_ / 2, 15);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2i(50 + w_ / 2, 13);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');

    //=============== Draw labels for the "side" viewport ======================
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(15, 15 + h_ / 2);
    glVertex2i(15, 45 + h_ / 2);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(13, 50 + h_ / 2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2i(15, 15 + h_ / 2);
    glVertex2i(45, 15 + h_ / 2);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2i(50, 13 + h_ / 2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');

    //=============== Draw labels for the "perspective" viewport ===============
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2i(13 + w_ / 2, 15 + h_ / 2);
    char *c = (char *)"Press x,X,y,Y,z,Z to rotate; t,T to texture; l to light.";
    for (c = c; *c; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
}
