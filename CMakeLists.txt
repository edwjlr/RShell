CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
	src/main.cpp
	src/executable.cpp
	src/parser.cpp
	src/semicolon.cpp
	src/connector.cpp
	src/or.cpp
	src/and.cpp
)
