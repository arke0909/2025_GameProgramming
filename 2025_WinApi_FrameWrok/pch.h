#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ObjIdl.h>
#include <tchar.h>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <format>
#include <assert.h>
#include <filesystem>
#include <functional>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#pragma push_macro("new")
#undef new
#endif

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#ifdef _DEBUG
#pragma pop_macro("new")
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

namespace fs = std::filesystem;

#include "Defines.h"
#include "Vec2.h"
#include "Enums.h"
#include "TimeManager.h"
#include "GDISelector.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")

using std::vector;
using std::list;
using std::map;
using std::wstring;

#define PI 3.14159265358979f
#define CLASS_NAME L"M!uqom"
const float SCREEN_WIDTH = ::GetSystemMetrics(SM_CXSCREEN);
const float SCREEN_HEIGHT = ::GetSystemMetrics(SM_CYSCREEN);

#include <iostream>
using std::cout;
using std::endl;
