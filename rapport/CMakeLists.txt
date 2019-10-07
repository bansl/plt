PROJECT(master_project NONE)
cmake_minimum_required(VERSION 2.8)
SET(LATEX_OUTPUT_PATH build)
set(CMAKE_MODULE_PATH "../cmake" ${CMAKE_MODULE_PATH})
INCLUDE(../cmake/UseLATEX.cmake)

file(GLOB_RECURSE contents_files RELATIVE ${CMAKE_SOURCE_DIR} rapport/*.tex)

ADD_LATEX_DOCUMENT(
    Rapport.tex
    INPUTS structure.tex title.tex abstract.tex presentation_generale.tex
    IMAGE_DIRS images

    )
