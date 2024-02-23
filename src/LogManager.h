#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// System includes.
#include "spdlog/spdlog.h"

// Engine includes.
#include "Manager.h"
#include "Singleton.h"

// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

namespace df
{

    const std::string LOGFILE_DEFAULT = "log/dragonfly.log";

    enum class Level
    {
        Debug,
        Info,
        Warning,
        Error
    };

    class LogManager : public Manager, public Singleton<LogManager>
    {
    private:
        std::shared_ptr<spdlog::logger> logger;

    public:
        // Do nothing destructor.
        ~LogManager(){};

        // Start up LogManager.
        // Return 0 if ok, else -1.
        int startUp();

        // Shut down LogManager (close all logfiles).
        void shutDown();

        // Set the log level.
        void setLevel(Level value);

        std::shared_ptr<spdlog::logger> getLogger() { return logger; }
    };

} // end of namespace df
#endif // __LOG_MANAGER_H__
