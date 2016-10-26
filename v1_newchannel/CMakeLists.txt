#----------------------------------------------------------------------------
set(name    ciae13Cmc)
set(mymain ${name}.cc )
set(myexe  ${name}    )
set(myproj  proj_${name}    )

#----------------------------------------------------------------------------
# Setup the project
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(${myproj})

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find ROOT (required package)
find_package(ROOT REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#file(GLOB libsrc ${YB_LIB_PATH}/src/*.cc)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#add_executable(${myexe} ${mymain} ${sources} ${headers})
add_executable(${myexe} ${mymain} ${sources})
target_link_libraries(${myexe} ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} -lMathCore -lMathMore)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
set(13C_SCRIPTS vis.mac fj13c_setup.par)

foreach(_script ${13C_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#install(TARGETS ${myexe} DESTINATION bin)
#message(${PROJECT_SOURCE_DIR}) 

