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

    // Left triangle
    float triangle1Vert[] = {
        -0.5f, -0.5f, 0.0f, // top left
        0.0f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f, // bottom left
    };

    // right triangle
    float triangle2Vert[] = {
        0.0f, -0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f // bottom left
    };

    // Triangle 1 VBO & VAO settings
    unsigned int triangle1VBO;
    glGenBuffers( 1, &triangle1VBO );
    unsigned int triangle1VAO;
    glGenVertexArrays(1, &triangle1VAO);
    glBindVertexArray( triangle1VAO );

    // triangle 1 VBO
    glBindBuffer( GL_ARRAY_BUFFER, triangle1VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(triangle1Vert), triangle1Vert, GL_STATIC_DRAW );

    /* Linking Vertex Attributes Section */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    // Triangle 2 VBO & VAO settings
    unsigned int triangle2VBO;
    glGenBuffers( 1, &triangle2VBO );
    unsigned int triangle2VAO;
    glGenVertexArrays( 1, &triangle2VAO );
    glBindVertexArray( triangle2VAO );

    glBindBuffer( GL_ARRAY_BUFFER, triangle2VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(triangle2Vert), triangle2Vert, GL_STATIC_DRAW );

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
        // drawing triangle 1
        glBindVertexArray(triangle1VAO);
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        // drawing triangle 2
        glBindVertexArray( triangle2VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

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
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
    glViewport( 0, 0, width, height );
}
