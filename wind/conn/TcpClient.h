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

#include "Connector.h"
#include "TcpConnection.h"

namespace wind {
namespace conn {
class TcpClient : base::NonCopyable {
public:
    TcpClient(base::EventLoop *loop, string name, const SockAddrInet &remoteAddr);
    virtual ~TcpClient() noexcept;

    const string &name() const
    {
        return name_;
    }

    void start();
    void stop();

private:
    void assertInLoopThread();

    // callback for connector_, would be called in loop thread.
    void onConnect(int sockFd);

    base::EventLoop *loop_ = nullptr;
    string name_;
    ConnectorPtr connector_;

    std::atomic<bool> started_ = false;

    std::atomic<uint64_t> nextConnId_;
    mutable std::mutex mutex_;
    TcpConnectionPtr connection_; // guarded by mutex_.
};
} // namespace conn
} // namespace wind
