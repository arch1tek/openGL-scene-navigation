#ifndef SCENE_H
#define SCENE_H
#include "Room.h"
#include <GL/glut.h>
#include <GL/glu.h>

/**
 * @brief this class provides the scene, room object, keyboard controls and mouse controls
 * 
 */
class Scene{
    public:
        /**
         * @brief Construct a new Scene object
         * 
         */
        Scene(){
            room=new Room();
        }

        
        float angleX = 0.0;
        ///< @brief rotation angle for x axis
        
        float angleY = 0.0;
        ///< @brief rotation angle for y axis
        
        float angleXbuff = 0.0;
        ///< @brief rolling angle for y axis
        
        float angleYbuff = 0.0;
        ///< @brief rolling angle for y axis

        float cameraX = 0.0;
        ///< @brief poition of camera on x axis
        
        float cameraY = 0.0;
        ///< @brief poition of camera on y axis

        float cameraZ = -5.0;
        ///< @brief poition of camera on z axis
        


        
        Room* room;
        ///< @brief room object

        /**
         * @brief render scene callback function
         * 
         */
        void renderScene() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glRotatef(angleXbuff, 1.0, 0.0, 0.0);
            glRotatef(angleYbuff, 0.0, 1.0, 0.0);
            
            glTranslatef(cameraX, cameraY, cameraZ);
            
            glRotatef(angleX, 1.0, 0.0, 0.0);
            glRotatef(angleY, 0.0, 1.0, 0.0);
            
            
            room->createRoom();
            
            glutSwapBuffers();
        }

        /**
         * @brief reshape callback function to handle reshapes
         * 
         * @param w window width
         * @param h window height
         */
        void reshape(int w, int h) {
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
        }

        /**
         * @brief specialKeys callback function to handle rotations
         * 
         * @param key key pressed
         * @param x 
         * @param y 
         */
        void specialKeys(int key, int x, int y) {
            switch (key) {
                case GLUT_KEY_UP:
                    angleX -= 5.0; // Roll scene clockwise about the X-axis
                    break;
                case GLUT_KEY_DOWN:
                    angleX += 5.0; // Roll scene counter-clockwise about the X-axis
                    break;
                case GLUT_KEY_LEFT:
                    angleY -= 5.0; // Roll scene counter-clockwise about the Y-axis
                    break;
                case GLUT_KEY_RIGHT:
                    angleY += 5.0; // Roll scene clockwise about the X-axis
                    break;
            }
            
            glutPostRedisplay();
        }
        
        /**
         * @brief keyboardkeys callback function to handle  panning and zooming
         * 
         * @param key key pressed
         * @param x 
         * @param y 
         */
        void keyboardKeys(unsigned char key, int x, int y) {
            bool addRoll = true;
            switch (key) {
                case 'w':
                    cameraY -= 0.1; // Pan up
                    break;
                case 's':
                    cameraY += 0.1; // Pan down
                    break;
                case 'x':
                    cameraZ += 0.1; // Zoom in
                    break;
                case 'z':
                    cameraZ -= 0.1; // Zoom out
                    break;
                case 'a':
                    cameraX += 0.1; // Pan left
                    break;
                case 'd':
                    cameraX -= 0.1; // Pan right
                    break;
                default:
                    addRoll = false;
                    break;
            }
            if(addRoll){
                angleX += angleXbuff;
                angleY += angleYbuff;
                angleXbuff = 0;
                angleYbuff = 0;
            }else{
                switch(key){
                    case 'i':
                        angleXbuff -= 5.0; // Roll camera clockwise about the X-axis
                        break;
                    case 'k':
                        angleXbuff += 5.0; // Roll camera counter-clockwise about the X-axis
                        break;
                    case 'j':
                        angleYbuff -= 5.0; // Roll camera counter-clockwise about the Y-axis
                        break;
                    case 'l':
                        angleYbuff += 5.0; // Roll camera clockwise about the Y-axis
                        break;
                    default:
                        break;
                }
            }
            
            glutPostRedisplay();
        }
        
        /**
         * @brief mouseclick callback function to handle mouseclicks and change time of the day
         * 
         * @param button button
         * @param state state
         * @param x x position of mouse
         * @param y y position of mouse
         */
        void mouseClick(int button, int state, int x, int y)
        {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                room->changeTime();
                glutPostRedisplay();
            }
        }
};

#endif
