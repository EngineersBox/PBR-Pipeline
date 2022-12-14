#pragma once

#ifndef PBR_PIPELINE_SHADER_HPP
#define PBR_PIPELINE_SHADER_HPP

#include <initializer_list>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <unordered_map>

namespace PBRPipeline::Device::GPU::Shaders {

    struct ShaderData {
        GLuint type;
        std::string file;
    };

    struct ShaderValidationState {
        bool valid = false;
        std::optional<std::string> message = std::nullopt;
    };

    class Shader {
    public:
        Shader(const std::string& name, std::initializer_list<ShaderData> shaderData);
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
        [[nodiscard]]
        GLuint createShader(const ShaderData& data) const;
        void link(const std::unordered_map<GLuint, GLuint>& modules) const;
        [[nodiscard]]
        inline std::string getPrefix() const;

        const std::string name;
        GLuint programId = 0;
        bool bound = false;
    };

}

#endif //PBR_PIPELINE_SHADER_HPP
