#pragma once

#ifndef PBR_PIPELINE_SHADER_HPP
#define PBR_PIPELINE_SHADER_HPP

#include <initializer_list>
#include <string>
#include <optional>
#include <gl/GL.h>
#include <gl/glew.h>

namespace PBRPipeline::Device::GPU::Shaders {

    struct ShaderData {
        std::string file;
        GLuint type;
    };

    struct ShaderValidationState {
        bool valid;
        std::optional<std::string> message;
    };

    class Shader {
    public:
        Shader(std::string name, std::initializer_list<ShaderData> shaderData);
        ~Shader();

        void bind();
        void unbind();

        ShaderValidationState validate();

        GLuint getProgramId() {
            return this->programId;
        }

        [[nodiscard]]
        std::string getName() const& {
            return this->name;
        }
        void cleanup() {
            if (this->programId != 0) {
                glDeleteProgram(this->programId);
            }
        }
    private:
        GLuint createShader(const ShaderData& data);
        void link(std::unordered_map<GLuint, GLuint>& modules);

        const std::string name;
        GLuint programId = 0;
        bool bound = false;
    };

}

#endif //PBR_PIPELINE_SHADER_HPP
