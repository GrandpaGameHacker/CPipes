#pragma once
#include <Windows.h>
constexpr int MAX_PIPE_PATH = 256;
constexpr int MAX_PIPE_NAME = MAX_PIPE_PATH - 10;
const char PIPE_DIR[] = "\\\\.\\pipe\\";