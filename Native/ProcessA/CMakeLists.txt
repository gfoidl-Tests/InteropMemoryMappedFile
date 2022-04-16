project(MMFServer C)

add_executable(mmf_server
    main.c
)

target_link_libraries(mmf_server PRIVATE
    mmf_lib
)
