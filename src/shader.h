#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

class Shader {
public:
    Shader() = default;
    Shader(const char* vertexPath, const char* fragmentPath);

    Shader(Shader& shader) { this->shaderID = shader.shaderID; }  //copy
    Shader(Shader&& shader) noexcept { this->shaderID = shader.shaderID; shader.shaderID = 0; }  //move

    Shader& operator=(const Shader& lhs) = default; //assignment copy
    Shader& operator=(Shader&& lhs)  noexcept { shaderID = lhs.shaderID; return *this;}

public:
    void use() const;
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setMat2(const std::string& name, const glm::mat2& mat);
    void setMat3(const std::string& name, const glm::mat3& mat);
    void setMat4(const std::string& name, const glm::mat4& mat);

private:
    void checkCompileErrors(GLuint shader, std::string type);

public:
    unsigned int shaderID{};
};



#endif //SHADER_H
