#pragma once

/// Macros to switch off warnings from external header
// Switch warnings off for vc
#ifdef _WIN32

// __pragma(warning(push,0)) ?
#define SWITCH_WARNINGS_OFF  \
                __pragma(warning(push)) \
                __pragma(warning(disable:4127)) \
                __pragma(warning(disable:4129)) \
                __pragma(warning(disable:4231)) \
                __pragma(warning(disable:4244)) \
                __pragma(warning(disable:4251)) \
				__pragma(warning(disable:4275)) \
                __pragma(warning(disable:4431)) \
                __pragma(warning(disable:4481)) \
                __pragma(warning(disable:4512)) \
                __pragma(warning(disable:4800)) \
                __pragma(warning(disable:4996)) \
				__pragma(warning(disable:6326))

#define SWITCH_WARNINGS_ON __pragma(warning(pop))

#define SUPPRESS_DLL_WARNING __pragma(warning(suppress:4251))

#endif

// Switch warnings off for clang
#ifdef __clang__

#define SWITCH_WARNINGS_OFF \
                _Pragma("clang diagnostic push")\
                _Pragma("clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")\

#define SWITCH_WARNINGS_ON _Pragma("clang diagnostic pop")

#define SUPPRESS_DLL_WARNING

#endif




// Do nothing if other compiler is used
#ifndef _WIN32
#ifndef __clang__

#undef SWITCH_WARNINGS_OFF
#define SWITCH_WARNINGS_OFF
#undef SWITCH_WARNINGS_ON
#define SWITCH_WARNINGS_ON

#define SUPPRESS_DLL_WARNING

#endif
#endif


