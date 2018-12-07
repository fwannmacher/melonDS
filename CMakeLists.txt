cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_STANDARD 11)

SET(PROJECT_WX melonDS)
PROJECT(${PROJECT_WX})

SET(SOURCES
	src/ARM.cpp
	src/ARMInterpreter.cpp
	src/ARMInterpreter_ALU.cpp
	src/ARMInterpreter_Branch.cpp
	src/ARMInterpreter_LoadStore.cpp
	src/Config.cpp
	src/CP15.cpp
	src/DMA.cpp
	src/GPU.cpp
	src/GPU2D.cpp
	src/GPU3D.cpp
	src/GPU3D_Soft.cpp
	src/NDS.cpp
	src/NDSCart.cpp
	src/RTC.cpp
	src/Savestate.cpp
	src/SPI.cpp
	src/SPU.cpp
	src/Wifi.cpp
	src/WifiAP.cpp
	src/wiiu/Platform.cpp
	src/wiiu/main.cpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
LINK_LIBRARIES("dl")
endif ()

add_executable(${PROJECT_WX} ${SOURCES})
target_link_libraries(${PROJECT_WX})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE EQUAL Debug)
set(CMAKE_CXX_FLAGS "-g")
endif()
if(CMAKE_BUILD_TYPE EQUAL Release)
set(CMAKE_CXX_FLAGS "-O3 -flto")
endif()

install(TARGETS ${PROJECT_WX} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
