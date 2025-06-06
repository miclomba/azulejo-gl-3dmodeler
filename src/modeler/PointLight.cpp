#include "modeler/PointLight.h"

#include <array>
#include <string>

using _3dmodeler::PointLight;
using entity::Entity;

namespace
{
    const std::string POINT_LIGHT_KEY = "PointLight";
}

std::string PointLight::PointLightKey()
{
    return POINT_LIGHT_KEY;
}

std::array<std::array<GLfloat, 4>, 2> &PointLight::GetPosition()
{
    return position_;
}

void PointLight::Draw(GLenum _renderMode)
{
    glPointSize(7.0);
    glColor3f(1.0f, 1.0f, 0.0f);

    if (_renderMode == GL_SELECT)
        glLoadName(17);
    glBegin(GL_POINTS);
    glVertex3f(position_[0][0], position_[0][1], position_[0][2]);
    glEnd();

    if (_renderMode == GL_SELECT)
        glLoadName(18);
    glBegin(GL_POINTS);
    glVertex3f(position_[1][0], position_[1][1], position_[1][2]);
    glEnd();
}

PointLight::PointLight() : Entity()
{
    SetKey(POINT_LIGHT_KEY);

    position_ = {{{{-3, 3, 1, 1}},
                  {{3, -3, 1, 1}}}};

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, position_[0].data());
    glLightfv(GL_LIGHT1, GL_POSITION, position_[1].data());

    GLfloat specular[] = {0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

    GLfloat ambient[] = {0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);

    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}
