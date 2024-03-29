cmake_minimum_required(VERSION 3.5)

project(DentalAnalyzer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CGAL_DIR "C:/dev/CGAL-5.1.1")
set(GMP_LIBRARIES "C:/dev/CGAL-5.1.1/auxiliary/gmp/lib/libgmp-10.lib")
set(GMP_INCLUDE_DIR "C:/dev/CGAL-5.1.1/auxiliary/gmp/include")
set(MPFR_LIBRARIES "C:/dev/CGAL-5.1.1/auxiliary/gmp/lib/libmpfr-4.lib")
set(MPFR_INCLUDE_DIR "C:/dev/CGAL-5.1.1/auxiliary/gmp/include")
set(Boost_INCLUDE_DIR "C:/dev/boost_1_75_0")
set(Boost_DIR "C:/dev/boost_1_75_0/stage/lib/cmake/Boost-1.75.0")
set(Boost_DEBUG OFF)
set(CGAL_Boost_USE_STATIC_LIBS ON)

set(CMAKE_BUILD_TYPE "Release")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)

# CGAL and its components
find_package( CGAL COMPONENTS  )

if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()

endif()
set(CGAL_libs CGAL::CGAL)
#
# Boost and its components
find_package(Boost REQUIRED COMPONENTS
    thread
    filesystem
    system
    program_options
    date_time
    chrono)

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")
  return()

endif()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Analyzer.cpp
        Analyzer.h
        objects.h
        utility.cpp
        utility.h
        result.h
        parameter.h
        result.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DentalAnalyzer
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(DentalAnalyzer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(DentalAnalyzer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DentalAnalyzer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia ${CGAL_libs})
