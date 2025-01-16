#include "PointLight.h"

using _3dmodeler::PointLight;

void PointLight::display(GLenum _renderMode) {
    glPointSize(7.0);
    glColor3f(1.0f,1.0f,0.0f);

    if (_renderMode == GL_SELECT)
        glLoadName(17);
    glBegin(GL_POINTS);
        glVertex3f(position_[0][0],position_[0][1],position_[0][2]);
    glEnd();

    if (_renderMode == GL_SELECT)
        glLoadName(18);
    glBegin(GL_POINTS);
        glVertex3f(position_[1][0],position_[1][1],position_[1][2]);
    glEnd();
}

PointLight::PointLight() {
    position_[0][0] = -3;
    position_[0][1] = 3;
    position_[0][2] = 1;
    position_[0][3] = 1;

    position_[1][0] = 3;
    position_[1][1] = -3;
    position_[1][2] = 1;
    position_[1][3] = 1;

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, position_[0]);
    glLightfv(GL_LIGHT1, GL_POSITION, position_[1]);

    GLfloat specular[] = {0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

    GLfloat ambient[] = { 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}


