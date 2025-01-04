#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    // VBO example with EBO
    // float vertices [] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f  // top left
    // };
    // unsigned int indices [] = {
    //     0, 1, 3,
    //     1, 2, 3
    // };

    /* VBO */
    unsigned int VBO;
    glGenBuffers( 1, &VBO );

    /* EBO */
    // unsigned int EBO;
    // glGenBuffers( 1, &EBO );

    /* VAO Section */
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray( VAO ); // bind vertex array object
    /*----------------------------------------*/

    // Bind the object to a buffer type
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    // glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );

    /* Linking Vertex Attributes Section */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    /* Vertex Shader  */
    // Create vertex shader source and object
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    // Load the source and compile
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );
    // Error Logging
    int success;
    char infoLog[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if (!success) {
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* Fragment Shader  */
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "    FragColor = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
        "}\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );
    //Error logging
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if (!success) {
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    /* Shader Program */
    // Create shader program object
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    // attach and link the 2 shader above into shader program
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    // Error Logging
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    if (!success) {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION::FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    while ( !glfwWindowShouldClose(window) ) {
        /* Update  */
        // Input
        processInput( window );

        /* Draw  */
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram ); // Shader Program Section
        glBindVertexArray(VAO);
        // draw triangle with only VBO
        glDrawArrays( GL_TRIANGLES, 0, 6 );
        // glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

        /* Check and call events and swap the buffers */
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

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
