#ifndef _3dmodeler_mesheditor_h
#define	_3dmodeler_mesheditor_h

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>

#include "Grid.h"
#include "PointLight.h"
#include "UserInterface.h"

#include "config.h"

namespace _3dmodeler {

class _3DMODELER_DLL_EXPORT MeshEditor {
public:
    MeshEditor(int _argc, char* _argv[]);
    virtual ~MeshEditor();
    void run();

private:
    Grid* grid_;
    PointLight* lights_;
    UserInterface* userInterf_;

    bool toggleLights_;
    bool toggleTextures_;

    std::string curViewport_;
    bool picking_;
    bool dragging_;
    GLint i_;
    GLint j_;
    GLint k_;
    GLint pickIdx_;
    GLint ctrlPntIdxCount_;
    GLint lightIdxCount_;
    GLenum renderMode_;

    bool moving_;
    GLfloat xo_;
    GLfloat yo_;
    GLfloat xi_;
    GLfloat yi_;
    GLfloat xf_;
    GLfloat yf_;
    GLfloat panX_;
    GLfloat panY_;
    GLfloat frontX_;
    GLfloat frontZ_;
    GLfloat sideZ_;
    GLfloat sideY_;
    GLfloat topX_;
    GLfloat topY_;

    static const int NUMBER_KEYS = 256;

    bool keysPressed_[NUMBER_KEYS];
    GLfloat zPhi_;
    GLfloat yTheta_;
    GLfloat xPsi_;

    GLint w_;
    GLint h_;
    GLfloat projOrtho_[16];
    GLfloat projPerspective_[16];

    static MeshEditor* callback_;

    void regGlutCallbacks();
    static void displayWrapper() {
        callback_->display();
    };
    static void reshapeWrapper(int x, int y) {
        callback_->reshape(x, y);
    };
    static void keyboardWrapper(unsigned char c, int x, int y) {
        callback_->keyboard(c, x, y);
    };
    static void keyboardUpWrapper(unsigned char c, int x, int y) {
        callback_->keyboardUp(c, x, y);
    };
    static void mouseWrapper(int b, int s, int x, int y) {
        callback_->mouse(b, s, x, y);
    };
    static void mouseMotionWrapper(int x, int y) {
        callback_->mouseMotion(x, y);
    };
    static void actionMenuWrapper(int _index) {
        callback_->actionMenu(_index);
    };

    void display();
    void reshape(int _w, int _h);

    void keyboard(unsigned char _chr, int _x, int _y);
    void keyboardUp(unsigned char _chr, int _x, int _y);
    void keyboardUpdateState();

    void pick(int _x, int _y, std::string _viewport);
    void mouse(int _button, int _state, int _x, int _y);
    void mouseMotion(int _x, int _y);
    void actionMenu(int _index);

    void processPicks(GLint _hits, GLuint* _slct_bff);
};

} // end _3dmodeler{

#endif	// _3dmodeler_mesheditor_h

