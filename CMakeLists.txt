# The minimal version of cmake that is required
cmake_minimum_required (VERSION 2.6)


# Set up the environment and variables
set (INCLUDES_FOLDER"${PROJECT_SOURCE_DIR}Anima/include/")
set (SOURCES_FOLDER "${PROJECT_SOURCE_DIR}Anima/)
set (DEPENDENCIES_FOLDER "${PROJECT_SOURCE_DIR}Dependencies/")
set (STATIC_LIBS_FOLDER "${PROJECT_BINARY_DIR}libs/static/")
set (LIBS_FOLDER "${PROJECT_BINARY_DIR}libs/")

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBS_FOLDER})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${STATIC_LIBS_FOLDER})


# The projects definitions
set (ANIMA_CORE AnimaCore)
set (ANIMA_CORE_OUTPUT AnimaCore)
set (ANIMA_CORE_FILES
        "${SOURCES_FOLDER}AnimaConsole.cpp"
        "${SOURCES_FOLDER}AnimaConsoleShell.cpp"
        "${SOURCES_FOLDER}AnimaPlugin.cpp"
        "${SOURCES_FOLDER}AnimaPluginGroup.cpp"
        "${SOURCES_FOLDER}AnimaPluginManager.cpp"
        "${SOURCES_FOLDER}AnimaPluginRoot.cpp"
        )

set (ANIMA_GRAPHICS AnimaGraphics)
set (ANIMA_GRAPHICS_OUTPUT AnimaGraphics)
set (ANIMA_GRAPHICS_FILES
        "${SOURCES_FOLDER}Graphics/AxesConvention2d.cpp"
        "${SOURCES_FOLDER}Graphics/Camera.cpp"
        "${SOURCES_FOLDER}Graphics/DeviceDriver.cpp" #TODO not in Codeblocks
        "${SOURCES_FOLDER}Graphics/DeviceManager.cpp"
#        "${SOURCES_FOLDER}Graphics/DevicePipeline.cpp" #TODO not in Codeblocks
#        "${SOURCES_FOLDER}Graphics/DeviceSubpipeline.cpp" #TODO not in Codeblocks
        "${SOURCES_FOLDER}Graphics/FontFaceFT.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/FontFactory.cpp"
        "${SOURCES_FOLDER}Graphics/FontFactoryFT.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/FontManager.cpp"
        "${SOURCES_FOLDER}Graphics/FontManagerFT.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/GeometryFactory.cpp"
        "${SOURCES_FOLDER}Graphics/ImageFactory.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/ImageLoaderPNG.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/Manager.cpp"
        "${SOURCES_FOLDER}Graphics/PrimitiveFactory.cpp"
        "${SOURCES_FOLDER}Graphics/RasterFactory.cpp"
        "${SOURCES_FOLDER}Graphics/SurfaceFactory.cpp"
        "${SOURCES_FOLDER}Graphics/SurfaceFactoryGL1_5.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/SurfaceGL1_5.cpp" #TODO not in VS2008
        "${SOURCES_FOLDER}Graphics/Viewport.cpp"
        )
set (ANIMA_GRAPHICS_LINK_LIBS "")    #TODO remove this -> only use as example
set (ANIMA_GRAPHICS_DEPENDENCIES "") #TODO remove this -> only use as example


# The options

# TODO fill this part
#      Maybe putting wizards for starting a new Anima project


# Add the folder containing all the Anima '.h's in the search path
include_directories (${INCLUDES_FOLDER})


# Create the projects
project     (${ANIMA_CORE})
add_library (${ANIMA_CORE_OUTPUT} ${ANIMA_CORE_FILES})

## Model to a project
project               (${ANIMA_GRAPHICS})
include_directories   ("${DEPENDENCIES_FOLDER}freetype-2.4.3/include")
#add_dependencies      (${ANIMA_GRAPHICS_DEPENDENCIES}) #TODO remove this -> only use as example
#target_link_libraries (${ANIMA_GRAPHICS_LINK_LIBS})    #TODO remove this -> only use as example
add_library           (${ANIMA_GRAPHICS_OUTPUT} ${ANIMA_GRAPHICS_FILES})
