cmake_minimum_required(VERSION 2.8.11)
project("N-QueenApplication")


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(LOCAL_DIR   Local)
set(GENETIC_DIR Genetic)
set(ALGORITHMS_DIR  Algorithms)
set(OBJECTS_DIR     Objects)


set(LOCAL_FILES
  
)

set(OBJECTS_FILES
  ${OBJECTS_DIR}/Board.hpp
  ${OBJECTS_DIR}/Board.cpp
)


set(GENETIC_FILES
  ${GENETIC_DIR}/Population.hpp
  ${GENETIC_DIR}/Population.cpp
  ${GENETIC_DIR}/GeneticSearch.hpp
  ${GENETIC_DIR}/GeneticSearch.cpp
)


set(ALGORITHMS_FILES
  ${ALGORITHMS_DIR}/Algorithms.hpp
  ${ALGORITHMS_DIR}/Algorithms.cpp
)



set(QUEEN_APP
  ${LOCAL_FILES}
  ${GENETIC_FILES}
  ${ALGORITHMS_FILES}
  ${OBJECTS_FILES}
  Types.hpp
  Common.hpp
  Main.cpp
  StopWatch.hpp
  StopWatch.cpp
)

if (${CMAKE_CXX_COMPILER_ID})
  # Doing some stuff for organization.
  if (MSVC)
    foreach(source IN LISTS QUEEN_APP)
      get_filename_component(source_path "${source}" PATH)
      string(REPLACE "/" "\\" source_path_msvc "${source_path}")
      source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
  endif()
endif()


add_executable(NQueenApplication
  ${QUEEN_APP}
)