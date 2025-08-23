# Nimbus Editor Application

# Collect source files
file(GLOB_RECURSE EDITOR_SOURCES
    Source/*.cpp
    Source/*.c
)

file(GLOB_RECURSE EDITOR_HEADERS
    Include/*.h
    Include/*.hpp
)

# Create the editor executable
add_executable(NimbusEditor ${EDITOR_SOURCES} ${EDITOR_HEADERS})

# Include directories
target_include_directories(NimbusEditor
    PRIVATE
        Include
        ${CMAKE_SOURCE_DIR}/Engine/Include
)

# Link engine and dependencies
target_link_libraries(NimbusEditor
    PRIVATE
        NimbusEngine
)

# Set target properties
set_target_properties(NimbusEditor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    FOLDER "Editor"
)

# Set working directory for debugging
set_target_properties(NimbusEditor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Copy assets to build directory
add_custom_command(TARGET NimbusEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:NimbusEditor>/Assets
    COMMENT "Copying assets to build directory"
)

# Install target
install(TARGETS NimbusEditor
    RUNTIME DESTINATION bin
    COMPONENT Editor
)