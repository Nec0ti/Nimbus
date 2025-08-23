# Package configuration for Nimbus Engine

set(CPACK_PACKAGE_NAME "NimbusEngine")
set(CPACK_PACKAGE_VENDOR "Nimbus Engine Team")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Advanced 3D Game Engine")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "NimbusEngine")

# Resource files
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# Windows-specific packaging
if(WIN32)
    set(CPACK_NSIS_DISPLAY_NAME "Nimbus Engine ${PROJECT_VERSION}")
    set(CPACK_NSIS_PACKAGE_NAME "Nimbus Engine")
    set(CPACK_NSIS_CONTACT "support@nimbusengine.com")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://nimbusengine.com")
    set(CPACK_NSIS_HELP_LINK "https://docs.nimbusengine.com")
    
    # Create desktop shortcut
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut '$DESKTOP\\\\Nimbus Engine.lnk' '$INSTDIR\\\\bin\\\\NimbusEditor.exe'")
    set(CPACK_NSIS_DELETE_ICONS_EXTRA
        "Delete '$DESKTOP\\\\Nimbus Engine.lnk'")
    
    # Add to Start Menu
    set(CPACK_NSIS_MENU_LINKS
        "bin/NimbusEditor.exe" "Nimbus Engine Editor"
        "share/doc/NimbusEngine/README.md" "Documentation")
endif()

# Linux-specific packaging
if(NIMBUS_PLATFORM_LINUX)
    # Debian package
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Advanced 3D Game Engine
 Nimbus Engine is a professional-grade 3D game engine that rivals Unity
 in functionality and user experience. Features sophisticated graphical
 user interface, robust 3D rendering capabilities, comprehensive asset
 management, and cross-platform deployment tools.")
    set(CPACK_DEBIAN_PACKAGE_SECTION "games")
    set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgl1-mesa-dev, libglfw3-dev, libassimp-dev, libfreetype6-dev")
    
    # RPM package
    set(CPACK_RPM_PACKAGE_SUMMARY "Advanced 3D Game Engine")
    set(CPACK_RPM_PACKAGE_DESCRIPTION ${CPACK_DEBIAN_PACKAGE_DESCRIPTION})
    set(CPACK_RPM_PACKAGE_GROUP "Amusements/Games")
    set(CPACK_RPM_PACKAGE_REQUIRES "mesa-libGL-devel, glfw-devel, assimp-devel, freetype-devel")
    
    # Arch Linux package (custom)
    if(EXISTS "/etc/arch-release")
        set(CPACK_GENERATOR "TGZ")
        set(CPACK_PACKAGE_FILE_NAME "nimbusengine-${PROJECT_VERSION}-x86_64")
        
        # Create PKGBUILD for Arch
        configure_file(
            "${CMAKE_SOURCE_DIR}/packaging/PKGBUILD.in"
            "${CMAKE_BINARY_DIR}/PKGBUILD"
            @ONLY
        )
    endif()
endif()

# Component-based installation
set(CPACK_COMPONENTS_ALL Engine Editor Runtime Documentation)

set(CPACK_COMPONENT_ENGINE_DISPLAY_NAME "Engine Core")
set(CPACK_COMPONENT_ENGINE_DESCRIPTION "Core engine libraries and headers")
set(CPACK_COMPONENT_ENGINE_REQUIRED TRUE)

set(CPACK_COMPONENT_EDITOR_DISPLAY_NAME "Nimbus Editor")
set(CPACK_COMPONENT_EDITOR_DESCRIPTION "Visual editor application")
set(CPACK_COMPONENT_EDITOR_DEPENDS Engine)

set(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Runtime Libraries")
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime libraries for game deployment")
set(CPACK_COMPONENT_RUNTIME_DEPENDS Engine)

set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION "API documentation and tutorials")

include(CPack)