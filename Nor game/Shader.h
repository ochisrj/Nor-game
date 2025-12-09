#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
    GLuint ID; // Program ID

    // Constructor: from main.cpp
    Shader(const char* vertexSource, const char* fragmentSource);

    void use() { glUseProgram(ID); }

    // Utility Uniform setters 
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, float v1, float v2, float v3, float v4) const;

private:
    //  Error 
    void checkCompileErrors(GLuint shader, std::string type);
};