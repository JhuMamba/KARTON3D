Lazy graphics engine project that will eventually turn into a masterpiece!

Just run setup.bat file to install the dependencies and build the solution.

You can directly set the environment variable of %VCPKG_ROOT% for session then run the "setup.bat". It will find auto.

If it doesn't work, make sure that you have installed the vcpkg. If not installed then install vcpkg then set the cmake toolchain variable to your vcpkg.cmake directory.

Example: "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" is used for creating an environment then dealing with vcpkg.

Or you can just build with setting variable.

Example:
	cmake -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake ..
	cmake --build .