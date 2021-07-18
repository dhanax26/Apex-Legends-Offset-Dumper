#pragma once
#include <Windows.h>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <TlHelp32.h>
#include <Psapi.h>
#include <filesystem>

/*fmt*/
#include <fmt/core.h>
#include <fmt/color.h>

/*nlohmann json*/
#include <json.hpp>

/*Resources*/
#include "../Resources/xorstr/XorStr.hpp"
#include "../Resources/printa/printa.hpp"

/*Manager*/
#include "../Manager/Manager.hpp"

/*Dumper*/
#include "../Memory/FindPattern.hpp"

/*SDK*/
#include "../SDK/SDK.hpp"