#!/bin/bash

# Nimbus Engine Build Script
# This script helps build the Nimbus Engine on Linux systems

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

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

# Default values
BUILD_TYPE="Release"
BUILD_DIR="build"
CLEAN_BUILD=false
INSTALL=false
PACKAGE=false
JOBS=$(nproc)

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -d|--debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        -i|--install)
            INSTALL=true
            shift
            ;;
        -p|--package)
            PACKAGE=true
            shift
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        -h|--help)
            echo "Nimbus Engine Build Script"
            echo ""
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  -d, --debug     Build in Debug mode (default: Release)"
            echo "  -c, --clean     Clean build directory before building"
            echo "  -i, --install   Install after building"
            echo "  -p, --package   Create package after building"
            echo "  -j, --jobs N    Number of parallel jobs (default: auto)"
            echo "  -h, --help      Show this help message"
            exit 0
            ;;
        *)
            print_error "Unknown option: $1"
            exit 1
            ;;
    esac
done

print_status "Starting Nimbus Engine build process..."
print_status "Build type: $BUILD_TYPE"
print_status "Build directory: $BUILD_DIR"
print_status "Parallel jobs: $JOBS"

# Check if we're on a supported platform
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    print_status "Detected Linux system"
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    print_status "Detected Windows system (MSYS/Cygwin)"
else
    print_warning "Unsupported operating system: $OSTYPE"
fi

# Check for required tools
print_status "Checking for required tools..."

# Check for CMake
if ! command -v cmake &> /dev/null; then
    print_error "CMake not found. Please install CMake 3.20 or later."
    exit 1
fi

# Check for compiler
if command -v g++ &> /dev/null; then
    print_status "Found GCC compiler"
    COMPILER="gcc"
elif command -v clang++ &> /dev/null; then
    print_status "Found Clang compiler"
    COMPILER="clang"
else
    print_error "No C++ compiler found. Please install GCC or Clang."
    exit 1
fi

# Check for required libraries
print_status "Checking for required libraries..."

# Function to check if a package is installed (Ubuntu/Debian)
check_package_debian() {
    dpkg -l | grep -q "^ii  $1"
}

# Function to check if a package is installed (Arch Linux)
check_package_arch() {
    pacman -Q | grep -q "^$1 "
}

# Detect package manager
if command -v apt &> /dev/null; then
    PACKAGE_MANAGER="apt"
    check_package() { check_package_debian "$1"; }
elif command -v pacman &> /dev/null; then
    PACKAGE_MANAGER="pacman"
    check_package() { check_package_arch "$1"; }
else
    print_warning "Unknown package manager. Please ensure required libraries are installed."
    PACKAGE_MANAGER="unknown"
fi

# List of required packages
REQUIRED_PACKAGES=(
    "libgl1-mesa-dev"
    "libglfw3-dev"
    "libglm-dev"
    "libbullet-dev"
    "libopenal-dev"
    "vulkan-tools"
    "vulkan-validationlayers"
)

# Check for required packages
if [[ "$PACKAGE_MANAGER" != "unknown" ]]; then
    for package in "${REQUIRED_PACKAGES[@]}"; do
        if ! check_package "$package"; then
            print_warning "Package $package not found. You may need to install it."
        fi
    done
fi

# Create build directory
if [[ "$CLEAN_BUILD" == true ]]; then
    print_status "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

if [[ ! -d "$BUILD_DIR" ]]; then
    print_status "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Navigate to build directory
cd "$BUILD_DIR"

# Configure with CMake
print_status "Configuring with CMake..."
cmake .. \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DNIMBUS_BUILD_EDITOR=ON \
    -DNIMBUS_BUILD_EXAMPLES=ON \
    -DNIMBUS_VULKAN_ENABLED=ON \
    -DNIMBUS_OPENGL_ENABLED=ON \
    -DNIMBUS_DIRECTX_ENABLED=OFF

if [[ $? -ne 0 ]]; then
    print_error "CMake configuration failed"
    exit 1
fi

# Build the project
print_status "Building Nimbus Engine..."
make -j"$JOBS"

if [[ $? -ne 0 ]]; then
    print_error "Build failed"
    exit 1
fi

print_success "Build completed successfully!"

# Install if requested
if [[ "$INSTALL" == true ]]; then
    print_status "Installing Nimbus Engine..."
    sudo make install
    
    if [[ $? -ne 0 ]]; then
        print_error "Installation failed"
        exit 1
    fi
    
    print_success "Installation completed successfully!"
fi

# Create package if requested
if [[ "$PACKAGE" == true ]]; then
    print_status "Creating package..."
    make package
    
    if [[ $? -ne 0 ]]; then
        print_error "Package creation failed"
        exit 1
    fi
    
    print_success "Package created successfully!"
fi

print_success "Nimbus Engine build process completed!"
print_status "You can now run the engine with: ./NimbusEngine"