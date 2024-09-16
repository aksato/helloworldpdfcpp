find_package(PoDoFo CONFIG REQUIRED)

add_executable(hello_world_podofo main.cpp)
target_link_libraries(hello_world_podofo PRIVATE $<IF:$<TARGET_EXISTS:podofo_shared>,podofo_shared,podofo_static>)
