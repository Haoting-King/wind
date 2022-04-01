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

#include "TcpConnection.h"

namespace wind {
namespace conn {
using namespace base;

TcpConnection::TcpConnection(EventLoop *loop, string name, int sockFd)
    : loop_(loop),
      name_(std::move(name)),
      socket_(sockFd),
      localAddr_(sockets::getLocalAddrInet(sockFd)),
      peerAddr_(sockets::getPeerAddrInet(sockFd)),
      channel_(std::make_shared<EventChannel>(sockFd, loop_))
{
    channel_->setReadCallback([this](TimeStamp receivedTime) { onChannelReadable(receivedTime); });
    channel_->setWriteCallback([this]() { onChannelWritable(); });
    channel_->setErrorCallback([this]() { onChannelError(); });
    channel_->setCloseCallback([this]() { onChannelClose(); });
    socket_.setKeepAlive(true);
    setState(TcpConnectionState::CONNECTING);
}

TcpConnection::~TcpConnection() noexcept {}

void TcpConnection::connectionEstablished()
{
    loop_->runInLoop([this]() {
        ASSERT(state() == TcpConnectionState::CONNECTING);
        auto sharedObj = shared_from_this();
        channel_->tie(sharedObj);
        channel_->enableReading(true);
        setState(TcpConnectionState::CONNECTED);
        if (connectionCallback_ != nullptr) {
            connectionCallback_(sharedObj);
        }
    });
}

void TcpConnection::connectionRemoved() {}

// TODO: handle channel events.
void TcpConnection::onChannelReadable(TimeStamp receivedTime)
{
    (void)receivedTime;
}
void TcpConnection::onChannelWritable() {}
void TcpConnection::onChannelError() {}
void TcpConnection::onChannelClose() {}
} // namespace conn
} // namespace wind