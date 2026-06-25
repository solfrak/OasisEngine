add_library(OasisPlatform STATIC
    src/Platform.cpp
)

target_include_directories(OasisPlatform
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(OasisPlatform PUBLIC cxx_std_20)

target_link_libraries(OasisPlatform
    PUBLIC
        Oasis::Core
)

add_library(Oasis::Platform ALIAS OasisPlatform)
