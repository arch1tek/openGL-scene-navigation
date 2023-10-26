#include <GL/gl.h>
#include <GL/glut.h>
#include "Room.h"
#include "Scene.h"

Scene* scene;
///< @brief Scene object

void renderScene() {
    scene->renderScene();
}

void reshape(int w, int h) {
    scene->reshape(w, h);
}

void specialKeys(int key, int x, int y) {
    scene->specialKeys(key,x,y);
}

void keyboardKeys(unsigned char key, int x, int y) {
    scene->keyboardKeys(key, x, y);
}

void mouseClick(int button, int state, int x, int y)
{
    scene->mouseClick(button, state, x, y);
}

/**
 * @brief main function that runs on program start
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) {

    scene = new Scene();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Room");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboardKeys);
    glutMouseFunc(mouseClick);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
