#include <GLFW/glfw3.h>
// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>

int main(void) {
    /* Initialize the library */
    if (!glfwInit()) return -1;

    std::cout << "Hello World" << std::endl;

    // /* Create a windowed mode window and its OpenGL context */
    auto window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // /* Make the window's context current */
    // glfwMakeContextCurrent(window);

    // /* Loop until the user closes the window */
    // while (!glfwWindowShouldClose(window))
    // {
    //     /* Render here */
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glBegin(GL_TRIANGLES);
    //     glVertex2f(0, 0);
    //     glVertex2f(1, 0.5);
    //     glVertex2f(0.5, 0.5);
    //     glEnd();


    //     /* Swap front and back buffers */
    //     glfwSwapBuffers(window);

    //     /* Poll for and process events */
    //     glfwPollEvents();
    // }


    
}