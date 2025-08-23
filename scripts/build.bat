@echo off
setlocal enabledelayedexpansion

REM Nimbus Engine Build Script for Windows
REM This script helps build the Nimbus Engine on Windows systems

echo [INFO] Starting Nimbus Engine build process...

REM Default values
set BUILD_TYPE=Release
set BUILD_DIR=build
set CLEAN_BUILD=false
set INSTALL=false
set PACKAGE=false
set JOBS=%NUMBER_OF_PROCESSORS%

REM Parse command line arguments
:parse_args
if "%~1"=="" goto :end_parse
if "%~1"=="-d" (
    set BUILD_TYPE=Debug
    shift
    goto :parse_args
)
if "%~1"=="--debug" (
    set BUILD_TYPE=Debug
    shift
    goto :parse_args
)
if "%~1"=="-c" (
    set CLEAN_BUILD=true
    shift
    goto :parse_args
)
if "%~1"=="--clean" (
    set CLEAN_BUILD=true
    shift
    goto :parse_args
)
if "%~1"=="-i" (
    set INSTALL=true
    shift
    goto :parse_args
)
if "%~1"=="--install" (
    set INSTALL=true
    shift
    goto :parse_args
)
if "%~1"=="-p" (
    set PACKAGE=true
    shift
    goto :parse_args
)
if "%~1"=="--package" (
    set PACKAGE=true
    shift
    goto :parse_args
)
if "%~1"=="-j" (
    set JOBS=%~2
    shift
    shift
    goto :parse_args
)
if "%~1"=="--jobs" (
    set JOBS=%~2
    shift
    shift
    goto :parse_args
)
if "%~1"=="-h" (
    goto :show_help
)
if "%~1"=="--help" (
    goto :show_help
)
echo [ERROR] Unknown option: %~1
exit /b 1
:end_parse

echo [INFO] Build type: %BUILD_TYPE%
echo [INFO] Build directory: %BUILD_DIR%
echo [INFO] Parallel jobs: %JOBS%

REM Check for required tools
echo [INFO] Checking for required tools...

REM Check for CMake
where cmake >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo [ERROR] CMake not found. Please install CMake 3.20 or later.
    exit /b 1
)

REM Check for Visual Studio or MSBuild
where msbuild >nul 2>&1
if %ERRORLEVEL% equ 0 (
    echo [INFO] Found MSBuild
    set BUILD_SYSTEM=msbuild
) else (
    where devenv >nul 2>&1
    if %ERRORLEVEL% equ 0 (
        echo [INFO] Found Visual Studio
        set BUILD_SYSTEM=vs
    ) else (
        echo [WARNING] No build system found. Using CMake default.
        set BUILD_SYSTEM=cmake
    )
)

REM Create build directory
if "%CLEAN_BUILD%"=="true" (
    echo [INFO] Cleaning build directory...
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
)

if not exist "%BUILD_DIR%" (
    echo [INFO] Creating build directory...
    mkdir "%BUILD_DIR%"
)

REM Navigate to build directory
cd "%BUILD_DIR%"

REM Configure with CMake
echo [INFO] Configuring with CMake...
cmake .. ^
    -DCMAKE_BUILD_TYPE="%BUILD_TYPE%" ^
    -DNIMBUS_BUILD_EDITOR=ON ^
    -DNIMBUS_BUILD_EXAMPLES=ON ^
    -DNIMBUS_VULKAN_ENABLED=ON ^
    -DNIMBUS_OPENGL_ENABLED=ON ^
    -DNIMBUS_DIRECTX_ENABLED=ON

if %ERRORLEVEL% neq 0 (
    echo [ERROR] CMake configuration failed
    exit /b 1
)

REM Build the project
echo [INFO] Building Nimbus Engine...
if "%BUILD_SYSTEM%"=="msbuild" (
    msbuild NimbusEngine.sln /p:Configuration=%BUILD_TYPE% /m:%JOBS%
) else (
    cmake --build . --config %BUILD_TYPE% --parallel %JOBS%
)

if %ERRORLEVEL% neq 0 (
    echo [ERROR] Build failed
    exit /b 1
)

echo [SUCCESS] Build completed successfully!

REM Install if requested
if "%INSTALL%"=="true" (
    echo [INFO] Installing Nimbus Engine...
    cmake --install . --config %BUILD_TYPE%
    
    if %ERRORLEVEL% neq 0 (
        echo [ERROR] Installation failed
        exit /b 1
    )
    
    echo [SUCCESS] Installation completed successfully!
)

REM Create package if requested
if "%PACKAGE%"=="true" (
    echo [INFO] Creating package...
    cmake --build . --config %BUILD_TYPE% --target package
    
    if %ERRORLEVEL% neq 0 (
        echo [ERROR] Package creation failed
        exit /b 1
    )
    
    echo [SUCCESS] Package created successfully!
)

echo [SUCCESS] Nimbus Engine build process completed!
echo [INFO] You can now run the engine with: NimbusEngine.exe
exit /b 0

:show_help
echo Nimbus Engine Build Script for Windows
echo.
echo Usage: %0 [OPTIONS]
echo.
echo Options:
echo   -d, --debug     Build in Debug mode (default: Release)
echo   -c, --clean     Clean build directory before building
echo   -i, --install   Install after building
echo   -p, --package   Create package after building
echo   -j, --jobs N    Number of parallel jobs (default: auto)
echo   -h, --help      Show this help message
exit /b 0