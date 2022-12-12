#pragma once


#ifndef PBR_PIPELINE_FILE_UTILS_HPP
#define PBR_PIPELINE_FILE_UTILS_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace PBRPipeline::Utils::FileUtils {

    static std::string readFile(std::string filePath) {
        std::ifstream file(filePath);
        std::string fileContents;
        if (!file.is_open()) {
            return fileContents;
        }
        while (file.good()) {
            file >> fileContents;
        }
        file.close();
        return fileContents;
    }

}

#endif //PBR_PIPELINE_FILE_UTILS_HPP
