# MIT License

# Copyright (c) 2020 Tracy

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(WIND_BASE_SRC
    CurrentThread.cpp
    EventChannel.cpp
    EventPoller.cpp
    EventLoop.cpp
    EventLoopThread.cpp
    EventLoopThreadPool.cpp
    Log.cpp
    LogDaemon.cpp
    LogFile.cpp
    LogStream.cpp
    ThreadPool.cpp
    TimeStamp.cpp
    Timer.cpp
    TimerManager.cpp
    Utils.cpp
)

add_library(wind_base ${WIND_BASE_SRC})
target_link_libraries(wind_base pthread)

add_subdirectory(tests)
