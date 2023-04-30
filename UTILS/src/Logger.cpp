#include "my_utils/Logger.hpp"
Logger logger;
std::mutex mxLog;
void Logger::setTarget(Target target) { this->LoggerTarget = (short)target; }
void Logger::xorTarget(Target target) { this->LoggerTarget ^= (short)target; }

void Logger::setLevel(Level level) { this->LoggerLevel = level; }

Level Logger::getLevel() { return this->LoggerLevel; }

string Logger::levelToString(Level level) { return levelMap[level]; }

short Logger::setFile(string fileName, bool deleteFile, const std::experimental::source_location location)
{
    if (this->LoggingFileStream.is_open()) {
        this->LoggingFileStream.close();
    }
    // Make sure we can open the file for writing
    if (deleteFile) {
        remove(fileName.c_str());
    }
    this->LoggingFileStream.open(fileName, ofstream::app);
    if (!this->LoggingFileStream.is_open()) {
        // Logger the failure and return an error code
        this->write(Level::ERR, "Failed to open Logger file '" + fileName + "'", location);
        return 1;
    }
    this->LoggerFile = fileName;
    return 0;
}

short Logger::setFile(string fileName, ofstream::openmode mode, bool deleteFile,
                      const std::experimental::source_location location)
{
    if (this->LoggingFileStream.is_open()) {
        this->LoggingFileStream.close();
    }
    if (deleteFile) {
        remove(fileName.c_str());
    }
    this->LoggingFileStream.open(fileName, ofstream::app);
    if (!this->LoggingFileStream.is_open()) {
        // Logger the failure and return an error code
        this->write(Level::ERR, "Failed to open Logger file '" + fileName + "'", location);
        return 1;
    }
    this->LoggerFile = fileName;
    return 0;
}

void Logger::write(Level level, string message, const std::experimental::source_location location)
{
    // Only log if we're at or above the pre-defined severity
    if (level < this->LoggerLevel) {
        return;
    }
    // Target::DISABLED takes precedence over other targets
    if (this->LoggerTarget == (short)Target::DISABLED) {
        return;
    }

    string toLogger;

    if (!this->LoggingFileStream.is_open()) {
        setFile(this->LoggerFile);
    }

    // Append the message to our Logger statement
    if (this->fileEnabled || this->timestampEnabled || this->levelEnabled) {
        toLogger = getLoggerfunctionInfo(level, location) + ":\n" + message + "\n";
    } else {
        toLogger = message + "\n";
    }
    // printf makes printing a bit faster
    // Logger to stdout if it's one of our targets
    if ((this->LoggerTarget & (short)Target::STDOUT)) {
        mxLog.lock();
        fprintf(stdout, "%s", toLogger.c_str());
        mxLog.unlock();
    }

    // Logger to stderr if it's one of our targets
    if ((this->LoggerTarget & (short)Target::STDERR)) {
        mxLog.lock();
        fprintf(stderr, "%s", toLogger.c_str());
        mxLog.unlock();
    }

    // Logger to a file if it's one of our targets and we've set a LoggerFile
    if ((this->LoggerTarget & (short)Target::LOG_FILE) && this->LoggerFile != "") {
        mxLog.lock();
        this->LoggingFileStream << toLogger;
        mxLog.unlock();
    }
}

std::string Logger::getLoggerfunctionInfo(Level level, const std::experimental::source_location location)
{
    newTimer("FunctionInfo");
    string toLogger;
    size_t offset = 0;

    // Append the current date and time if enabled
    if (this->timestampEnabled) {
        std::time_t time = system_clock::to_time_t(system_clock::now());
        if (this->lastTime < time) {
            this->lastTime = time;
            struct tm* timeStruct = std::localtime(&time);
            strftime(&this->timeStr[1], 200, "%d/%b/%Y %H:%M:%S", timeStruct);
        }
        offset = cpyChar(timeString, "[");
        offset += cpyChar(timeString + offset, this->timeStr);
        offset += cpyChar(timeString + offset, "] \0");
        toLogger += timeString;
    }

    if (this->levelEnabled) {
        toLogger += levelMap[level] + " ";
    }

    if (this->fileEnabled) {
        size_t fileNameSize = strlen(location.file_name());
        size_t funcNameSize = strlen(location.function_name());
        size_t stringSize = fileNameSize + funcNameSize + 20 + 5;

        if (stringSize > tempStringSize) {
            tempStringSize = stringSize;
            free(fileString);
            fileString = (char*)malloc(sizeof(char) * (stringSize));
        }
        offset = cpyChar(fileString, location.file_name());
        offset += cpyChar(fileString + offset, ":");
        offset += cpyChar(fileString + offset, location.line());
        offset += cpyChar(fileString + offset, ";");
        offset += cpyChar(fileString + offset, location.column());
        offset += cpyChar(fileString + offset, "  ");
        offset += cpyChar(fileString + offset, location.function_name());
        cpyChar(fileString + offset, "\0");
        toLogger += fileString;
    }
    return toLogger;
}
