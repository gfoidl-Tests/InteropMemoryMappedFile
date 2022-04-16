project(MMFLib C)

if (WIN32)
    set(NATIVE_SOURCES
        pal_windows.c
    )

    message("Building for Win32, sources: ${NATIVE_SOURCES}")
else()
    set(NATIVE_SOURCES
        pal_posix.c
    )

    message("Building for POSIX, sources: ${NATIVE_SOURCES}")
endif()

add_library(mmf_lib STATIC
    ${NATIVE_SOURCES}
)

target_include_directories(mmf_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# As we have the sources built-up, the linker can't be determined by cmake, so provide it help.
set_target_properties(mmf_lib PROPERTIES LINKER_LANGUAGE C)
