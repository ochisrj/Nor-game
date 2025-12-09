#pragma once

#include <glad/glad.h>

class Triangle {
public:
    Triangle();
    ~Triangle();
    void draw();
private:
    GLuint VAO, VBO;
};