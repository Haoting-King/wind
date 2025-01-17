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

#pragma once

#include "EventLoopThread.h"

namespace wind {
namespace base {
class EventLoopThreadPool : NonCopyable {
public:
    explicit EventLoopThreadPool(EventLoop *mainLoop, string name = "WindEventLoopThreadPool");
    ~EventLoopThreadPool() noexcept;

    void setThreadNum(size_t threadNum)
    {
        if (running_) {
            return;
        }
        threadNum_ = threadNum;
    }

    EventLoop *getNextLoop();
    void start();
    const string &name() const
    {
        return name_;
    }

private:
    EventLoop *mainLoop_ = nullptr;
    string name_;
    size_t threadNum_ = 0;
    std::atomic<bool> running_ = false;
    std::vector<std::unique_ptr<EventLoopThread>> loopThreads_;
    std::vector<EventLoop *> loops_;
    size_t currLoopIdx_ = 0;
};
} // namespace base
} // namespace wind
