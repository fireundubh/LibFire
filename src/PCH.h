#pragma once

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

#include "Constants.h"

using namespace std::literals;

namespace stl = SKSE::stl;

namespace logger = SKSE::log;

#define DLLEXPORT __declspec(dllexport)