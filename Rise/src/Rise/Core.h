#pragma once

#ifdef RS_PLATFORM_WINDOWS // Nếu đang chạy trên Windows
	#ifdef RS_BUILD_DLL     // Nếu đang BUILD file DLL
		#define RISE_API __declspec(dllexport)  // → Xuất ra (chỉ sử dụng khi SandBox gọi)
	#else 
		#define RISE_API __declspec(dllimport)   // → Nhập vào
	#endif
#else
	#error Rise only support Window! // Không phải Windows → báo lỗi
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