// MIT License

// Copyright (c) 2020 Tracy

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef WIND_LOG_H
#define WIND_LOG_H

#include "LogStream.h"

// if you want to define your custom log tag
// plese define it before including Log.h, here a sample:
// -------------------------------------------
//      #define LOG_TAG "MyLogTag"
//      #include "Log.h"
// -------------------------------------------
#ifndef LOG_TAG
#define LOG_TAG "Wind"
#endif // LOG_TAG

namespace wind {
enum class LogLevel {
    TRACE = 1,
    DEBUG,
    INFO,
    WARN,
    ERROR,
};

// Read log level from env: WIND_LOG_LEVEL
// "TRACE" or 1 --> LogLevel::TRACE
// "DEBUG" or 2 --> LogLevel::DEBUG
// "INFO" or 3 --> LogLevel::INFO
// "WARN" or 4 --> LogLevel::WARN
// "ERROR" or 5 --> LogLevel::ERROR
// else --> defaultLogLevel: DEBUG in Debug mode, and INFO in release mode.

// we can change the env at runtime use gdb to test this function:
// https://stackoverflow.com/questions/205064/is-there-a-way-to-change-the-environment-variables-of-another-process-in-unix
LogLevel currentLogLevel();

class LogFileName {
public:
    // not explicit cause we use its implicit constructor.
    LogFileName(const char *s)
    {
        size_t len = ::strlen(s);
        append(s, len);
    }
    // not explicit, too.
    template <size_t len>
    LogFileName(const char (&s)[len])
    {
        append(s, len);
    }
    ~LogFileName() noexcept = default;

    const char *data() const { return buf_; }

    size_t length() const { return ::strlen(buf_); }

private:
    void append(const char *data, size_t len)
    {
        const char *p = ::strrchr(data, '/') + 1;
        if (WIND_UNLIKELY(p == NULL)) {
            return;
        }

        size_t bytesToWrite = len - (p - data);
        ASSERT(sizeof(buf_) > bytesToWrite);
        ::memcpy(buf_, p, bytesToWrite);
    }

    char buf_[256] = {0};
};

class Logger : NonCopyable {
public:
    Logger(LogFileName fileName, int line, LogLevel level, std::string tag, bool isFatal);
    ~Logger() noexcept;
    LogStream &stream() { return stream_; }

private:
    LogStream stream_;
    LogFileName fileName_;
    int line_;
    LogLevel level_;
    std::string tag_;
    bool isFatal_;
};
} // namespace wind

#define LOG_TRACE                                                                                                      \
    if (wind::currentLogLevel() <= wind::LogLevel::TRACE)                                                              \
    wind::Logger(__FILE__, __LINE__, wind::LogLevel::TRACE, LOG_TAG, false).stream()
#define LOG_DEBUG                                                                                                      \
    if (wind::currentLogLevel() <= wind::LogLevel::DEBUG)                                                              \
    wind::Logger(__FILE__, __LINE__, wind::LogLevel::DEBUG, LOG_TAG, false).stream()
#define LOG_INFO                                                                                                       \
    if (wind::currentLogLevel() <= wind::LogLevel::INFO)                                                               \
    wind::Logger(__FILE__, __LINE__, wind::LogLevel::INFO, LOG_TAG, false).stream()
#define LOG_WARN                                                                                                       \
    if (wind::currentLogLevel() <= wind::LogLevel::WARN)                                                               \
    wind::Logger(__FILE__, __LINE__, wind::LogLevel::WARN, LOG_TAG, false).stream()
#define LOG_ERROR wind::Logger(__FILE__, __LINE__, wind::LogLevel::ERROR, LOG_TAG, false).stream()
#define LOG_SYS_FATAL wind::Logger(__FILE__, __LINE__, wind::LogLevel::ERROR, LOG_TAG, true).stream()
#define LOG_FATAL_IF(expr)                                                                                             \
    if ((expr))                                                                                                        \
    wind::Logger(__FILE__, __LINE__, wind::LogLevel::ERROR, LOG_TAG, true).stream()
#endif // WIND_LOG_H
