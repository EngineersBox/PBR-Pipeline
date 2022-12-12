#include "shader.hpp"

#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "../../../utils/file_utils.hpp"

namespace PBRPipeline::Device::GPU::Shaders {

    Shader::Shader(const std::string name, std::initializer_list<ShaderData> shaderData): name(std::move(name)) {
        std::unordered_map<GLuint, GLuint> modules = std::unordered_map<GLuint, GLuint>();
        for (const ShaderData& data : shaderData) {
            if (modules.find(data.type) != modules.end()) {
                throw std::runtime_error("Duplicate shader module data, already bound for type " + std::to_string(data.type));
            }
        }
        this->programId = glCreateProgram();
        if (this->programId == 0) {
            throw std::runtime_error("Unable to create new shader program " + name);
        }
    }

    GLuint Shader::createShader(const ShaderData& data) {
        if (data.file.empty()) {
            throw std::runtime_error("Shader data file path cannot be empty");
        }
        std::string code = Utils::FileUtils::readFile(data.file);
        GLuint shaderId = glCreateShader(data.type);
        if (shaderId == 0) {
            throw std::runtime_error("[SHADER PROGRAM] Error while creating shader of type " + std::to_string(data.type));
        }
        glShaderSource(shaderId, code);
        glCompileShader(shaderId);
        if (glGetShaderi(shaderId, GL_COMPILE_STATUS) == 0) {
            char log[1024];
            glGetShaderInfoLog(shaderId, 1024, log);
            throw std::runtime_error("[SHADER PROGRAM] Error while compiling shader: " + std::string(log));
        }
    }

}