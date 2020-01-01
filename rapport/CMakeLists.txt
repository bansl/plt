PROJECT(master_project NONE)
cmake_minimum_required(VERSION 2.8)
SET(LATEX_OUTPUT_PATH "")
set(CMAKE_MODULE_PATH "../cmake" ${CMAKE_MODULE_PATH})
INCLUDE(../cmake/UseLATEX.cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE contents_files RELATIVE ${CMAKE_SOURCE_DIR} rapport/*.tex)

ADD_LATEX_DOCUMENT(
    Rapport.tex
    INPUTS structure.tex title.tex abstract.tex presentation_generale.tex description_et_conception_des_etats.tex description_et_conception_du_rendu.tex engine.tex ai.tex modularisation.tex
    IMAGE_DIRS images

    )

