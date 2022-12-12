#pragma once

#ifndef PBR_PIPELINE_SHADER_HPP
#define PBR_PIPELINE_SHADER_HPP

#include <initializer_list>
#include <string>
#include <gl/gl.h>
#include <gl/glew.h>

namespace PBRPipeline::Device::GPU::Shaders {

    struct ShaderData {
        std::string file;
        GLuint type;
    };

    class Shader {
    public:
        Shader(std::string name, std::initializer_list<ShaderData> shaderData);
        ~Shader();
    private:
        GLuint createShader(const ShaderData& data);

        const std::string name;
        GLuint programId = 0;
        bool bound = false;
    };

}

#endif //PBR_PIPELINE_SHADER_HPP
