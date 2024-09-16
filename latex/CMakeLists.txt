find_package(inja CONFIG REQUIRED)

add_executable(hello_world_latex main.cpp)

add_executable(hello_world_latex2 main2.cpp)
target_link_libraries(hello_world_latex2 PRIVATE pantor::inja)