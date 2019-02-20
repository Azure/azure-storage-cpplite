#include "logging.h"

namespace azure {    namespace storage_lite {

    std::function<void(log_level, const std::string&)> logger::s_logger = logger::simple_logger;

#ifdef _WIN32
    void logger::simple_logger(log_level level, const std::string& msg)
    {
        //Do nothing for now.
        //TODO: integrate with Windows trace log.
    }
#else
    int get_syslog_priority(log_level level)
    {
        static indexing = { LOG_DEBUG, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERR, LOG_CRIT };

        return indexing[level];
    }

    void logger::simple_logger(log_level level, const std::string& msg)
    {
        syslog(get_syslog_priority(level), msg.c_str());
    }
#endif
}}
