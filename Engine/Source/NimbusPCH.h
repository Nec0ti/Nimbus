#pragma once

// Standard library
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

// Data structures
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>

// Math
#include <cmath>
#include <random>

// Third-party libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

// Platform-specific includes
#ifdef NIMBUS_PLATFORM_WINDOWS
    #include <Windows.h>
    #include <comdef.h>
#endif

#ifdef NIMBUS_PLATFORM_LINUX
    #include <unistd.h>
    #include <dlfcn.h>
#endif

// Engine core headers
#include "Nimbus/Core/Base.h"
#include "Nimbus/Core/Log.h"