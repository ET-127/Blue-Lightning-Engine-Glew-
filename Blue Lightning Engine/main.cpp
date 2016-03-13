//
//  main.cpp
//  Blue Lightning Engine
//
//  Created by Eyitayo Adedeji on 12/03/2016.
//  Copyright (c) 2016 Eyitayo Adedeji. All rights reserved.
//

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void DrawRect(float sizeX,float sizeY){
    
    GLfloat vertices[] = {
        
        0.0f,sizeY,0.0f, // Top Left
        sizeX,sizeY,0.0f, // Top Right
        sizeX,0.0f,0.0f, // Bottom Right
        0.0f,0.0f,0.0f // Bottom Left
        
        
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);
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

void DrawPoint(float x,float y,float size){
    
    GLfloat point[] = {
        
        x,y
        
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(50);
    glVertexPointer(2, GL_FLOAT, 0, point);
    glDrawArrays(GL_POINT, 0, 1);
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
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    //Defines how objects are transformed(e.g translated and rotated)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    cout << "Starting game loop..." << endl;
    //Game Loop
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Rendering OpenGL :)
        
        /*
        
        1.Tell OpenGl we want to draw a vertex Array
         
        2.Size of Each Vertex(3D = 3,2D = 2,1D = 1) ;Value type; Vertex Array
         
        3.DrawType ;Where to Start; Number of Vertices
         
        4.Tell OpenGl we are done drawing the vertex array
     
        */
        
        DrawPoint(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 50);

        //DrawRect(50, 150);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        
        //Swap front and back buffers
        glfwSwapBuffers(window);
        
        //Pool for and process events
        glfwPollEvents();
        
    }
    
    glfwTerminate();
    cout << "Ended Smoothly ;)" << endl;
    
    return 0;
    
}
