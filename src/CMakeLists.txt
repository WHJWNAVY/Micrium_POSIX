cmake_minimum_required (VERSION 3.3.2)

project (Micrium_POSIX C)

set(EXECUTABLE_NAME ucos_app)
set(CMAKE_BUILD_TYPE Release)

SET(CMAKE_C_FLAGS "-m32")

find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIB_PTHREAD REQUIRED pthread)

file(GLOB UCOS_APP_SRCS  ./Application/POSIX/GNU/OS3/*.c)
file(GLOB UCOS_OS_SRCS   ./Software/uCOS-III/Source/*.c
                         ./Software/uCOS-III/Ports/POSIX/GNU/*.c)
file(GLOB UCOS_CPU_SRCS  ./Software/uC-CPU/*.c
                         ./Software/uC-CPU/Posix/GNU/*.c)
file(GLOB UCOS_LIB_SRCS  ./Software/uC-LIB/*.c)
                                         
add_executable(${EXECUTABLE_NAME} ${UCOS_APP_SRCS}
                                  ${UCOS_OS_SRCS}
                                  ${UCOS_CPU_SRCS}
                                  ${UCOS_LIB_SRCS})

target_link_libraries(${EXECUTABLE_NAME} pthread)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}
                                          ${PROJECT_SOURCE_DIR}/Application/POSIX/GNU/OS3
                                          ${PROJECT_SOURCE_DIR}/Software/uC-CPU
                                          ${PROJECT_SOURCE_DIR}/Software/uC-CPU/Posix/GNU
                                          ${PROJECT_SOURCE_DIR}/Software/uCOS-III/Ports/POSIX/GNU
                                          ${PROJECT_SOURCE_DIR}/Software/uCOS-III/Source
                                          ${PROJECT_SOURCE_DIR}/Software/uC-LIB)

install(TARGETS ${EXECUTABLE_NAME}
        RUNTIME DESTINATION bin)