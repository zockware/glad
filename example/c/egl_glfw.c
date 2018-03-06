#include <stdlib.h>
#include <stdio.h>

#include <glad/glad_egl.h>
#include <glad/glad_gles1.h>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_EGL 1
#include <GLFW/glfw3native.h>


const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char ** argv) {
    /* Set up GLFW */
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "[glad] EGL with GLFW", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    /* Load EGL */
    EGLDisplay display = glfwGetEGLDisplay();
    int eglVersion = gladLoadEGLInternalLoader(display);
    printf("EGL %d.%d\n", eglVersion / 10, eglVersion % 10);

    /* Load GLES */
    int glesVersion = gladLoadGLES1InternalLoader();
    printf("GLES %d.%d\n", glesVersion / 10, glesVersion % 10);

    /* Main Loop */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}