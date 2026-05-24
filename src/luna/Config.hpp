#pragma once

#if defined _WIN32
#	define LUNA_PLAT_WINDOWS
#elif defined __APPLE__
#	define LUNA_PLAT_MACOS
#elif not defined __ANDROID__ and defined __linux__
#	define LUNA_PLAT_LINUX
#elif defined __ANDROID__
#	define LUNA_PLAT_ANDROID
#endif
