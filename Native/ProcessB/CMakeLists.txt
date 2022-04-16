project(MMFClient C)

add_executable(mmf_client
    main.c
)

target_link_libraries(mmf_client PRIVATE
    mmf_lib
)
