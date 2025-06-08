#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setVec3( const std::string &name, float val1, float val2, float val3 );
    void setVec3( const std::string &name, const glm::vec3 &inVec3);
};
