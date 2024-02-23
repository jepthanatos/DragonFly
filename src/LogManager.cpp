#include "LogManager.h"

// System includes
#include "spdlog/sinks/basic_file_sink.h"
#include <iostream>

namespace df
{
    int LogManager::startUp()
    {
        try
        {
            logger = spdlog::basic_logger_mt("file_logger", LOGFILE_DEFAULT, true);

            // Set global log level to debug
            logger->set_level(spdlog::level::debug);

            // change log pattern
            logger->set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
            setType("LogManager");
            logger->debug("LogManager::startUp");
            return Manager::startUp();
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cerr << "Log file creation failed." << std::endl;
            std::cerr << ex.what() << std::endl;
            return -1;
        }
    }

    void LogManager::shutDown()
    {
        logger->debug("LogManager::shutDown");
        spdlog::shutdown();
        Manager::shutDown();
    }

    void LogManager::setLevel(Level newLevel)
    {
        switch (newLevel)
        {
        case Level::Debug:
            logger->set_level(spdlog::level::debug);
            break;
        case Level::Info:
            logger->set_level(spdlog::level::info);
            break;
        case Level::Warning:
            logger->set_level(spdlog::level::warn);
            break;
        case Level::Error:
            logger->set_level(spdlog::level::err);
            break;
        default:
            logger->set_level(spdlog::level::debug);
            break;
        }
    }
}
