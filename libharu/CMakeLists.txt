find_package(unofficial-libharu CONFIG REQUIRED)

add_executable(hello_world_libharu main.cpp)
target_link_libraries(hello_world_libharu PRIVATE unofficial::libharu::hpdf)