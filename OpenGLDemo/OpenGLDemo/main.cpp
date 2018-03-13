//
//  main.cpp
//  OpenGLDemo
//
//  Created by exitingchen on 2018/2/28.
//  Copyright © 2018年 jidongchen. All rights reserved.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mach-o/dyld.h>
#include <stdlib.h>
#include <string.h>


//static void InitEntryPoints (void);
//static void DeallocEntryPoints (void);
//
//// Function pointer type definitions
//typedef void (*glBlendColorProcPtr)(GLclampf red,GLclampf green,
//GLclampf blue,GLclampf alpha);
//typedef void (*glBlendEquationProcPtr)(GLenum mode);
//typedef void (*glDrawRangeElementsProcPtr)(GLenum mode, GLuint start,
//GLuint end,GLsizei count,GLenum type,const GLvoid *indices);
//
//glBlendColorProcPtr pfglBlendColor = NULL; // 2
//glBlendEquationProcPtr pfglBlendEquation = NULL;
//glDrawRangeElementsProcPtr pfglDrawRangeElements = NULL;
//
//
//// -------------------------
//static void DeallocEntryPoints (void) // 4
//{
//    pfglBlendColor = NULL;
//    pfglBlendEquation = NULL;
//    pfglDrawRangeElements = NULL;;
//}
//
//void * MyNSGLGetProcAddress (const char *name)
//{
//    NSSymbol symbol;
//    char *symbolName;
//    symbolName = (char *)malloc (strlen (name) + 2); // 1
//    strcpy(symbolName + 1, name); // 2
//    symbolName[0] = '_'; // 3
//    symbol = NULL;
//    if (NSIsSymbolNameDefined (symbolName)) // 4
//        symbol = NSLookupAndBindSymbol (symbolName);
//    free (symbolName); // 5
//    return symbol ? NSAddressOfSymbol (symbol) : NULL; // 6
//}
//
//static void InitEntryPoints (void) // 3
//{
//    pfglBlendColor = (glBlendColorProcPtr) MyNSGLGetProcAddress
//    ("glBlendColor");
//    pfglBlendEquation = (glBlendEquationProcPtr)MyNSGLGetProcAddress
//    ("glBlendEquation");
//    pfglDrawRangeElements = (glDrawRangeElementsProcPtr)MyNSGLGetProcAddress
//    ("glDrawRangeElements");
//}

const char *vertextShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

void renderTrangle(void *vertices)
{
    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //Vertex shader
    unsigned int vertextShader;
    vertextShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertextShader,1,(const char * const *)vertextShaderSource,NULL);
    glCompileShader(vertextShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char * const *)fragShaderSource, NULL);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertextShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    glDeleteShader(vertextShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

}

int main(int argc, const char * argv[]) {

    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Demo", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create CLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout<< "Failed to init glad" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    unsigned int vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //Vertex shader
    unsigned int vertextShader;
    vertextShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertextShader,1,&vertextShaderSource,NULL);
    glCompileShader(vertextShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertextShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    glDeleteShader(vertextShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}
