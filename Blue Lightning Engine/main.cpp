//
//  main.cpp
//  Blue Lightning Engine
//
//  Created by Eyitayo Adedeji on 12/03/2016.
//  Copyright (c) 2016 Eyitayo Adedeji. All rights reserved.
//

#include <iostream>
#include <vector>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

const float halfScreenWidth = SCREEN_WIDTH / 2.0f;
const float halfScreenHeight = SCREEN_HEIGHT / 2.0f;

void keyCallback(GLFWwindow *window,int key,int scancode,int action,int mods);
void characterCallback(GLFWwindow *window,unsigned int keyCode);
void characterModCallback(GLFWwindow *window,unsigned int keyCode,int modifierKey);
static void cursorPosCallBack(GLFWwindow *window,double xPos,double yPos);
void cursorEnterCallBack(GLFWwindow *window,int entered);
void mouseButtonCallback(GLFWwindow *window,int button,int action,int mods);
void DrawCube(GLfloat centerPosX,GLfloat centerPosY,GLfloat centerPosZ,GLfloat edgeLength); 

double timeSinceStart;
float rotationX;
float rotationY;

void DrawRect(float sizeX,float sizeY){
    
    GLfloat vertices[] = {
        
        0.0f,sizeY,0.0f, // Top Left
        sizeX,sizeY,0.0f, // Top Right
        sizeX,0.0f,0.0f, // Bottom Right
        0.0f,0.0f,0.0f // Bottom Left
        
        
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

void DrawPoly(int sides){
    
    //vector<GLfloat> vertices;
    GLfloat vertices[] = {
        
        0,0,0,
        0,150,0,
        20,100,0,
        40,150,0,
        60,0,0
        
    };
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_POLYGON, 0, 5);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

void DrawTriangle(float size){
    
    static GLfloat vertices[] = {
        
        0.0f,size,0.0f, // Middle Top
        size,0.0f,0.0f, // Bottom Right
        0.0f,0.0f,0.0f // Bottom Left
        
        
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

void DrawPoint(float x,float y,float size,bool isCircular){
    
    GLfloat point[] = {
        
        x,y
        
    };
    
    if(isCircular) {
        
        glEnable(GL_POINT_SMOOTH);
        
    }
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(size);
    glVertexPointer(2, GL_FLOAT, 0, point);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    if(isCircular) {
        
        glDisable(GL_POINT_SMOOTH);
        
    }
    
}

void DrawCube(GLfloat centerPosX,GLfloat centerPosY,GLfloat centerPosZ,GLfloat edgeLength){
    
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] = {
        
        //Front z is always +
        centerPosX - halfSideLength, centerPosY + halfSideLength,centerPosZ + halfSideLength, //Top Left
        centerPosX + halfSideLength, centerPosY + halfSideLength,centerPosZ + halfSideLength, //Top Right
        centerPosX + halfSideLength, centerPosY - halfSideLength,centerPosZ + halfSideLength, //Bottom Right
        centerPosX - halfSideLength, centerPosY - halfSideLength,centerPosZ + halfSideLength, //Bottom Left
        
        //Back z is always -
        centerPosX - halfSideLength, centerPosY + halfSideLength,centerPosZ - halfSideLength, //Top Left
        centerPosX + halfSideLength, centerPosY + halfSideLength,centerPosZ - halfSideLength, //Top Right
        centerPosX + halfSideLength, centerPosY - halfSideLength,centerPosZ - halfSideLength, //Bottom Right
        centerPosX - halfSideLength, centerPosY - halfSideLength,centerPosZ - halfSideLength, //Bottom Left
        
        ///////
        
        //Left x is always -
        centerPosX - halfSideLength, centerPosY + halfSideLength,centerPosZ + halfSideLength, //Top Left
        centerPosX - halfSideLength, centerPosY + halfSideLength,centerPosZ - halfSideLength, //Top Right
        centerPosX - halfSideLength, centerPosY - halfSideLength,centerPosZ - halfSideLength, //Bottom Right
        centerPosX - halfSideLength, centerPosY - halfSideLength,centerPosZ + halfSideLength, //Bottom Left
        
        //Right x is always +
        centerPosX + halfSideLength, centerPosY + halfSideLength,centerPosZ + halfSideLength, //Top Left
        centerPosX + halfSideLength, centerPosY + halfSideLength,centerPosZ - halfSideLength, //Top Right
        centerPosX + halfSideLength, centerPosY - halfSideLength,centerPosZ - halfSideLength, //Bottom Right
        centerPosX + halfSideLength, centerPosY - halfSideLength,centerPosZ + halfSideLength, //Bottom Left
        
        ///////
        
        //Top y is always +
        centerPosX - halfSideLength, centerPosY + halfSideLength,centerPosZ + halfSideLength, //Top Left
        centerPosX - halfSideLength, centerPosY + halfSideLength,centerPosZ - halfSideLength, //Top Right
        centerPosX + halfSideLength, centerPosY + halfSideLength,centerPosZ - halfSideLength, //Bottom Right
        centerPosX + halfSideLength, centerPosY + halfSideLength,centerPosZ + halfSideLength, //Bottom Left
        
        //Bottom y is always -
        centerPosX - halfSideLength, centerPosY - halfSideLength,centerPosZ + halfSideLength, //Top Left
        centerPosX - halfSideLength, centerPosY - halfSideLength,centerPosZ - halfSideLength, //Top Right
        centerPosX + halfSideLength, centerPosY - halfSideLength,centerPosZ - halfSideLength, //Bottom Right
        centerPosX + halfSideLength, centerPosY - halfSideLength,centerPosZ + halfSideLength //Bottom Left
        
        
    };
    
    GLfloat colours[] = {
        
        255,0,0,
        255,0,0,
        255,0,0,
        255,0,0,
        
        0,255,0,
        0,255,0,
        0,255,0,
        0,255,0,
        
        0,0,255,
        0,0,255,
        0,0,255,
        0,0,255,
        
        255,255,0,
        255,255,0,
        255,255,0,
        255,255,0,
        
        255,0,255,
        255,0,255,
        255,0,255,
        255,0,255,
        
        0,255,255,
        0,255,255,
        0,255,255,
        0,255,255
        
    };
    
  
    //Draw a coloured cube
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colours);
    
    glDrawArrays(GL_QUADS, 0, 24);
    
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    //Draw a wireframe cube ontop of it
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    
    glDrawArrays(GL_QUADS, 0, 24);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

//Main function
int main( void ) {
    // insert code here...
    
    cout << "Starting up..." << endl;
    
    cout << "Initializing GLFW..." << endl;
    
    GLFWwindow *window;
    //initialise library
    
    if(!glfwInit()){
        
        cout << "GLFW Initialisation Error!" << endl;
        return -1;
        
    }
    
    cout << "Initializing main window..." << endl;
    
    //Create a window + OpenGL Context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Blue Lightning Engine", NULL, NULL);
    
    //Set Keyboard Mode
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    
    //Set Cursor Mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    //Set all the input callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCharCallback(window, characterCallback);
    glfwSetCharModsCallback(window, characterModCallback);
    glfwSetCursorPosCallback(window, cursorPosCallBack);
    glfwSetCursorEnterCallback(window, cursorEnterCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    
    if(!window){
        
        cout << "Window Initialisation Error!" << endl;
        glfwTerminate();
        return -2;
        
    }
    
    //Make the window's context current
    glfwMakeContextCurrent(window);
    
    //Declare Vertices in Clockwise Manner
    
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Replaces current matrix with identity matrix
    
    //Left;Right;Bottom;Top;Near;Far
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 2000);

    //Defines how objects are transformed(e.g translated and rotated)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    cout << "Initilises time = " << glfwGetTime() << endl;
    
    cout << "Starting game loop..." << endl;
    glfwSetTime(0);
    //Game Loop
    while (!glfwWindowShouldClose(window)) {
        
        timeSinceStart = glfwGetTime();
        //cout << timeSinceStart << endl;
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Rendering OpenGL :)
        
        /*
        
        1.Tell OpenGl we want to draw something e.g a Vertex Array
         
        2.Size of Each Vertex(3D = 3,2D = 2,1D = 1) ;Value type; Vertex Array
         
        3.DrawType ;Where to Start; Number of Vertices
         
        4.Tell OpenGl we are done drawing the thing e.g a Vertex Array
     
        */

        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
        
        DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);
        
        DrawCube(halfScreenWidth, halfScreenHeight, -500, 200);
        
        glPopMatrix();
        
        //Swap front and back buffers
        glfwSwapBuffers(window);
        
        //Pool for and process events
        glfwPollEvents();
        
    }
    
    glfwTerminate();
    cout << "Ended Smoothly ;)" << endl;
    
    return 0;
    
}




//Cursor Position
static void cursorPosCallBack(GLFWwindow *window,double xPos,double yPos){
    
    //cout << "X: " << xPos << " Y: " << yPos << endl;
    
}

//Whether mouse has entered or exited the window
void cursorEnterCallBack(GLFWwindow *window,int entered){
    
    if(entered){
        
        //cout << "Mouse has entered window" << endl;
        
    } else {
        
        //cout << "Mouse has left window" << endl;
        
    }
    
}

void mouseButtonCallback(GLFWwindow *window,int button,int action,int mods){
    
    //cout << button << endl;
    
}


//Character entered
void characterCallback(GLFWwindow *window,unsigned int keyCode){
   
    //cout << (char)keyCode << endl;
    
}

//Character + Special entered
void characterModCallback(GLFWwindow *window,unsigned int keyCode,int modifierKey){
    
    cout << (char)keyCode << " : " << modifierKey << endl;
    
}

//All Key Presses ,Held and Released
void keyCallback(GLFWwindow *window,int key,int scancode,int action,int mods){
    
    const GLfloat rotationSpeed = 10;
    
    switch (key) {
            
        case GLFW_KEY_UP:
            
            rotationX -= rotationSpeed;
            break;
            
        case GLFW_KEY_DOWN:
            
            rotationX += rotationSpeed;
            break;
            
        case GLFW_KEY_LEFT:
            
            rotationY += rotationSpeed;
            break;
            
        case GLFW_KEY_RIGHT:
            
            rotationY -= rotationSpeed;
            break;
            
        default:
            
            break;
            
    }
    
    /*switch (action) {
            
        case GLFW_PRESS:
            
            cout << (char)key << " was pressed!" << endl;
        
            break;
            
        case GLFW_REPEAT:
            
            cout << (char)key << " is being held!" << endl;
            break;
            
        case GLFW_RELEASE :
            
            cout << (char)key << " was released!" << endl;
            break;
            
        default:
            break;
    }*/
    
}

