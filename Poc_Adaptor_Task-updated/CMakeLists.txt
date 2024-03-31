# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly

cmake_minimum_required(VERSION 3.16)

# Check if platform flag is set

if(DEFINED PLATFORM)

    # Set build directory based on platform

    if(${PLATFORM} STREQUAL "ESP32")

        include($ENV{IDF_PATH}/tools/cmake/project.cmake)

         project(esp32_test)

    elseif(${PLATFORM} STREQUAL "LINUX")

        # Add subdirectory for Linux platform build
        add_subdirectory(main/Platform_Linux)

    endif()

else()

    message(FATAL_ERROR "Please specify PLATFORM flag: -DPLATFORM=ESP32 or -DPLATFORM=LINUX")

endif()

