# Engine Core Module

# Collect source files
file(GLOB_RECURSE ENGINE_SOURCES
    Source/*.cpp
    Source/*.c
)

file(GLOB_RECURSE ENGINE_HEADERS
    Include/*.h
    Include/*.hpp
)

# Create the engine library
add_library(NimbusEngine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Include directories
target_include_directories(NimbusEngine
    PUBLIC
        Include
    PRIVATE
        Source
)

# Link third-party dependencies
target_link_libraries(NimbusEngine
    PUBLIC
        NimbusThirdParty
)

# Platform-specific compile definitions
target_compile_definitions(NimbusEngine
    PUBLIC
        $<$<CONFIG:Debug>:NIMBUS_DEBUG>
        $<$<CONFIG:Release>:NIMBUS_RELEASE>
        $<$<CONFIG:RelWithDebInfo>:NIMBUS_RELEASE>
        $<$<CONFIG:MinSizeRel>:NIMBUS_RELEASE>
)

# Precompiled headers
target_precompile_headers(NimbusEngine
    PRIVATE
        Source/NimbusPCH.h
)

# Set target properties
set_target_properties(NimbusEngine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    FOLDER "Engine"
)

# Install targets
install(TARGETS NimbusEngine
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT Engine
)