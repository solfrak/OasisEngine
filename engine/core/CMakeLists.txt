add_library(OasisCore STATIC
    src/Core.cpp
    src/Log.cpp
)

target_include_directories(OasisCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(OasisCore PUBLIC cxx_std_20)

add_library(Oasis::Core ALIAS OasisCore)
