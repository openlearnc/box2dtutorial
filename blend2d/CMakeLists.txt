cmake_minimum_required(VERSION 3.6.0)
project(Main)
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/include/*"
	"${PROJECT_SOURCE_DIR}/src/*"
)
LINK_DIRECTORIES(
${PROJECT_SOURCE_DIR}/static)
add_executable(Main ${SRCS})


find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
target_link_libraries(Main ${SDL2_LIBRARIES})
#target_link_libraries(Main ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(Main libblend2d.a)
target_link_libraries(Main libbox2d.a)

target_link_libraries(Main pthread)
target_link_libraries(Main rt)