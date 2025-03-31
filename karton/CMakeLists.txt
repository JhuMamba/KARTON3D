add_executable (karton "karton.cpp" "karton.h" "stb_image.cpp" "include/utils/filemanager.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET karton PROPERTY CXX_STANDARD 20)
endif()

find_package(SDL2 REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

target_include_directories(karton PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/rendering
	${CMAKE_CURRENT_SOURCE_DIR}/include/utils
)

target_link_libraries(karton
    PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    glfw
    glad::glad
    glm::glm
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})