#include "include/shader.h"

Shader::Shader( const char* vertexPath, const char* fragmentPath ) {
    std::string vertexSource;
    std::string fragmentSource;

    std::ifstream vShader;
    std::ifstream fShader;

    vShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        vShader.open(vertexPath);
        fShader.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShader.rdbuf();
        fShaderStream << fShader.rdbuf();
        vShader.close();
        fShader.close();
        vertexSource = vShaderStream.str();
        fragmentSource = fShaderStream.str();
    }catch ( std::ifstream::failure e ){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &vShaderCode, NULL );
    glCompileShader( vertex );
    glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
    if ( !success ) {
        glGetShaderInfoLog( vertex, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &fShaderCode, NULL );
    glCompileShader( fragment );
    glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
    if ( !success ) {
        glGetShaderInfoLog( fragment, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::setColorUni4f( const std::string &name, float r, float g, float b ) const{
    // only works with vec4 uniform variable
    int location = glGetUniformLocation(ID, name.c_str());
    if ( location < 0 ) {
        std::cout << "Shader Program couldn't find the uniform variable\n";
    }
    glUniform4f(location, r, g, b, 1.0f);
}

void Shader::use(){ glUseProgram(ID); }

void Shader::setBool( const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt( const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat( const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3( const std::string &name, float val1, float val2, float val3 ) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), val1, val2, val3);
}

void Shader::setVec3( const std::string &name, const glm::vec3 &inVec3) {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &inVec3[0]);
}
