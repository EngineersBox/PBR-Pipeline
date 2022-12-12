#include <spdlog/spdlog.h>
#include "logging/logger.hpp"
#include "device/gpu/shaders/shader.hpp"

int main() {
    PBRPipeline::Logger::init();
    return 0;
}