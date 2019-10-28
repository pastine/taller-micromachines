add_library(HelloWorld SHARED
        libHelloWorld.cpp)

add_executable(mods_test
        modsTests.cpp
        )

target_link_libraries(mods_test HelloWorld ${CMAKE_DL_LIBS})
