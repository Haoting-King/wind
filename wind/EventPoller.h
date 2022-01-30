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

#ifndef WIND_EVENT_POLLER_H
#define WIND_EVENT_POLLER_H

#include <cstddef>
#include <memory>
#include <sys/epoll.h>
#include <unordered_map>
#include <vector>

#include "EventChannel.h"

namespace wind {
class EventPoller : NonCopyable {
public:
    EventPoller();
    ~EventPoller() noexcept;

    TimeStamp pollOnce(std::vector<std::shared_ptr<EventChannel>> &activeChannels, int timeOutMs);
    void updateChannel(std::shared_ptr<EventChannel> channel);
    void removeChannel(int fd);

private:
    UniqueFd epollFd_;
    static size_t eventSize_;
    std::vector<epoll_event> activeEvents_; // to receive events from epoll_wait. 
    std::unordered_map<int, std::shared_ptr<EventChannel>> channels_;
};
} // namespace wind
#endif // WIND_EVENT_POLLER_H
