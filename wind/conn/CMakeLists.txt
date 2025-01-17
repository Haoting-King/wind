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

include(CheckFunctionExists)

check_function_exists(accept4 HAVE_ACCEPT4)
if(NOT HAVE_ACCEPT4)
  set_source_files_properties(Socket.cpp PROPERTIES COMPILE_FLAGS "-DNO_ACCEPT4")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(WIND_CONN_SRC
    Acceptor.cpp
    Buffer.cpp
    Connector.cpp
    SockAddr.cpp
    Socket.cpp
    TcpConnection.cpp
    TcpServer.cpp
    TcpClient.cpp
)

add_library(wind_conn ${WIND_CONN_SRC})
target_link_libraries(wind_conn wind_base)

add_subdirectory(tests)
