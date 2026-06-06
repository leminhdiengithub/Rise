#pragma once

#ifdef RS_PLATFORM_WINDOWS // Nếu đang chạy trên Windows
	#ifdef RS_BUILD_DLL     // Nếu đang BUILD file DLL
		#define RISE_API __declspec(dllexport)  // → Xuất ra
	#else 
		#define RISE_API __declspec(dllimport)   // → Nhập vào
	#endif
#else
	#error Rise only support Window! // Không phải Windows → báo lỗi
#endif 

#define BTT(x) (1 << x)