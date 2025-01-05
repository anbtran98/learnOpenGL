#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "include/shader.h"

void processInput( GLFWwindow* window );
void framebuffer_size_callback( GLFWwindow* window, int width, int height );

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main() {

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL );
    if ( window == NULL ) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent( window );

    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    // VBO example without EBO
    float vertices[] = {
         // Positions
         0.0f, 0.5f, 0.0f,  // top
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f  // bottom right
    };

    /* VBO */
    unsigned int VBO;
    glGenBuffers( 1, &VBO );

    /* VAO Section */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray( VAO ); // bind vertex array object
    /*----------------------------------------*/

    // Bind the object to a buffer type
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    Shader ourShader("src/vsShader.vs", "src/fShader.fs");

    while ( !glfwWindowShouldClose(window) ) {
        /* Update  */
        // Input
        processInput( window );

        /* Draw  */
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        // glUseProgram( shaderProgram );
        ourShader.use();
        // ourShader.setColorUni4f( "myColor", 0.7f, 0.1f, 0.7f ); // for Uniform vec4 variable
        ourShader.setFloat( "r", 1.0f );
        ourShader.setFloat( "g", 0.0f );
        ourShader.setFloat( "b", 1.0f );
        ourShader.setFloat( "a", 1.0f );
        glBindVertexArray(VAO);
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        /* Check and call events and swap the buffers */
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ourShader.ID);

    glfwTerminate();
    return 0;
}

void processInput( GLFWwindow* window ) {
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, true );
    else if ( glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS ) {
        static bool flag = true;
        if (flag) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            flag = false;
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            flag = true;
        }
    }
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
    glViewport( 0, 0, width, height );
}
