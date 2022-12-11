#include <spdlog/spdlog.h>
#include "logger/logger.hpp"

int main() {
    PBRPipeline::Logger::init();
    return 0;
}