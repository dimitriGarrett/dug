#pragma once

/*
		
	All information here is based on the site at: https://web.archive.org/web/20191012035921/http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
*/

#if defined(_AIX)
	#define PLATFORM_AIX 1
#endif

#if defined(__unix__) || defined(__APPLE__) || defined (__MACH__)
	#if defined(__DragonFly__)
		#define PLATFORM_DRAGONFLY 1
	#elif defined(__FreeBSD__)
		#define PLATFORM_FREEBSD 1
	#elif defined(__NetBSD__)
		#define PLATFORM_NETBSD 1
	#elif defined(__OpenBSD__)
		#define PLATFORM_OPENBSD 1
	#endif
#endif

#if defined(__bsdi__)
	#define PLATFORM_BSD 1
#endif

#if defined(__hpux)
	#define PLATFORM_HP 1
#endif

#if defined(__GNU__)
	#define PLATFORM_GNU 1
#endif

#if defined(__gnu_linux__)
	#define PLATFORM_GNU_LINUX 1
#endif

#if defined (__linux__)
	#define PLATFORM_LINUX 1
#endif

#if defined(__APPLE__) || defined(__MACH__)
	#define PLATFORM_APPLE 1
	
	#include <TargetConditionals.h>
	#if TARGET_OS_EMBEDDED == 1
		#define APPLE_IOS 1
	#elif TARGET_IPHONE_SIMULATOR == 1
		#define APPLE_IOS_SIMULATOR 1
	#elif TARGET_OS_MAC == 1
		#define APPLE_MAC 1
	#endif
#endif

#if defined(__sun)
	#if defined(__SVR4)
		#define PLATFORM_SOLARIS 1
	#else
		#define PLATFORM_SUNOS 1
	#endif
#endif

#if defined(__CYGWIN__) && !defined(_WIN32)
	#define ENVIRONMENT_CYGWIN 1
#endif

#if defined(__MINGW64__)
	#define MINGW_64 1
#elif defined(__MINGW32__)
	#define MINGW_32 1
#endif

#if defined (_WIN32)
	#define PLATFORM_WINDOWS 1
	#if defined(_WIN64)
		#define WINDOWS_64 1
	#else
		#define WINDOWS_32 1
	#endif
#endif

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || defined(PLATFORM_APPLE))
	#define PLATFORM_UNIX 1

	#include <unistd.h>
	#if defined(_POSIX_VERSION)
		#define POSIX_COMPLIANT _POSIX_VERSION

		#if _POSIX_VERSION == 198808L
			#define POSIX_1988 198808L
		#elif _POSIX_VERSION == 199008L
			#define POSIX_1990 199008L
		#elif _POSIX_VERSION == 199506L
			#define ISO_POSIX_1996 199506L
		#elif _POSIX_VERSION == 200112L
			#define ISO_POSIX_2001 200112L
		#elif _POSIX_VERSION == 200809L
			#define ISO_POSIX_2008 200809L
		#endif
	#endif
#endif

// Common compiler tests
#if defined(__GNUC__) && !defined(__clang__)
	#define COMPILER_GCC 1
#endif

#if defined(__clang__)
	#define COMPILER_CLANG 1
#endif

#if defined(_MSC_VER)
	#define COMPILER_MSVC 1
#endif

#if defined(__INTEL_LLVM_COMPILER)
	#if defined(SYCL_LANGUAGE_VERSION)	
		#define COMPILER_INTELDPC 1
	#else
		#define COMPILER_INTEL 1
	#endif
#endif

#if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_BUILD_DATE)
	#define COMPILER_INTEL_CLASSIC 1
#endif

//Architecture
#include <cstdint>

#if INTPTR_MAX == INT64_MAX
	#define ARCHITECTURE_64 1
#elif INTPTR_MAX == INT32_MAX
	#define ARCHITECTURE_32 1
#endif

//Debug / Release modes
#if defined(_DEBUG) || defined(__DEBUG__) || defined(DEBUG)
	#define BUILD_DEBUG 1
#endif

#if defined(NDEBUG) || defined(__OPTIMIZE)
	#define BUILD_RELEASE 1
#endif