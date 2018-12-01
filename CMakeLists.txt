include(cpfInitPackageProject)
include(cpfAddCppPackage)
include(cpfLocations)

#-----------------------------------------------------
function( getForceIncludeOption optionOut )
	cpfGetCompiler(compiler)
	if((${compiler} STREQUAL Gcc) OR (${compiler} STREQUAL Clang))
		set( option -include )
	elseif( ${compiler} STREQUAL Vc )
		set( option /FI)
	else()
		message (FATAL_ERROR "Compiler ${compiler} is not supported by function getForceIncludeOption().")
	endif()
	set(${optionOut} ${option} PARENT_SCOPE)
endfunction()

#-----------------------------------------------------
function( getIncludeFileCompileOptions optionsOut switchWarningsOffHeader )
	cpfGetCompiler(compiler)
	if((${compiler} STREQUAL Gcc) OR (${compiler} STREQUAL Clang))
		set( options "-include$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${switchWarningsOffHeader}>$<INSTALL_INTERFACE:install/${switchWarningsOffHeader}>" )
	elseif( (${compiler} STREQUAL Vc) AND (${CMAKE_GENERATOR} MATCHES "^Visual Studio.*$") )
		set( options "/FI$<BUILD_INTERFACE:\"${CMAKE_CURRENT_SOURCE_DIR}/${switchWarningsOffHeader}\">$<INSTALL_INTERFACE:install/${switchWarningsOffHeader}>" )
	elseif( (${compiler} STREQUAL Vc) ) # With Ninja the apostophes are not derefernced.
		set( options "/FI$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${switchWarningsOffHeader}>$<INSTALL_INTERFACE:install/${switchWarningsOffHeader}>" )
	else()
		message (FATAL_ERROR "Compiler ${compiler} is not supported by function getIncludeFileCompileOptions().")
	endif()
	set(${optionsOut} ${options} PARENT_SCOPE)
endfunction()

#-----------------------------------------------------
# Target libSwitchWarningsOffMacro

# This targets ccbContains functions that extend the classes from the STL

set( PACKAGE_NAMESPACE swo )
cpfInitPackageProject()


set( briefDescription "A package that provides macros to switch of warnings from external headers." )

set( longDescription 
"The package provides only the SwitchWarningsOffMacro.h header. 
The header file is automatically added to the include defintions of client targets, to make sure it must not manually included for each source file.
"
)

#### add library without CppCodeBase, because it does not support interface libraries yet
set( switchWarningsOffHeader SwitchWarningsOff.h )
cpfGetPackageName(package)
add_library( ${package} INTERFACE )

set(filesTarget ${package}Files)
add_custom_target( ${filesTarget} SOURCES ${switchWarningsOffHeader} )
set_property(TARGET ${filesTarget} PROPERTY FOLDER ${package} )


getIncludeFileCompileOptions( includeFlags ${switchWarningsOffHeader} )
target_compile_options( ${package} INTERFACE ${includeFlags} )

#target_compile_definitions( ${package} INTERFACE BLUB )

## install rules
cpfGetRelativeOutputDir( relIncludeDir ${package} INCLUDE)
cpfGetTargetsExportsName( targetsExportName ${package})

# exported targets
install( 
	TARGETS ${package}
	EXPORT ${targetsExportName}
	COMPONENT ${package}
	INCLUDES DESTINATION "${relIncludeDir}"
)

# install header file
install(
	FILES ${switchWarningsOffHeader}
	COMPONENT ${package}
	DESTINATION "${relIncludeDir}"
)

# generate and install cmake files
cpfGetRelativeOutputDir( relConfigDir ${package} CMAKE_CONFIG)
set(packageConfigFile ${package}Config.cmake)
set(versionConfigFile ${package}ConfigVersion.cmake )
set(packageConfigFileFull "${CMAKE_CURRENT_BINARY_DIR}/${packageConfigFile}")	# The config file is used by find package 
set(versionConfigFileFull "${CMAKE_CURRENT_BINARY_DIR}/${versionConfigFile}")

configure_package_config_file(
	${CPF_PACKAGE_CONFIG_TEMPLATE}
	"${packageConfigFileFull}"
	INSTALL_DESTINATION ${relConfigDir}
)
	
write_basic_package_version_file( 
	"${versionConfigFileFull}" 
	COMPATIBILITY ExactVersion # currently we assume globally that this compatibility scheme applies
) 

# Install cmake exported targets config file
# This can not be done in the configs loop, so we need a generator expression for the output directory
install(
	EXPORT "${targetsExportName}"
	COMPONENT ${package}
	NAMESPACE "${PACKAGE_NAMESPACE}::"
	DESTINATION "${relConfigDir}"
)

# Install cmake config files
install(
	FILES "${packageConfigFileFull}" "${versionConfigFileFull}"
	COMPONENT ${package}
	DESTINATION "${relConfigDir}"
)
