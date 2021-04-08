#pragma once

/// Macros to switch off warnings from external header
// Switch warnings off for vc
#ifdef _MSC_VER

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
					__pragma(warning(disable:6326)) \
					__pragma(warning(disable:26400)) \
					__pragma(warning(disable:26401)) \
					__pragma(warning(disable:26408)) \
					__pragma(warning(disable:26409)) \
					__pragma(warning(disable:26426)) \
					__pragma(warning(disable:26429)) \
					__pragma(warning(disable:26432)) \
					__pragma(warning(disable:26434)) \
					__pragma(warning(disable:26435)) \
					__pragma(warning(disable:26439)) \
					__pragma(warning(disable:26440)) \
					__pragma(warning(disable:26443)) \
					__pragma(warning(disable:26444)) \
					__pragma(warning(disable:26446)) \
					__pragma(warning(disable:26447)) \
					__pragma(warning(disable:26451)) \
					__pragma(warning(disable:26455)) \
					__pragma(warning(disable:26456)) \
					__pragma(warning(disable:26460)) \
					__pragma(warning(disable:26461)) \
					__pragma(warning(disable:26462)) \
					__pragma(warning(disable:26465)) \
					__pragma(warning(disable:26466)) \
					__pragma(warning(disable:26471)) \
					__pragma(warning(disable:26472)) \
					__pragma(warning(disable:26473)) \
					__pragma(warning(disable:26474)) \
					__pragma(warning(disable:26475)) \
					__pragma(warning(disable:26476)) \
					__pragma(warning(disable:26481)) \
					__pragma(warning(disable:26482)) \
					__pragma(warning(disable:26485)) \
					__pragma(warning(disable:26486)) \
					__pragma(warning(disable:26487)) \
					__pragma(warning(disable:26489)) \
					__pragma(warning(disable:26490)) \
					__pragma(warning(disable:26491)) \
					__pragma(warning(disable:26492)) \
					__pragma(warning(disable:26493)) \
					__pragma(warning(disable:26494)) \
					__pragma(warning(disable:26495)) \
					__pragma(warning(disable:26496)) \
					__pragma(warning(disable:26497)) \
					__pragma(warning(disable:26498)) \

	#define SWITCH_WARNINGS_ON __pragma(warning(pop))

	#define SUPPRESS_DLL_WARNING __pragma(warning(suppress:4251))

#endif

#define CLANG_COMPILER (defined(__GNUC__) && defined(__clang__))

// Switch warnings off for clang
#ifdef __GNUC__
	#ifdef __clang__

		#define SWITCH_WARNINGS_OFF \
						_Pragma("clang diagnostic push")\
						_Pragma("clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")\


		#define SWITCH_WARNINGS_ON _Pragma("clang diagnostic pop")

		#define SUPPRESS_DLL_WARNING

	#endif
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


