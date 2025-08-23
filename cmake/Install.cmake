# Install configuration for Nimbus Engine

# Install binaries
install(TARGETS NimbusEditor NimbusRuntime
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

# Install headers
install(DIRECTORY Engine/Include/
    DESTINATION include/NimbusEngine
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

# Install assets
install(DIRECTORY Assets/
    DESTINATION share/NimbusEngine/Assets)

# Install documentation
install(FILES README.md LICENSE
    DESTINATION share/doc/NimbusEngine)

# Platform-specific install configurations
if(WIN32)
    # Windows-specific install
    set(CPACK_GENERATOR "NSIS;ZIP")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
elseif(NIMBUS_PLATFORM_LINUX)
    # Linux-specific install
    set(CPACK_GENERATOR "DEB;RPM;TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nimbus Engine Team")
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
endif()

# Set install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(WIN32)
        set(CMAKE_INSTALL_PREFIX "C:/Program Files/NimbusEngine" CACHE PATH "Install path prefix" FORCE)
    else()
        set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install path prefix" FORCE)
    endif()
endif()