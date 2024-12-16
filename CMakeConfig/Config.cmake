
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT isConfigDone)

    set(isConfigDone TRUE)

    if (MSVC)
        add_compile_options(/Zc:__cplusplus)
    endif()

    get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

    if(isMultiConfig)
        set(CMAKE_CONFIGURATION_TYPES "Debug;MinSizeRel;Editor" CACHE STRING "" FORCE) 
    else()
        message(FATAL_ERROR "Only MULTI_CONFIG is supported!")
    endif()
    
    set(CMAKE_CXX_FLAGS_EDITOR "${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS_EDITOR "${CMAKE_C_FLAGS_DEBUG}")
    set(CMAKE_EXE_LINKER_FLAGS_EDITOR "${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
    set(CMAKE_SHARED_LINKER_FLAGS_EDITOR "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")

endif()
