@echo off
setlocal ENABLEEXTENSIONS

:: ===== CONFIGURATION =====
set DEFAULT_VCPKG_DIR=%CD%\vcpkg
set VCPKG_REPO=https://github.com/microsoft/vcpkg.git

:: ===== CHECK VCPKG_ROOT =====
if defined VCPKG_ROOT (
    if exist "%VCPKG_ROOT%\vcpkg.exe" (
        echo Found vcpkg at VCPKG_ROOT: %VCPKG_ROOT%
        goto cmake_run
    ) else (
        echo VCPKG_ROOT is set but vcpkg.exe not found. Ignoring...
    )
)

:: ===== CHECK DEFAULT VCPKG DIR =====
if exist "%DEFAULT_VCPKG_DIR%\vcpkg.exe" (
    set VCPKG_ROOT=%DEFAULT_VCPKG_DIR%
    echo Found vcpkg in default directory: %VCPKG_ROOT%
    goto cmake_run
)

:: ===== CLONE VCPKG =====
echo vcpkg not found. Cloning from GitHub...
git clone %VCPKG_REPO% "%DEFAULT_VCPKG_DIR%" || (
    echo ? Failed to clone vcpkg.
    pause
    exit /b 1
)

:: ===== BOOTSTRAP VCPKG =====
cd /d "%DEFAULT_VCPKG_DIR%"
echo Bootstrapping vcpkg...
call bootstrap-vcpkg.bat || (
    echo ? Failed to bootstrap vcpkg.
    pause
    exit /b 1
)

cd /d "%~dp0"
set VCPKG_ROOT=%DEFAULT_VCPKG_DIR%
echo ? vcpkg installed at %VCPKG_ROOT%

:: ===== RUN CMAKE =====
:cmake_run
set TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake

if not exist build (
    mkdir build
)

echo Running CMake with toolchain file: %TOOLCHAIN_FILE%
cmake -B build -DCMAKE_TOOLCHAIN_FILE=%TOOLCHAIN_FILE% .

echo ? Build setup complete.
pause
