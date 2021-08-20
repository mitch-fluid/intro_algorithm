cmake_minimum_required(VERSION 3.0.0)
project(intro_algorithm VERSION 0.1.0 LANGUAGES C)

# C standard
SET(C_STANDARD_REQUIRED ON)
SET(C_STANDARD 17)

# all working executable 
add_subdirectory(chapter_2)
add_subdirectory(chapter_4)
add_subdirectory(chapter_6)

include(CTest)
enable_testing()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
