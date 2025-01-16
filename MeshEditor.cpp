#include "MeshEditor.h"

using _3dmodeler::MeshEditor;

namespace {
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 480;
const int BUFFER_SIZE = 256;
}

MeshEditor* MeshEditor::callback_(NULL);

void MeshEditor::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //===================== Display a user interface ===========================
    userInterf_->display(w_,h_);
    
    glEnable(GL_SCISSOR_TEST);

        //===================== Draw bottom left viewport ======================
        glViewport(0,0,w_/2,h_/2);
        glScissor(0,0,w_/2,h_/2);
        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(projOrtho_);
        glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (moving_ == true && dragging_ == true && curViewport_ == "top") {
                topY_ = yo_ + panY_/20;
                topX_ = xo_ - panX_/20;
            }
            gluLookAt(topX_,topY_,1,topX_,topY_,0,0,1,0);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        lights_->display(renderMode_);
        if (toggleLights_ == true)
            glEnable(GL_LIGHTING);
        if (toggleTextures_ == true)
            glEnable(GL_TEXTURE_2D);
        grid_->display(renderMode_);
            glLoadIdentity();

        //===================== Draw top left viewport =========================
        glViewport(0,h_/2 + 1,w_/2,h_/2);
        glScissor(0,h_/2 + 1,w_/2,h_/2);
        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(projOrtho_);
        glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (moving_ == true && dragging_ == true && curViewport_ == "side"){
                sideY_ = yo_ + panY_/20;
                sideZ_ = xo_ - panX_/20;
            }
            gluLookAt(-1,sideY_,sideZ_,0,sideY_,sideZ_,0,1,0);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        lights_->display(renderMode_);
        if (toggleLights_ == true)
            glEnable(GL_LIGHTING);
        if (toggleTextures_ == true)
            glEnable(GL_TEXTURE_2D);
        grid_->display(renderMode_);
            glLoadIdentity();

        //===================== Draw bottom right viewport =====================
        glViewport(w_/2 + 1,0,w_/2,h_/2);
        glScissor(w_/2 + 1,0,w_/2,h_/2);
        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(projOrtho_);
        glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            if (moving_ == true && dragging_ == true && curViewport_=="front") {
                frontZ_ = yo_ + panY_/20;
                frontX_ = xo_ - panX_/20;
            }
            gluLookAt(frontX_,-1,frontZ_,frontX_,0,frontZ_,0,0,1);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        lights_->display(renderMode_);
        if (toggleLights_ == true)
            glEnable(GL_LIGHTING);
        if (toggleTextures_ == true)
            glEnable(GL_TEXTURE_2D);
        grid_->display(renderMode_);
            glLoadIdentity();

        //===================== Draw top right viewport ========================
        glViewport(w_/2 + 1,h_/2 + 1,w_/2,h_/2);
        glScissor(w_/2 + 1,h_/2 + 1,w_/2,h_/2);
        glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glLoadMatrixf(projPerspective_);
        glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(-10,0,-10,0,0,0,0,1,0);
            glRotatef(zPhi_,0.0f,0.0f,1.0f);
            glRotatef(yTheta_,0.0f,1.0f,0.0f);
            glRotatef(xPsi_,1.0f,0.0f,0.0f);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        lights_->display(renderMode_);
        if (toggleLights_ == true)
            glEnable(GL_LIGHTING);
        if (toggleTextures_ == true)
            glEnable(GL_TEXTURE_2D);
        grid_->display(renderMode_);
            glLoadIdentity();

    glDisable(GL_SCISSOR_TEST);

    glFlush();
    glutSwapBuffers();
}

void MeshEditor::reshape(int _w, int _h) {
    w_ = _w;
    h_ = _h;

    GLint i;
    GLdouble projection[16];

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //========================= Ortho Projection ===========================
        if ( _w/2 <= _h/2 )
            glOrtho(-5.0,5.0,-5.0*((GLfloat)(_h/2) / (GLfloat)(_w/2)),
                     5.0*((GLfloat)(_h/2) / (GLfloat)(_w/2)),10.0,-200.0);
        else
            glOrtho(-5.0*((GLfloat)(_w/2) / (GLfloat)(_h/2)),
                    5.0*((GLfloat)(_w/2)/(GLfloat)(_h/2)),-5.0,5.0,10.0,-200.0);

        glGetDoublev(GL_PROJECTION_MATRIX,projection);
        for (i = 0; i < 16; i++) projOrtho_[i] = projection[i];
    
        glLoadIdentity();
        //========================= Perspective Projection =====================
        gluPerspective(40.0,(GLdouble)_w/(GLdouble)_h,0.5,200.0);
    
        glGetDoublev(GL_PROJECTION_MATRIX,projection);
        for (i = 0; i < 16; i++) projPerspective_[i] = projection[i];
        glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void MeshEditor::keyboard(unsigned char _chr, int _x, int _y) {
    if (false) std::cerr << _x << _y << std::endl;
    keysPressed_[_chr] = true;
    keysPressed_[_chr+32] = false;
    keysPressed_[_chr-32] = false;

    //========================= UPDATE STATE ===================================
    keyboardUpdateState();
    glutPostRedisplay();
}

void MeshEditor::keyboardUp(unsigned char _chr, int _x, int _y) {
    if (false) std::cerr << _x << _y << std::endl;
    keysPressed_[_chr] = false;
    keysPressed_[_chr+32] = false;
    keysPressed_[_chr-32] = false;

    //========================= UPDATE STATE ===================================
    keyboardUpdateState();
    glutPostRedisplay();
}

void MeshEditor::keyboardUpdateState() {
    GLint i;
    for (i = 0; i < NUMBER_KEYS; i++) {
        if (keysPressed_[i]) {
            switch (i)
            {
                case 'z':
                    zPhi_ += 1.5f;
                    if (zPhi_ > 360.0f)
                        zPhi_ -= 360.0f;
                    break;
                case 'Z':
                    zPhi_ += -1.5f;
                    if (zPhi_ < -360.0f)
                        zPhi_ += 360.0f;
                    break;
                case 'y':
                    yTheta_ += 1.5f;
                    if (yTheta_ > 360.0f)
                        yTheta_ -= 360.0f;
                    break;
                case 'Y':
                    yTheta_ += -1.5f;
                    if (yTheta_ < -360.0f)
                        yTheta_ += 360.0f;
                    break;
                case 'x':
                    xPsi_ += 1.5f;
                    if (xPsi_ > 360.0f)
                        xPsi_ -= 360.0f;
                    break;
                case 'X':
                    xPsi_ += -1.5f;
                    if (xPsi_ < -360.0f)
                        xPsi_ += 360.0f;
                    break;
                case 'l':
                    toggleLights_ = !toggleLights_;
                    glutPostRedisplay();
                    break;
                case 't':
                    toggleTextures_ = !toggleTextures_;
                    glutPostRedisplay();
                    break;
                case 'T':
                    grid_->changeTextures();
                    glutPostRedisplay();
                    break;

                default:
                    break;
            }
        }
    }
}

void MeshEditor::pick(int _x, int _y, std::string _viewport) {

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLuint select_buff[BUFFER_SIZE];
    glSelectBuffer(BUFFER_SIZE,select_buff);

    renderMode_ = GL_SELECT;
    glRenderMode(renderMode_);

    glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluPickMatrix((GLdouble)_x,(GLdouble)(h_-_y),8,8,viewport);

        if ( (viewport[2]) <= (viewport[3]) )
            glOrtho(-5.0,5.0,
                    -5.0*((GLfloat)(viewport[3]) / (GLfloat)(viewport[2])),
                    5.0*((GLfloat)(viewport[3]) / (GLfloat)(viewport[2])),
                    5.0,-200.0);
        else
            glOrtho(-5.0*((GLfloat)(viewport[2]) / (GLfloat)(viewport[3])),
                     5.0*((GLfloat)(viewport[2]) / (GLfloat)(viewport[3])),
                    -5.0,5.0,5.0,-200.0);

    glMatrixMode(GL_MODELVIEW);
        if (_viewport == "top") {
            glLoadIdentity();
            gluLookAt(topX_,topY_,1,topX_,topY_,0,0,1,0);
        }
        else if (_viewport == "side") {
            glLoadIdentity();
            gluLookAt(-1,sideY_,sideZ_,0,sideY_,sideZ_,0,1,0);
        }
        else if (_viewport == "front") {
            glLoadIdentity();
            gluLookAt(frontX_,-1,frontZ_,frontX_,0,frontZ_,0,0,1);
        }
    glInitNames();
    glPushName(0);
    grid_->displayControlPoints(renderMode_);
    lights_->display(renderMode_);
        glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
        glPopMatrix();

    glFlush();

    renderMode_ = GL_RENDER;
    GLint hits = glRenderMode(renderMode_);
    processPicks(hits,select_buff);

    GLint i,j;
    i_ = -1;
    j_ = -1;
    k_ = -1;
    for(i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if ( (GLfloat)(i*4 + j + 1) == pickIdx_) {
                dragging_ = true;
                i_ = i;
                j_ = j;
                break;
            }
        }

        j--;
        if (i*4 + j + 1 == pickIdx_)
            break;
    }
    for (i = 1; i <= lightIdxCount_; i++) {
        if (pickIdx_ == ctrlPntIdxCount_ + i) {
            k_ = i - 1;
            dragging_ = true;
            break;
        }
    }

    glMatrixMode(GL_MODELVIEW);
}

void MeshEditor::mouse(int _button, int _state, int _x, int _y) {

    if (picking_ == true && _button == GLUT_LEFT_BUTTON && _state==GLUT_DOWN) {
        //========================= Quadrant 1 Click ===========================
        if (_x > w_/2 && _y < h_/2) {
            //Do Nothing.
        }
        //========================= Quadrant 2 Click ===========================
        else if (_x < w_/2 && _y < h_/2) {
            glViewport(0,h_/2 + 1,w_/2,h_/2);
            curViewport_ = "side";
            pick(_x,_y,"side");
        }
        //========================= Quadrant 3 Click ===========================
        else if (_x < w_/2 && _y > h_/2) {
            glViewport(0,0,w_/2,h_/2);
            curViewport_ = "top";
            pick(_x,_y,"top");
        }
        //========================= Quadrant 4 Click ===========================
        else if (_x > w_/2 && _y > h_/2) {
            glViewport(w_/2 + 1,0,w_/2,h_/2);
            curViewport_ = "front";
            pick(_x,_y,"front");
        }

        glutPostRedisplay();
    }
    else if (picking_ == true && dragging_==true &&
             _button==GLUT_LEFT_BUTTON && _state==GLUT_UP) {
        dragging_ = false;
        curViewport_ = "";
        glutPostRedisplay();
    }
    else if (moving_==true &&
             _button == GLUT_LEFT_BUTTON && _state == GLUT_DOWN) {
        dragging_ = true;
        xi_ = _x;
        yi_ = _y;
        panX_ = 0;
        panY_ = 0;
        //========================= Quadrant 1 Click ===========================
        if (_x > w_/2 && _y < h_/2) {
            //Do Nothing.
        }
        //========================= Quadrant 2 Click ===========================
        else if (_x < w_/2 && _y < h_/2) {
            glViewport(0,h_/2 + 1,w_/2,h_/2);
            curViewport_ = "side";
            xo_ = sideZ_;
            yo_ = sideY_;
        }
        //========================= Quadrant 3 Click ===========================
        else if (_x < w_/2 && _y > h_/2) {
            glViewport(0,0,w_/2,h_/2);
            curViewport_ = "top";
            xo_ = topX_;
            yo_ = topY_;
        }
        //========================= Quadrant 4 Click ===========================
        else if (_x > w_/2 && _y > h_/2) {
            glViewport(w_/2 + 1,0,w_/2,h_/2);
            curViewport_ = "front";
            xo_ = frontX_;
            yo_ = frontZ_;
        }

        glutPostRedisplay();
    }
    else if (moving_==true && dragging_ == true &&
             _button == GLUT_LEFT_BUTTON && _state == GLUT_UP) {
        dragging_ = false;
        xi_ = 0;
        yi_ = 0;
        xf_ = 0;
        yf_ = 0;
        curViewport_ = "";

        glutPostRedisplay();
    }
}

void MeshEditor::mouseMotion(int _x, int _y) {
    if (picking_ == true && dragging_ == true) {
        //========================= Quadrant 1 Motion ==========================
        if (_x > w_/2 && _y < h_/2) {
            //Do Nothing
        }
        //========================= Quadrant 2 Motion ==========================
        else if (curViewport_=="side" &&
                 _x < w_/2 && _y < h_/2 && _x > 0 && _y > 0){

            glViewport(0,h_/2 + 1,w_/2,h_/2);

            glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(projOrtho_);
            GLdouble projection[16];
            glGetDoublev(GL_PROJECTION_MATRIX,projection);
                glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(-1,sideY_,sideZ_,0,sideY_,sideZ_,0,1,0);
            GLdouble modelView[16];
            glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
                glLoadIdentity();

            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            GLdouble mouseX,mouseY,mouseZ;

            GLint success = gluUnProject(_x,_y,0,
                                   modelView,projection,viewport,
                                   &mouseX,&mouseY,&mouseZ);

            if (success == 1) {
                mouseY += 10;
                mouseY *= -1;
                mouseY += 2*sideY_;
            }

            if (k_ == -1) {
                grid_->controlPoints_[i_][j_][1] = (GLfloat)mouseY;
                grid_->controlPoints_[i_][j_][2] = (GLfloat)mouseZ;
            }
            else {
                lights_->position_[k_][1] = (GLfloat)mouseY;
                lights_->position_[k_][2] = (GLfloat)mouseZ;
                glLightfv(GL_LIGHT0, GL_POSITION, lights_->position_[0]);
                glLightfv(GL_LIGHT1, GL_POSITION, lights_->position_[1]);
            }

            glutPostRedisplay();
        }
        //========================= Quadrant 3 Motion ==========================
        else if (curViewport_=="top" &&
                 _x < w_/2 && _y > h_/2 && _x > 0 && _y < h_){

            glViewport(0,0,w_/2,h_/2);

            glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(projOrtho_);
            GLdouble projection[16];
            glGetDoublev(GL_PROJECTION_MATRIX,projection);
                glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(topX_,topY_,1,topX_,topY_,0,0,1,0);
            GLdouble modelView[16];
            glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
                glLoadIdentity();

            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            GLdouble mouseX,mouseY,mouseZ;

            GLint success = gluUnProject(_x,_y,0,
                                   modelView,projection,viewport,
                                   &mouseX,&mouseY,&mouseZ);

            if (success == 1) {
                mouseY = 10 - mouseY;
                mouseY += 2*topY_;
            }

            if (k_ == -1) {
                grid_->controlPoints_[i_][j_][0] = (GLfloat)mouseX;
                grid_->controlPoints_[i_][j_][1] = (GLfloat)mouseY;
            }
            else {
                lights_->position_[k_][0] = (GLfloat)mouseX;
                lights_->position_[k_][1] = (GLfloat)mouseY;
                glLightfv(GL_LIGHT0, GL_POSITION, lights_->position_[0]);
                glLightfv(GL_LIGHT1, GL_POSITION, lights_->position_[1]);
            }

            glutPostRedisplay();
        }
        //========================= Quadrant 4 Motion ==========================
        else if (curViewport_=="front" &&
                 _x > w_/2 && _y > h_/2 && _x < w_ && _y < h_){

            glViewport(w_/2 + 1,0,w_/2,h_/2);

            glMatrixMode(GL_PROJECTION);
                glLoadMatrixf(projOrtho_);
            GLdouble projection[16];
            glGetDoublev(GL_PROJECTION_MATRIX,projection);
                glLoadIdentity();

            glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                gluLookAt(frontX_,-1,frontZ_,frontX_,0,frontZ_,0,0,1);
            GLdouble modelView[16];
            glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
                glLoadIdentity();

            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            GLdouble mouseX,mouseY,mouseZ;

            GLint success = gluUnProject(_x,_y,0,
                                   modelView,projection,viewport,
                                   &mouseX,&mouseY,&mouseZ);

            if (success == 1) {
                mouseZ -= 10;
                mouseZ *= -1;
                mouseZ += 2*frontZ_;
            }

            if (k_ == -1) {
                grid_->controlPoints_[i_][j_][0] = (GLfloat)mouseX;
                grid_->controlPoints_[i_][j_][2] = (GLfloat)mouseZ;
            }
            else {
                lights_->position_[k_][0] = (GLfloat)mouseX;
                lights_->position_[k_][2] = (GLfloat)mouseZ;
                glLightfv(GL_LIGHT0, GL_POSITION, lights_->position_[0]);
                glLightfv(GL_LIGHT1, GL_POSITION, lights_->position_[1]);
            }

            glutPostRedisplay();
        }
    }
    else if (moving_ == true && dragging_ == true) {
        xf_ = _x;
        yf_ = _y;
        panX_ = xf_ - xi_;
        panY_ = yf_ - yi_;

        glutPostRedisplay();
    }
}

void MeshEditor::processPicks(GLint _hits, GLuint* _slct_bff) {

    GLuint* select_buff = _slct_bff;
    /*====== First GLuint in select_buff is number of names in this hit ======*/
    GLuint names = *select_buff;
    /*======================== Skip min and max depth ========================*/
    select_buff += 3;

    pickIdx_ = 0;

    GLint i,j,k;
    for (i = 0; i < _hits; i++)
    {
        for (j = 0; j < (GLint)names; j++)
        {
            for (k = 1; k <= ctrlPntIdxCount_ + lightIdxCount_; k++) {
                if (*select_buff == (GLuint)k) {
                    pickIdx_ = k;
                    break;
                }
            }
            if (pickIdx_ != 0)
                break;
            select_buff++;
        }
    }
}

void MeshEditor::actionMenu (int _index) {
    switch (_index) {
        case 0:
            picking_ = !picking_;
            moving_ = !moving_;
            if (picking_ == false) {
                i_ = 0;
                j_ = 0;
            }

            glutPostRedisplay();
            break;
        case 1:
            exit(1);
            break;
        default:
            break;
    }
}

void MeshEditor::run() {
    glutMainLoop();
}

void MeshEditor::regGlutCallbacks() {
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutKeyboardUpFunc(keyboardUpWrapper);
    glutMouseFunc(mouseWrapper);
    glutMotionFunc(mouseMotionWrapper);
}

MeshEditor::MeshEditor(int _argc, char* _argv[]) {
    if (callback_ == NULL)
        callback_ = this;

    glutInit(&_argc,_argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutCreateWindow("Mesh Editor");
    
    glutCreateMenu(actionMenuWrapper);
        glutAddMenuEntry("Toggle Pick/Pan",0);
        glutAddMenuEntry("Quit",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    regGlutCallbacks();

    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_DEPTH_TEST);
        glDepthRange(0,1);
    glEnable(GL_AUTO_NORMAL);
        glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

    grid_ = new Grid();
    lights_ = new PointLight();
    userInterf_ = new UserInterface();

    toggleLights_ = true;
    toggleTextures_ = true;

    curViewport_ = "";
    picking_ = true;
    dragging_ = false;
    i_ = -1;
    j_ = -1;
    k_ = -1;
    pickIdx_ = 0;
    ctrlPntIdxCount_ = 16;
    lightIdxCount_ = 2;
    renderMode_ = GL_RENDER;

    moving_ = false;
    xo_ = 0;
    yo_ = 0;
    xi_ = 0;
    yi_ = 0;
    xf_ = 0;
    yf_ = 0;
    panX_ = 0;
    panY_ = 0;
    frontX_ = 0;
    frontZ_ = 0;
    sideZ_ = 0;
    sideY_ = 0;
    topX_ = 0;
    topY_ = 0;

    GLint i;
    for (i = 0; i < NUMBER_KEYS; i++)
        keysPressed_[i] = false;
    
    zPhi_ = 0;
    yTheta_ = 45;
    xPsi_ = 225;

    w_ = WINDOW_WIDTH;
    h_ = WINDOW_HEIGHT;

    for (i = 0; i < 16; i++) {
        projOrtho_[i] = 0;
        projPerspective_[i] = 0;
    }
}

MeshEditor::~MeshEditor() {
    delete grid_;
    delete lights_;
    delete userInterf_;
}

