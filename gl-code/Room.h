#ifndef ROOM_H
#define ROOM_H
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
#include<map>



/**
 * @brief This class contains the functions required to create a room and all its components
 * 
 */
class Room {
private:
    /**
    * @brief sets foreground color to given HSV value
    * 
    * @param h hue, int between 0 and 360
    * @param s saturation, float between 0 and 1
    * @param v value, float between 0 and 1
    */
    void hsvColor3f(float h, float s, float v) {
        int i;
        float f, p, q, t;
        float r=0, g=0, b=0;

        if (s == 0) {
            // Achromatic (gray) color
            r = g = b = v;
            return;
        }

        h /= 60; // Convert hue to sector 0 to 5
        i = static_cast<int>(h);
        f = h - i; // Fractional part of h
        p = v * (1.0 - s);
        q = v * (1.0 - s * f);
        t = v * (1.0 - s * (1.0 - f));

        switch (i) {
            case 0:
                r = v;
                g = t;
                b = p;
                break;
            case 1:
                r = q;
                g = v;
                b = p;
                break;
            case 2:
                r = p;
                g = v;
                b = t;
                break;
            case 3:
                r = p;
                g = q;
                b = v;
                break;
            case 4:
                r = t;
                g = p;
                b = v;
                break;
            default: // case 5:
                r = v;
                g = p;
                b = q;
                break;
        }
        glColor3f(r,g,b);
    }

    /**
     * @brief utility to draw the desk top
     * 
     */
    void drawCube() {
        // Define the 8 vertices of the cube
        GLfloat vertices[8][3] = {
            {-0.5, -0.5, -0.5},
            { 0.5, -0.5, -0.5},
            { 0.5,  0.5, -0.5},
            {-0.5,  0.5, -0.5},
            {-0.5, -0.5,  0.5},
            { 0.5, -0.5,  0.5},
            { 0.5,  0.5,  0.5},
            {-0.5,  0.5,  0.5}
        };

        // Define the 6 faces of the cube by specifying the vertex indices for each face
        int faces[6][4] = {
            {0, 1, 2, 3},  // Front face
            {4, 5, 6, 7},  // Back face
            {0, 3, 7, 4},  // Left face
            {1, 2, 6, 5},  // Right face
            {0, 1, 5, 4},  // Bottom face
            {2, 3, 7, 6}   // Top face
        };

        glBegin(GL_QUADS);
        for (int i = 0; i < 6; i++) {
            if(i==5){
                hsvColor3f(17,1.0f,0.71f);
            }
            for (int j = 0; j < 4; j++) {
                int vertexIndex = faces[i][j];
                glVertex3fv(vertices[vertexIndex]);
            }
        }
        glEnd();
    }


    /**
     * @brief draws aa stack of books
     * 
     */
    void drawBookStack(){
        glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(0,0.1,0);
        glScalef(0.4,0.4,0.4);
        float coverColor[] = {0.8f, 0.2f, 0.2f}; // Red
        float spineColor[] = {0.2f, 0.2f, 0.8f}; // Blue
        float pageColor[] = {0.9f, 0.9f, 0.9f}; // Light Gray
        drawBook(0.5,1,0.2, coverColor,spineColor,pageColor);
        glTranslatef(0,0.2,0);
        drawBook(0.5,1,0.2, coverColor,spineColor,pageColor);
        glPopMatrix();
    }
    /**
     * @brief draws a book with the following parameters
     * 
     * @param width 
     * @param height 
     * @param depth 
     * @param coverColor 
     * @param spineColor 
     * @param pageColor 
     */
    void drawBook(float width, float height, float depth, float coverColor[], float spineColor[], float pageColor[]) {
        // Draw the front cover
        glPushMatrix();
        glRotatef(90,1,0,0);
        glTranslatef(0,1,-0.5*depth);
        glScalef(1,1,1);

        glColor3fv(coverColor);
        glBegin(GL_QUADS);
        glVertex3f(-width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, -height / 2, depth / 2);
        glVertex3f(width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);
        glEnd();

        // Draw the back cover
        glColor3fv(coverColor);
        glBegin(GL_QUADS);
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, -height / 2, -depth / 2);
        glVertex3f(width / 2, height / 2, -depth / 2);
        glVertex3f(-width / 2, height / 2, -depth / 2);
        glEnd();

        // Draw the spine
        glColor3fv(spineColor);
        glBegin(GL_QUADS);
        glVertex3f(-width / 2, -height / 2, -depth / 2);
        glVertex3f(-width / 2, -height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, depth / 2);
        glVertex3f(-width / 2, height / 2, -depth / 2);
        glEnd();
        // Draw the pages
        glColor3fv(pageColor);
        glScalef(width*0.9,height*0.9,depth*0.9);
        glutSolidCube(1);
        glScalef(1.01,1.01,1.01);

        glPopMatrix();
    }
    /**
     * @brief draws a cube without the front face used for room creation
     * 
     */
    void drawCubeWithoutFrontFace() {
        // Draw the back face
        glBegin(GL_QUADS);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glEnd();

        // Draw the left face
        glBegin(GL_QUADS);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glEnd();

        // Draw the right face
        glBegin(GL_QUADS);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glEnd();

        // Draw the top face
        glBegin(GL_QUADS);
        glVertex3f(-0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glEnd();

        // Draw the bottom face
        glBegin(GL_QUADS);
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glEnd();
    }
    /**
     * @brief draws a square
     * 
     */
    void drawSquare() {
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f); // Bottom-left vertex
        glVertex2f(1.0f, -1.0f);  // Bottom-right vertex
        glVertex2f(1.0f, 1.0f);   // Top-right vertex
        glVertex2f(-1.0f, 1.0f);  // Top-left vertex
        glEnd();
    }
    /**
     * @brief draws a filled circle with the followin parameters
     * 
     * @param radius 
     */
    void drawFilledCircle(float radius) {
        float PI = 3.14159265;
        int numSegments = 100;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);  // Center of the circle

        for (int i = 0; i <= numSegments; i++) {
            float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
            float x = radius * cos(theta);
            float y = radius * sin(theta);
            glVertex2f(x, y);
        }

        glEnd();
    }

    /**
     * @brief draws a cylinder with the following radius and height
     * 
     * @param radius 
     * @param height 
     */
    void drawCylinder(float radius, float height) {
        float PI = 3.14159265;
        int numSegments = 20;

        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= numSegments; i++) {
            float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
            float x = radius * cos(theta);
            float z = radius * sin(theta);

            glVertex3f(x, -height / 2.0, z);
            glVertex3f(x, height / 2.0, z);
        }
        glEnd();

        // Draw the top and bottom faces
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, height / 2.0, 0); // Center of the top face
        for (int i = 0; i <= numSegments; i++) {
            float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
            float x = radius * cos(theta);
            float z = radius * sin(theta);
            glVertex3f(x, height / 2.0, z);
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, -height / 2.0, 0); // Center of the bottom face
        for (int i = 0; i <= numSegments; i++) {
            float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
            float x = radius * cos(theta);
            float z = radius * sin(theta);
            glVertex3f(x, -height / 2.0, z);
        }
        glEnd();
    }
public:
    /**
     * @brief represents time of the day
     * 
     * 0 represents morning
     * 1 represents evening
     * 2 represents night
     * 
     */
    int time;
    /**
     * @brief changes time of the day
     * 
     */
    void changeTime(){
        time = (1 + time)%3;
    }
    Room(){
        time = 0;
    }

    /**
     * @brief draws the white board
     * 
     */
    void drawWhiteBoard(){
        glPushMatrix();
        glScalef(2,1,0.05);
        glColor3f(1-((float)time*0.25),1-((float)time*0.25),1-((float)time*0.25));
        glutSolidCube(1);
        glScalef(1.01,1.01,1.01);
        glColor3f(0,0,0);
        glutWireCube(1);
        glPopMatrix();
    }

    /**
     * @brief draws the interior of the room
     * 
     */
    void drawRoomInterior(){

        //walls+ceiling
        glPushMatrix();
        glScalef(10.0f,10.0f,10.0f);
        hsvColor3f(60,0.4f,1 - 0.2f*time);
        glutSolidCube(1.0f);
        glColor3f(0.0f,0.0f,0.0f);
        glScalef(0.99f,0.99f,0.99f);
        glutWireCube(1.0f);
        glPopMatrix();

        //floor
        glPushMatrix();
        glColor3f(0.9-(time*0.20),0.9-(time*0.20),0.9-(time*0.20));
        glBegin(GL_POLYGON);
            glVertex3f(5.0f,-4.999f,5.0f);
            glVertex3f(5.0f,-4.999f,-5.0f);
            glVertex3f(-5.0f,-4.999f,-5.0f);
            glVertex3f(-5.0f,-4.999f,5.0f);
        glEnd();
        glPopMatrix();

        //door
        glPushMatrix();
        glTranslatef(2.75f,0.0f,4.999f);
        hsvColor3f(60,0.8f,0.8f-0.2f*time);
        glBegin(GL_POLYGON);
            glVertex3f(1.75f,-4.999f,0.0f);
            glVertex3f(-1.75f,-4.999f,0.0f);
            glVertex3f(-1.75f,2.0f,0.0f);
            glVertex3f(1.75f,2.0f,0.0f);
        glEnd();
        
        hsvColor3f(60,0.9f,1.0f - time*0.2f);
        glBegin(GL_POLYGON);
            glVertex3f(1.7f,-4.999f,-0.001f);
            glVertex3f(-1.7f,-4.999f,-0.001f);
            glVertex3f(-1.7f,1.95f,-0.001f);
            glVertex3f(1.7f,1.95f,-0.001f);
        glEnd();
        glPopMatrix();

        //window
        glPushMatrix();
        glTranslatef(2.6f,0.5f,-4.999f);
        glColor3f(0.4f,0.4f,0.4f);
        glBegin(GL_POLYGON);
            glVertex3f(2.1f,-1.0f,0.0f);
            glVertex3f(2.1f,2.0f,0.0f);
            glVertex3f(-2.1f,2.0f,0.0f);
            glVertex3f(-2.1f,-1.0f,0.0f);
        glEnd();
        switch(time){
            case 0:
                glColor3f(0.0f,1.0f,1.0f);
                break;
            case 1:
                glColor3f(245/255.0f, 200/255.0f, 149/255.0f);
                break;
            case 2:
                glColor3f(0.0f,0.0f,0.4f);
                break;
            default:
                break;
        }
        glTranslatef(-1.0f,0.0f,0.001f);
        glBegin(GL_POLYGON);
            glVertex3f(-0.85f,-0.9f,0.0f);
            glVertex3f(-0.85f,1.9f,0.0f);
            glVertex3f(0.85f,1.9f,0.0f);
            glVertex3f(0.85f,-0.9f,0.0f);
        glEnd();
        glTranslatef(2.0f,0.0f,0.0f);
        glBegin(GL_POLYGON);
            glVertex3f(-0.85f,-0.9f,0.0f);
            glVertex3f(-0.85f,1.9f,0.0f);
            glVertex3f(0.85f,1.9f,0.0f);
            glVertex3f(0.85f,-0.9f,0.0f);
        glEnd();
        glPopMatrix();

        //closet
        glPushMatrix();
        glTranslatef(-2.7f,0.0f,-4.999f);
        hsvColor3f(60,0.9f,1.0f - 0.2f*time);
        glBegin(GL_POLYGON);
            glVertex3f(1.8f,-4.0f,0.0f);
            glVertex3f(-1.8f,-4.0f,0.0f);
            glVertex3f(-1.8f,2.5f,0.0f);
            glVertex3f(1.8f,2.5f,0.0f);
        glEnd();
        glColor3f(0.0f,0.0f,0.0f);
        glTranslatef(-0.9f,0.0f,0.001f);
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.9f,-4.0f,0.0f);
            glVertex3f(-0.9f,-4.0f,0.0f);
            glVertex3f(-0.9f,2.5f,0.0f);
            glVertex3f(0.9f,2.5f,0.0f);
        glEnd();
        glTranslatef(1.8f,0.0f,0.001f);
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.9f,-4.0f,0.0f);
            glVertex3f(-0.9f,-4.0f,0.0f);
            glVertex3f(-0.9f,2.5f,0.0f);
            glVertex3f(0.9f,2.5f,0.0f);
        glEnd();
        glPopMatrix();
    }

    /**
     * @brief draws the table lamp
     * 
     */
    void drawTableLamp(){
        
        glColor3f(1,0.6,0);
        
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        glutSolidCube(2.0);
        glPopMatrix();

        // Lamp stem
        glPushMatrix();
        glTranslatef(0.0f, 3.0f, 0.0f);
        glScalef(0.5f, 5.0f, 0.5f);
        glutSolidCube(1.0);
        glPopMatrix();

        // Lampshade
        glPushMatrix();
        glTranslatef(0.0f, 6.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(45.0,0,1,0);
        glTranslatef(0.0f, 0.0f, -1.5f);
        glutSolidCone(1.0, 1.5, 20, 20);
        glTranslatef(0,0,-0.01);
        time<2? glColor3f(0.6f,0.6f,0.6f) : glColor3f(1.0f,1.0f,0.8f);
        drawFilledCircle(1);
        glPopMatrix();
    };
    
    /**
     * @brief draws the desk
     * 
     */
    void drawDesk(){

        hsvColor3f(17,1.0f,0.71f- 0.1f*time);

        //Desktop
        glPushMatrix();
        glTranslatef(0.0f,3.0f,0.0f);
        glScalef(2.0f,0.2f,1.0f);
        drawCube();
        glPopMatrix();

        hsvColor3f(17,1.0f,0.71f - 0.15f*time);

        //Desk left frame
        glPushMatrix();
        glTranslatef(-0.65f,2.5f,0.0f);
        glScalef(0.6f,1.0f,0.99f);
        glutSolidCube(1.0f);
        glPopMatrix();
        
        //Desk right frame
        glPushMatrix();
        glTranslatef(0.65f,2.5f,0.0f);
        glScalef(0.6f,1.0f,0.99f);
        glutSolidCube(1.0f);
        glPopMatrix();

        hsvColor3f(30,1.0f,0.78f - 0.15f*time);

        //Desk bottom drawer
        glPushMatrix();
        glTranslatef(-0.65f,2.2f,0.0f);
        glScalef(0.5f,0.3f,1.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
        
        //Desk top drawer
        glPushMatrix();
        glTranslatef(-0.65f,2.7f,0.0f);
        glScalef(0.5f,0.3f,1.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
        
        //Desk cupboard
        glPushMatrix();
        glTranslatef(0.65f,2.5f,0.0f);
        glScalef(0.5f,0.75f,1.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    /**
     * @brief draws the bed
     * 
     */
    void drawBed(){
        float height=0.65;
        float width=2.0;
        float length=1.0;
        float mattressHeight=0.1;
        float standWidth=width/30.0;
        float standHeight=height-mattressHeight;

        //mattress
        glPushMatrix();
        glTranslatef(0.0f,height,0.0f);
        glScalef(width,mattressHeight,length);
        hsvColor3f(0,0.7f,1.0f - 0.2f*time);
        glutSolidCube(1);
        glPopMatrix();

        //frame
        glPushMatrix();
        glTranslatef(0.0f,height-mattressHeight,0.0f);
        glScalef(width,mattressHeight/2,length);
        glColor3f(0.5,0.2,0.2);
        glutSolidCube(1);
        glPopMatrix();

        //stands
        glPushMatrix();
        glTranslatef(width/2.0,standHeight/2.0,length/2.0);
        glTranslatef(-standWidth/2.0, 0.0f ,-standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glColor3f(0.5,0.2,0.2);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-width/2.0,standHeight/2.0,length/2.0);
        glTranslatef(standWidth/2.0, 0.0f ,-standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glColor3f(0.5,0.2,0.2);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(width/2.0,standHeight/2.0,-length/2.0);
        glTranslatef(-standWidth/2.0, 0.0f ,standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glColor3f(0.5,0.2,0.2);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-width/2.0,standHeight/2.0,-length/2.0);
        glTranslatef(standWidth/2.0, 0.0f ,standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glColor3f(0.5,0.2,0.2);
        glutSolidCube(1);
        glPopMatrix();
    }
    
    /**
     * @brief function to draw chair
     * 
     */
    void drawChair(){
        float height=0.55;
        float width=0.5;
        float length=0.5;
        float mattressHeight=0.08;
        float standWidth=width/15.0;
        float standHeight=height-mattressHeight;

        hsvColor3f(37,0.67f,0.82f - 0.2f*time);

        //rest
        glPushMatrix();
        glRotatef(90,0,0,1);
        glTranslatef(height*1.3,width/2,0);
        glScalef(width,mattressHeight/2,length);
        glutSolidCube(1);
        glPopMatrix();

        //frame
        glPushMatrix();
        glTranslatef(0.0f,height-mattressHeight,0.0f);
        glScalef(width,mattressHeight/2,length);
        glutSolidCube(1);
        glPopMatrix();

        //stands
        glColor3f(0.6-time*0.15,0.6-time*0.15,0.6-time*0.15);

        glPushMatrix();
        glTranslatef(width/2.0,standHeight/2.0,length/2.0);
        glTranslatef(-standWidth/2.0, 0.0f ,-standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-width/2.0,standHeight/2.0,length/2.0);
        glTranslatef(standWidth/2.0, 0.0f ,-standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(width/2.0,standHeight/2.0,-length/2.0);
        glTranslatef(-standWidth/2.0, 0.0f ,standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-width/2.0,standHeight/2.0,-length/2.0);
        glTranslatef(standWidth/2.0, 0.0f ,standWidth/2.0);
        glScalef(standWidth,standHeight,standWidth);
        glutSolidCube(1);
        glPopMatrix();
    }
    
    /**
     * @brief draws the contents on the table top such as stack of books, lamp and laptop
     * 
     */
    void tableTopContents(){
        glPushMatrix();
        glTranslatef(0.0f,3.0f,0.0f);

        glPushMatrix();
        glTranslatef(-0.1,0,0.15);
        glRotatef(90,0,1,0);
        glTranslatef(0,0.1,0);
        glScalef(0.4,0.4,0.4);
        drawLaptop();
        glPopMatrix();

        glPushMatrix();
        glRotatef(-90,0,1,0);
        glTranslatef(0.2,0.1,0.5);
        glScalef(0.1,0.1,0.1);
        drawTableLamp();
        glPopMatrix();

        drawBookStack();

        glPopMatrix();
    }

    /**
     * @brief draws a laptop
     * 
     */
    void drawLaptop(){
        //base
        glPushMatrix();
        glScalef(1,0.05,1);
        glTranslatef(0.5,0,0);
        glColor3f(0.8,0.8,0.8);
        glutSolidCube(1);
        glPopMatrix();

        //keyboard
        glPushMatrix();
        glScalef(1,0.05,1);
        glTranslatef(0.5,+0.2,0);
        glScalef(0.9,1,0.9);
        glColor3f(0.2,0.2,0.2);
        glutSolidCube(1);
        glPopMatrix();
        
        //screenbase
        glPushMatrix();
        glRotatef(110,0,0,1);
        glScalef(1,0.05,1);
        glTranslatef(0.5,0,0);
        glColor3f(0.8,0.8,0.8);
        glutSolidCube(1);
        glPopMatrix();

        //screen
        glPushMatrix();
        glRotatef(110,0,0,1);
        glScalef(1,0.05,1);
        glTranslatef(0.5,-0.2,0);
        glScalef(0.9,1,0.9);
        glColor3f(1,1,1);
        glutSolidCube(1);
        glPopMatrix();
    }

    /**
     * @brief draws a fan
     * 
     */
    void drawFan(){
        float innerRadius=0.4;
        float outerRadius=1.0;
        float height=1.0;

        glColor3f(1-time*0.25,1-time*0.25,1-time*0.25);

        // fan center
        glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(innerRadius,height/10.0,innerRadius);
        drawCylinder(1,1);
        glPopMatrix();

        //fan stem
        glPushMatrix();
        glTranslatef(0,height/2,0);
        glScalef(innerRadius/10,height,innerRadius/10);
        drawCylinder(1,1);
        glPopMatrix();


        //fan blades
        glColor3f(0.9-time*0.25,0.9-time*0.25,0.9-time*0.25);

        glPushMatrix();
        glRotatef(90.0,1,0,0);
        glScalef(outerRadius,outerRadius/5.0,outerRadius/5.0);
        glTranslatef(1,0,0);
        drawSquare();
        glPopMatrix();

        glPushMatrix();
        glRotatef(120.0,0,1,0);
        glRotatef(90.0,1,0,0);
        glScalef(outerRadius,outerRadius/5.0,outerRadius/5.0);
        glTranslatef(1,0,0);
        drawSquare();
        glPopMatrix();

        glPushMatrix();
        glRotatef(240.0,0,1,0);
        glRotatef(90.0,1,0,0);
        glScalef(outerRadius,outerRadius/5.0,outerRadius/5.0);
        glTranslatef(1,0,0);
        drawSquare();
        glPopMatrix();
    }
    
    /**
     * @brief Create a Room object
     */
    void createRoom(){
        drawRoomInterior();
        // glPushMatrix();
        // glScalef(10,10,10);
        // glColor3f(1,1,1);
        // glutSolidCube(1);
        // glScalef(0.99,0.99,0.99);
        // glColor3f(0,0,0);
        // glutWireCube(1);
        // glPopMatrix();

        glPushMatrix();
        glTranslatef(3.6f,-11.0f,-1.3f);
        glRotatef(90.0f,0.0f,1.0f,0.0f);
        glScalef(2.0f,3.0f,3.0f);
        drawDesk();
        glScalef(1.5,1,1);
        tableTopContents();
        glPopMatrix();


        //bed
        glPushMatrix();
        glTranslatef(0.0f,-5.0f,0);
        glScalef(3.3,3.3,3.3);
        glRotatef(90.0f,0.0f,1.0f,0.0f);
        glTranslatef(0,0,-1);
        drawBed();
        glPopMatrix();

        //chair
        glPushMatrix();
        glTranslatef(1,-5.0f,-1);
        glScalef(3.3,3.3,3.3);
        drawChair();
        glPopMatrix();

        //fan
        glPushMatrix();
        glTranslatef(0.0f,4,0);
        glScalef(1,1,1);
        drawFan();
        glPopMatrix();

        //board
        glPushMatrix();
        glTranslatef(4.9,0.8f,-1.3);
        glRotatef(90.0f,0.0f,1.0f,0.0f);
        glScalef(2.0f,3.0f,3.0f);
        drawWhiteBoard();
        glPopMatrix();
    }
};

#endif
