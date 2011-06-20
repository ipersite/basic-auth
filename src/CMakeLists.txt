INCLUDE(CheckIncludeFiles)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/config.h)
ADD_EXECUTABLE(basic-auth utils.cpp logger.cpp authenticator.cpp configurator.cpp main.cpp)
INSTALL(TARGETS basic-auth RUNTIME DESTINATION bin)
