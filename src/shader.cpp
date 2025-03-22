#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexShaderSourceCode{};
    std::string fragmentShaderSourceCode{};

    {
        std::ifstream vertexFileHandle(vertexPath, std::ios::in | std::ios::binary);
        if(vertexFileHandle){
            vertexFileHandle.seekg(0, std::ios::end);
            vertexShaderSourceCode.resize(vertexFileHandle.tellg());
            vertexFileHandle.seekg(0, std::ios::beg);
            vertexFileHandle.read(&vertexShaderSourceCode[0], static_cast<long>(vertexShaderSourceCode.size()));
        }
    }

    {
        std::ifstream fragmentShaderHandle(fragmentPath, std::ios::in | std::ios::binary);
        if(fragmentShaderHandle){
            fragmentShaderHandle.seekg(0, std::ios::end);
            fragmentShaderSourceCode.resize(fragmentShaderHandle.tellg());
            fragmentShaderHandle.seekg(0, std::ios::beg);
            fragmentShaderHandle.read(&fragmentShaderSourceCode[0], static_cast<long>(fragmentShaderSourceCode.size()));
        }
    }

    const char* vertShaderCode = vertexShaderSourceCode.c_str();
    const char* fragShaderCode = fragmentShaderSourceCode.c_str();

    unsigned int vertexShader{glCreateShader(GL_VERTEX_SHADER)}, fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};

    glShaderSource(vertexShader, 1, &vertShaderCode, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    glShaderSource(fragmentShader, 1, &fragShaderCode, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);
    checkCompileErrors(shaderID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(shaderID);
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) {
    glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) {
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) {
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) {
    glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            spdlog::info("ERROR::SHADER_COMPILATION_ERROR of type: {} : {}", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            spdlog::info("ERROR::SHADER_COMPILATION_ERROR of type: {} : {}", type, infoLog);
        }
    }
}
