#include "logger.hpp"

namespace PBRPipeline::Logger {
    std::string formatTime(const char *const formatString) {
        std::stringstream ss;
        static std::locale loc = std::locale(
            ss.getloc(),
            new boost::posix_time::time_facet(formatString)
        );
        ss.imbue(loc);
        ss << boost::posix_time::microsec_clock::universal_time();
        return ss.str();
    }
}