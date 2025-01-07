#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
 public:
    unsigned int ID;

    Shader( const char* vertexPath, const char* fragmentPath );
    void use();
    void setColorUni4f( const std::string &name, float r, float g, float b ) const;
    void setBool( const std::string &name, bool value) const;
    void setInt( const std::string &name, int value) const;
    void setFloat( const std::string &name, float value) const;
};
