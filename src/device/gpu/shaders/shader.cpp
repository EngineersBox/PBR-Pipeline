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
            modules.insert(std::pair(
                data.type,
                this->createShader(data)
            ));
        }
        this->programId = glCreateProgram();
        if (this->programId == 0) {
            throw std::runtime_error("Unable to create new shader program " + name);
        }
        this->link(modules);
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
        glAttachShader(this->programId, shaderId);
        return shaderId;
    }

    void Shader::link(std::unordered_map<GLuint, GLuint>& modules) {
        glLinkProgram(this->programId);
        if (glGetProgrami(this->programId, GL_LINK_STATUS) == 0) {
            char log[1024];
            glGetProgramInfoLog(this->programId, 1024, log);
            throw std::runtime_error("[SHADER PROGRAM] Error while linking shader" + std::string(log));
        }
        for (const auto& [_ignored, shaderId] : modules) {
            glDetachShader(this->programId, shaderId);
            glDeleteShader(shaderId);
        }
    }

    ShaderValidationState Shader::validate() {
        glValidateProgram(this->programId);
        if (glGetProgrami(this->programId, GL_VALIDATE_STATUS) == 0) {
            char log[1024];
            glGetProgramInfoLog(this->programId, 1024, log);
            return ShaderValidationState {
                .valid =  false,
                .message = std::optional<std::string>(log)
            };
        }
        return ShaderValidationState {
            .valid = true,
            .message = std::nullopt
        };
    }

}