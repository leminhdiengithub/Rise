#pragma once

#if RS_DEBUG
	#define RS_ENABLE_ASSERTS
#endif

#ifdef RS_ENABLE_ASSERTS

#define RS_ASSERT(x, ...) \
    { if(!(x)) { RS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define RS_CORE_ASSERT(x, ...) \
    { if(!(x)) { RS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

#define RS_ASSERT(x, ...)
#define RS_CORE_ASSERT(x, ...)

#endif

#define BTT(x) (1 << x)

#define RS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)