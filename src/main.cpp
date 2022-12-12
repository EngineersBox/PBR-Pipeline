#include <spdlog/spdlog.h>
#include "logging/logger.hpp"

int main() {
    PBRPipeline::Logger::init();
    return 0;
}