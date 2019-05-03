include(ExternalProject)


ExternalProject_Add(
    ultralight
    PREFIX ${CMAKE_BINARY_DIR}/external/ultralight
    URL https://ultralig.ht/ultralight-sdk-1.0-win.zip
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(ultralight source_dir)
message(STATUS "ultralight source dir is: ${source_dir}")

set(ULTRALIGHT_INCLUDE_DIR ${source_dir}/include)
set(ULTRALIGHT_LIB_DIR ${source_dir}/lib/win/x86)

function(ultralight_add_dependency target)
    add_dependencies(${target} ultralight)
    target_link_libraries(${target} ${ULTRALIGHT_LIB_DIR}/AppCore.lib)
    target_link_libraries(${target} ${ULTRALIGHT_LIB_DIR}/Ultralight.lib)
    target_link_libraries(${target} ${ULTRALIGHT_LIB_DIR}/UltralightCore.lib)
    target_link_libraries(${target} ${ULTRALIGHT_LIB_DIR}/WebCore.lib)
	target_include_directories(${target} PUBLIC ${ULTRALIGHT_INCLUDE_DIR})

	# TODO: Add copy function / manage dependencies
endfunction()



