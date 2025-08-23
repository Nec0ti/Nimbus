#!/bin/bash
# Nimbus Engine Build Script
# Supports Linux and Windows (via Git Bash/MSYS2)

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
BUILD_TYPE="Release"
ENABLE_VULKAN=OFF
ENABLE_DIRECTX12=OFF
BUILD_TESTS=OFF
INSTALL_DEPS=false
CLEAN_BUILD=false
JOBS=$(nproc 2>/dev/null || echo 4)

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show usage
show_usage() {
    echo "Nimbus Engine Build Script"
    echo ""
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -h, --help           Show this help message"
    echo "  -d, --debug          Build in Debug mode (default: Release)"
    echo "  -c, --clean          Clean build directory before building"
    echo "  -t, --tests          Enable building tests"
    echo "  -v, --vulkan         Enable Vulkan rendering backend"
    echo "  -x, --directx12      Enable DirectX 12 backend (Windows only)"
    echo "  -i, --install-deps   Install system dependencies"
    echo "  -j, --jobs N         Number of parallel jobs (default: $JOBS)"
    echo ""
    echo "Examples:"
    echo "  $0                   # Build release version"
    echo "  $0 -d -t             # Build debug with tests"
    echo "  $0 -v -x             # Build with Vulkan and DirectX 12"
    echo "  $0 -c -j 8           # Clean build with 8 jobs"
}

# Function to detect platform
detect_platform() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "linux"
    elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
        echo "windows"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macos"
    else
        echo "unknown"
    fi
}

# Function to install dependencies on Linux
install_linux_deps() {
    print_status "Installing dependencies for Linux..."
    
    if command -v apt >/dev/null 2>&1; then
        # Ubuntu/Debian
        sudo apt update
        sudo apt install -y build-essential cmake git
        sudo apt install -y libgl1-mesa-dev libglfw3-dev libassimp-dev libfreetype6-dev
        sudo apt install -y libopenal-dev libbullet-dev
    elif command -v pacman >/dev/null 2>&1; then
        # Arch Linux
        sudo pacman -S --needed base-devel cmake git
        sudo pacman -S --needed mesa glfw-x11 assimp freetype2
        sudo pacman -S --needed openal bullet
    elif command -v yum >/dev/null 2>&1; then
        # Red Hat/CentOS/Fedora
        sudo yum groupinstall -y "Development Tools"
        sudo yum install -y cmake git
        sudo yum install -y mesa-libGL-devel glfw-devel assimp-devel freetype-devel
        sudo yum install -y openal-soft-devel bullet-devel
    else
        print_warning "Unknown package manager. Please install dependencies manually."
    fi
}

# Function to install dependencies on Windows
install_windows_deps() {
    print_status "Installing dependencies for Windows..."
    
    if command -v choco >/dev/null 2>&1; then
        choco install cmake git visualstudio2019buildtools -y
    elif command -v vcpkg >/dev/null 2>&1; then
        vcpkg install glfw3 assimp freetype openal-soft bullet3
    else
        print_warning "Please install dependencies manually or use vcpkg/chocolatey."
        print_warning "Required: Visual Studio 2019+, CMake 3.20+, Git"
    fi
}

# Function to check prerequisites
check_prerequisites() {
    print_status "Checking prerequisites..."
    
    # Check CMake
    if ! command -v cmake >/dev/null 2>&1; then
        print_error "CMake is not installed. Please install CMake 3.20 or later."
        exit 1
    fi
    
    # Check CMake version
    CMAKE_VERSION=$(cmake --version | head -n1 | cut -d' ' -f3)
    CMAKE_MAJOR=$(echo $CMAKE_VERSION | cut -d'.' -f1)
    CMAKE_MINOR=$(echo $CMAKE_VERSION | cut -d'.' -f2)
    
    if [ "$CMAKE_MAJOR" -lt 3 ] || ([ "$CMAKE_MAJOR" -eq 3 ] && [ "$CMAKE_MINOR" -lt 20 ]); then
        print_error "CMake version $CMAKE_VERSION is too old. Please install CMake 3.20 or later."
        exit 1
    fi
    
    # Check Git
    if ! command -v git >/dev/null 2>&1; then
        print_error "Git is not installed. Please install Git."
        exit 1
    fi
    
    print_success "Prerequisites check passed"
}

# Function to initialize submodules
init_submodules() {
    print_status "Initializing Git submodules..."
    
    if [ ! -f .gitmodules ]; then
        print_warning "No .gitmodules file found. Skipping submodule initialization."
        return
    fi
    
    git submodule update --init --recursive
    print_success "Git submodules initialized"
}

# Function to configure build
configure_build() {
    print_status "Configuring build..."
    
    CMAKE_ARGS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
    CMAKE_ARGS="$CMAKE_ARGS -DNIMBUS_ENABLE_VULKAN=$ENABLE_VULKAN"
    CMAKE_ARGS="$CMAKE_ARGS -DNIMBUS_BUILD_TESTS=$BUILD_TESTS"
    
    # Platform-specific configuration
    PLATFORM=$(detect_platform)
    if [ "$PLATFORM" = "windows" ]; then
        CMAKE_ARGS="$CMAKE_ARGS -DNIMBUS_ENABLE_DIRECTX12=$ENABLE_DIRECTX12"
    fi
    
    # Create build directory
    if [ "$CLEAN_BUILD" = true ] && [ -d "build" ]; then
        print_status "Cleaning build directory..."
        rm -rf build
    fi
    
    mkdir -p build
    cd build
    
    # Run CMake
    print_status "Running CMake with args: $CMAKE_ARGS"
    cmake .. $CMAKE_ARGS
    
    print_success "Build configured successfully"
}

# Function to build the project
build_project() {
    print_status "Building Nimbus Engine..."
    
    cmake --build . --config $BUILD_TYPE --parallel $JOBS
    
    print_success "Build completed successfully"
}

# Function to run tests
run_tests() {
    if [ "$BUILD_TESTS" = "ON" ]; then
        print_status "Running tests..."
        ctest --config $BUILD_TYPE --output-on-failure
        print_success "All tests passed"
    fi
}

# Function to create packages
create_packages() {
    print_status "Creating installation packages..."
    
    PLATFORM=$(detect_platform)
    if [ "$PLATFORM" = "windows" ]; then
        cpack -G NSIS
    elif [ "$PLATFORM" = "linux" ]; then
        cpack -G TGZ
        if command -v pacman >/dev/null 2>&1; then
            # Create Arch Linux package
            cpack -G TGZ
        fi
    fi
    
    print_success "Installation packages created"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_usage
            exit 0
            ;;
        -d|--debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        -t|--tests)
            BUILD_TESTS=ON
            shift
            ;;
        -v|--vulkan)
            ENABLE_VULKAN=ON
            shift
            ;;
        -x|--directx12)
            ENABLE_DIRECTX12=ON
            shift
            ;;
        -i|--install-deps)
            INSTALL_DEPS=true
            shift
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        -p|--package)
            CREATE_PACKAGE=true
            shift
            ;;
        *)
            print_error "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
done

# Main build process
main() {
    print_status "Starting Nimbus Engine build process..."
    print_status "Build configuration:"
    print_status "  Build Type: $BUILD_TYPE"
    print_status "  Vulkan: $ENABLE_VULKAN"
    print_status "  DirectX 12: $ENABLE_DIRECTX12"
    print_status "  Tests: $BUILD_TESTS"
    print_status "  Jobs: $JOBS"
    echo ""
    
    # Install dependencies if requested
    if [ "$INSTALL_DEPS" = true ]; then
        PLATFORM=$(detect_platform)
        case $PLATFORM in
            linux)
                install_linux_deps
                ;;
            windows)
                install_windows_deps
                ;;
            *)
                print_warning "Dependency installation not supported on this platform"
                ;;
        esac
    fi
    
    # Check prerequisites
    check_prerequisites
    
    # Initialize submodules
    init_submodules
    
    # Configure and build
    configure_build
    build_project
    
    # Run tests if enabled
    run_tests
    
    # Create packages if requested
    if [ "$CREATE_PACKAGE" = true ]; then
        create_packages
    fi
    
    # Success message
    echo ""
    print_success "Nimbus Engine build completed successfully!"
    print_status "Executable location: build/bin/NimbusEditor"
    print_status "To run the editor: ./build/bin/NimbusEditor"
    echo ""
    print_status "Next steps:"
    print_status "  1. Run './build/bin/NimbusEditor' to start the editor"
    print_status "  2. Create a new scene and start building your game"
    print_status "  3. Check out the documentation at docs/"
}

# Run main function
main