include(cpfPackageProject)
include(cpfAddCppPackageComponent)
include(cpfLocations)

#-----------------------------------------------------
function( getIncludeFileCompileOptions optionsOut switchWarningsOffHeader )
	cpfGetCompiler(compiler)
	if((${compiler} STREQUAL Gcc) OR (${compiler} STREQUAL Clang))
		set( options "-include$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${switchWarningsOffHeader}>$<INSTALL_INTERFACE:install/${switchWarningsOffHeader}>" )
	elseif( (${compiler} STREQUAL Vc) AND (${CMAKE_GENERATOR} MATCHES "^Visual Studio.*$") )
		set( options "/FI$<BUILD_INTERFACE:\"${CMAKE_CURRENT_SOURCE_DIR}/${switchWarningsOffHeader}\">$<INSTALL_INTERFACE:install/${switchWarningsOffHeader}>" )
	elseif( (${compiler} STREQUAL Vc) ) # With Ninja the quotes are not dereferenced.
		set( options "/FI$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${switchWarningsOffHeader}>$<INSTALL_INTERFACE:install/${switchWarningsOffHeader}>" )
	else()
		message (FATAL_ERROR "Compiler ${compiler} is not supported by function getIncludeFileCompileOptions().")
	endif()
	set(${optionsOut} ${options} PARENT_SCOPE)
endfunction()

#-----------------------------------------------------
# Target libSwitchWarningsOffMacro

# This targets ccbContains functions that extend the classes from the STL

set( longDescription 
"The package provides only the SwitchWarningsOffMacro.h header. 
The header file is automatically added to the include defintions of client targets, to make sure it must not manually included for each source file.
"
)

cpfPackageProject(
	BRIEF_DESCRIPTION				"A package that provides macros to switch of warnings from external headers."
	LONG_DESCRIPTION				${longDescription}
	WEBPAGE_URL						"https://github.com/Knitschi/libSwitchWarningsOff"
	OWNER 							Knitschi
	TARGET_NAMESPACE swo
	COMPONENTS 						SINGLE_COMPONENT
	PACKAGE_ARCHIVES
		PACKAGE_ARCHIVE_CONTENT_TYPE 	CT_DEVELOPER
		PACKAGE_ARCHIVE_FORMATS 		7Z
	PACKAGE_ARCHIVES
		PACKAGE_ARCHIVE_CONTENT_TYPE 	CT_SOURCES
		PACKAGE_ARCHIVE_FORMATS 		7Z
)

set( switchWarningsOffHeader SwitchWarningsOff.h )

cpfAddCppPackageComponent(
	TYPE							INTERFACE_LIB
	PUBLIC_HEADER					${switchWarningsOffHeader}
	ENABLE_CLANG_FORMAT_TARGETS		FALSE
)

# Add the public compile options that force includes the header with clients.
getIncludeFileCompileOptions( includeFlags ${switchWarningsOffHeader})
target_compile_options(${PROJECT} INTERFACE ${includeFlags})

cpfFinalizePackageProject()