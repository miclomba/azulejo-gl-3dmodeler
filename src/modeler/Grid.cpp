#include "modeler/Grid.h"

#include <math.h>
#include <string>

#include "Entities/Entity.h"

using _3dmodeler::Grid;
using entity::Entity;

namespace
{
    const std::string GRID_KEY = "Grid";
    const int MAX_TEXTURES = 2;
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
}

std::string Grid::GridKey()
{
    return GRID_KEY;
}

void Grid::SetControlPoint(const GLfloat val, const int i, const int j, const int k)
{
    controlPoints_[i][j][k] = val;
}

void Grid::Draw(GLenum _mode)
{
    //===================== Draw Bezier Surface ================================

    glColor3f(1.0, 1.0, 1.0);

    if (curTexture_ == 1)
        MakeTexImage1();
    else if (curTexture_ == 2)
        MakeTexImage2();

    //===================== Apply material properties ==========================
    glMaterialfv(GL_FRONT, GL_AMBIENT, gold_Ka_.data());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_Kd_.data());
    glMaterialfv(GL_FRONT, GL_SPECULAR, gold_Ks_.data());
    glMaterialf(GL_FRONT, GL_SHININESS, gold_Ke_);
    glMaterialfv(GL_BACK, GL_AMBIENT, silver_Ka_.data());
    glMaterialfv(GL_BACK, GL_DIFFUSE, silver_Kd_.data());
    glMaterialfv(GL_BACK, GL_SPECULAR, silver_Ks_.data());
    glMaterialf(GL_BACK, GL_SHININESS, silver_Ke_);

    //===================== Apply textures properties ==========================
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, IMG_WIDTH, IMG_HEIGHT,
                 0, GL_RGB, GL_UNSIGNED_BYTE, image_.data());

    //=================== Create an evaluator for the grid =====================
    glMap2f(GL_MAP2_VERTEX_3, uRangeLow_, uRangeHigh_, uStride_, uOrder_,
            vRangeLow_, vRangeHigh_, vStride_, vOrder_,
            controlPoints_[0][0].data());
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2,
            0, 1, 4, 2,
            texturePoints_[0][0].data());

    //=========== Apply a grid subdivision of u and v to all evaluators ========
    glMapGrid2f(gridSubdivs_, uRangeLow_, uRangeHigh_,
                gridSubdivs_, vRangeLow_, vRangeHigh_);

    //=========== Evaluate mesh ================================================
    glEvalMesh2(GL_LINE, 0, gridSubdivs_, 0, gridSubdivs_);

    DrawControlPoints(_mode);
}

void Grid::DrawControlPoints(GLenum _mode)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPointSize(5.0);
    glColor3f(1.0f, 1.0f, 0.0f);

    GLint i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (_mode == GL_SELECT)
            {
                glLoadName(i * 4 + j + 1);
            }
            glBegin(GL_POINTS);
            glVertex3fv(controlPoints_[i][j].data());
            glEnd();
        }
    }
}

void Grid::InitGridPoints()
{

    GLfloat controlPoints[4][4][3] = {{{-2.0, -2.0, 0.0},
                                       {-0.5, -2.0, 0.0},
                                       {0.5, -2.0, 0.0},
                                       {2.0, -2.0, -2.0}},

                                      {{-2.0, -0.5, 0.0},
                                       {-0.5, -0.5, 0.0},
                                       {0.5, -0.5, 0.0},
                                       {2.0, -0.5, 0.0}},

                                      {{-2.0, 0.5, 0.0},
                                       {-0.5, 0.5, 0.0},
                                       {0.5, 0.5, 0.0},
                                       {2.0, 0.5, 0.0}},

                                      {{-2.0, 2.0, 0.0},
                                       {-0.5, 2.0, 0.0},
                                       {0.5, 2.0, 0.0},
                                       {2.0, 2.0, 0.0}}};

    GLfloat texturePoints[2][2][2] = {{{0.0f, 0.0f}, {0.0f, 1.0f}},
                                      {{1.0f, 0.0f}, {1.0f, 1.0f}}};

    GLint i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 3; k++)
                controlPoints_[i][j][k] = controlPoints[i][j][k];
        }
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            for (k = 0; k < 2; k++)
                texturePoints_[i][j][k] = texturePoints[i][j][k];
        }
    }
}

void Grid::MakeTexImage1()
{
    GLint i, j;
    GLfloat ti, tj;

    for (i = 0; i < IMG_WIDTH; i++)
    {
        ti = 2.0 * M_PI * i / IMG_WIDTH;
        for (j = 0; j < IMG_HEIGHT; j++)
        {
            tj = 2.0 * M_PI * j / IMG_WIDTH;
            image_[3 * (IMG_HEIGHT * i + j)] = (GLubyte)(127 * (1.0 + cos(ti)));
            image_[3 * (IMG_HEIGHT * i + j) + 1] = (GLubyte)(127 * (1.0 + sin(2 * tj)));
            image_[3 * (IMG_HEIGHT * i + j) + 2] = (GLubyte)(127 * (1.0 + sin(ti + tj)));
        }
    }
}

void Grid::MakeTexImage2()
{
    GLint i, j;
    GLfloat ti, tj;

    for (i = 0; i < IMG_WIDTH; i++)
    {
        ti = 2.0 * M_PI * i / IMG_WIDTH;
        for (j = 0; j < IMG_HEIGHT; j++)
        {
            tj = 2.0 * M_PI * j / IMG_WIDTH;
            image_[3 * (IMG_HEIGHT * i + j)] = (GLubyte)(127 * (1.0 + sin(ti)));
            image_[3 * (IMG_HEIGHT * i + j) + 1] = (GLubyte)(127 * (1.0 + tan(2 * tj)));
            image_[3 * (IMG_HEIGHT * i + j) + 2] = (GLubyte)(127 * (1.0 + tan(ti + tj)));
        }
    }
}

void Grid::ChangeTextures()
{
    if (curTexture_ < MAX_TEXTURES)
        curTexture_ += 1;
    else
        curTexture_ = 1;
}

Grid::Grid() : Entity()
{
    SetKey(GRID_KEY);

    glEnable(GL_MAP2_VERTEX_3);

    //================== Create textures and init mesh points ==================
    MakeTexImage1();
    MakeTexImage2();
    InitGridPoints();

    //===================== Initialize member variables ========================

    curTexture_ = 1;

    gridSubdivs_ = 16.0f;

    uOrder_ = 4;
    uRangeLow_ = 0;
    uRangeHigh_ = 1;
    uStride_ = 3;

    vOrder_ = 4;
    vRangeLow_ = 0;
    vRangeHigh_ = 1;
    vStride_ = uStride_ * 4;

    GLfloat gold_Ka[4] = {0.24725f, 0.1995f, 0.0745f, 1.0f};
    GLfloat gold_Kd[4] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
    GLfloat gold_Ks[4] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
    GLfloat gold_Ke = 41.2f;
    GLfloat silver_Ka[4] = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat silver_Kd[4] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat silver_Ks[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat silver_Ke = 12.0f;

    GLint i;
    for (i = 0; i < 4; i++)
    {
        gold_Ka_[i] = gold_Ka[i];
        gold_Kd_[i] = gold_Kd[i];
        gold_Ks_[i] = gold_Ks[i];
        silver_Ka_[i] = silver_Ka[i];
        silver_Kd_[i] = silver_Kd[i];
        silver_Ks_[i] = silver_Ks[i];
    }

    gold_Ke_ = gold_Ke;
    silver_Ke_ = silver_Ke;
}
