cmake_minimum_required (VERSION 3.3.2)

project (Micrium_POSIX C)

set(EXECUTABLE_NAME ucos_app)
set(CMAKE_BUILD_TYPE Release)

SET(CMAKE_C_FLAGS "-m32")

find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIB_PTHREAD REQUIRED pthread)

file(GLOB UC_APP_SRCS       ./Application/*.c)

file(GLOB UC_OSIII_SRCS     ./Software/uCOS-III/Cfg/*.c
                            ./Software/uCOS-III/Source/*.c
                            ./Software/uCOS-III/Ports/POSIX/GNU/*.c)

file(GLOB UC_CPU_SRCS       ./Software/uC-CPU/*.c
                            ./Software/uC-CPU/Posix/GNU/*.c)

file(GLOB UC_LIB_SRCS       ./Software/uC-LIB/Source/*.c)

file(GLOB UC_SHELL_SRCS     ./Software/uC-Shell/Cmd/General/*.c
                            ./Software/uC-Shell/Source/*.c)

file(GLOB UC_TERMINAL_SRCS  ./Software/uC-Terminal/Mode/VT100/*.c
                            ./Software/uC-Terminal/OS/uCOS-III/*.c
                            ./Software/uC-Terminal/Serial/Posix/GNU/*.c
                            ./Software/uC-Terminal/Source/*.c)

                                         
add_executable(${EXECUTABLE_NAME} ${UC_APP_SRCS}
                                  ${UC_OSIII_SRCS}
                                  ${UC_CPU_SRCS}
                                  ${UC_LIB_SRCS}
                                  ${UC_SHELL_SRCS}
                                  ${UC_TERMINAL_SRCS})

target_link_libraries(${EXECUTABLE_NAME} pthread curses)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_SOURCE_DIR}
                                          ${PROJECT_SOURCE_DIR}/Application/Cfg
                                          ${PROJECT_SOURCE_DIR}/Software/uC-CPU
                                          ${PROJECT_SOURCE_DIR}/Software/uC-CPU/Cfg
                                          ${PROJECT_SOURCE_DIR}/Software/uC-CPU/Posix/GNU
                                          ${PROJECT_SOURCE_DIR}/Software/uCOS-III/Cfg
                                          ${PROJECT_SOURCE_DIR}/Software/uCOS-III/Source
                                          ${PROJECT_SOURCE_DIR}/Software/uCOS-III/Ports/POSIX/GNU
                                          ${PROJECT_SOURCE_DIR}/Software/uC-LIB/Cfg
                                          ${PROJECT_SOURCE_DIR}/Software/uC-LIB/Source
                                          ${PROJECT_SOURCE_DIR}/Software/uC-Shell/Cfg
                                          ${PROJECT_SOURCE_DIR}/Software/uC-Shell/Cmd/General
                                          ${PROJECT_SOURCE_DIR}/Software/uC-Shell/Source
                                          ${PROJECT_SOURCE_DIR}/Software/uC-Terminal/Cfg
                                          ${PROJECT_SOURCE_DIR}/Software/uC-Terminal/Source)

install(TARGETS ${EXECUTABLE_NAME}
        RUNTIME DESTINATION bin)