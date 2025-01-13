#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#include <iostream>
#include "include/shader.h"

void processInput( GLFWwindow* window, Shader* shader );
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

    int width, height, nrChannels;
    unsigned char *data = nullptr;
    // stbi_set_flip_vertically_on_load(true);
    data = stbi_load( "res/container.jpg", &width, &height, &nrChannels, 0 );

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if (data) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load( "res/awesomeface.png", &width, &height, &nrChannels, 0 );

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if (data) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap( GL_TEXTURE_2D );
    } else {
        std::cout << "Failed to load texture 2" << std::endl;
    }

    stbi_image_free(data);
    data = nullptr;

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    /* VBO */
    unsigned int VBO;
    glGenBuffers( 1, &VBO );

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    /* VAO Section */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray( VAO ); // bind vertex array object
    /*----------------------------------------*/

    // Bind the object to a buffer type
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)) );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    float vertices2[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices2[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VBO2, VAO2, EBO2;
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // Bind the object to a buffer type
    glBindBuffer( GL_ARRAY_BUFFER, VBO2 );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)) );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)) );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    Shader ourShader("src/vsShader.vs", "src/fShader.fs");
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    ourShader.setFloat("transInterpolation", 0.2f);

    Shader obj2("src/vsShader.vs", "src/fShader.fs");
    obj2.use();
    obj2.setInt("texture1", 0);
    obj2.setInt("texture2", 1);
    obj2.setFloat("transInterpolation", 0.2f);

    while ( !glfwWindowShouldClose(window) ) {
        /* Update  */
        // Input
        processInput( window, &ourShader );

        /* The order of the scale, translate & rotate matters.
           Changing the order will chnage the behavior of the object */
        float glfwCurrentTime = glfwGetTime();

        /* Draw  */
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        trans = glm::translate(trans, glm::vec3(1.0f, -0.5f, 0.0f));
        trans = glm::rotate(trans, glfwCurrentTime, glm::vec3(0.0f, 0.0f, 0.1f));

        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans = glm::scale(trans, glm::vec3(glm::sin(glm::radians(glfwCurrentTime) * 100),
                                            glm::sin(glm::radians(glfwCurrentTime) * 100),
                                            0.0f));

        obj2.use();
        unsigned int transLocation2 =  glGetUniformLocation(obj2.ID, "transform");
        glUniformMatrix4fv(transLocation2, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Check and call events and swap the buffers */
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(ourShader.ID);

    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO2);
    glDeleteProgram(obj2.ID);

    glfwTerminate();
    return 0;
}

void processInput( GLFWwindow* window, Shader* shader ) {
    static float interpolationValue = 0.2f;
    bool arrowPressed = false;

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
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        interpolationValue += 0.0001f;
        arrowPressed = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        interpolationValue -= 0.0001f;
        arrowPressed = true;
    }
    if (arrowPressed) {
        if (interpolationValue > 1) {
            interpolationValue = 1;
        } else if (interpolationValue < 0) {
            interpolationValue = 0;
        }
        shader->setFloat("transInterpolation", interpolationValue);
    }
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
    glViewport( 0, 0, width, height );
}
