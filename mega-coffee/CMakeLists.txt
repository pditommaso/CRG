cmake_minimum_required(VERSION 2.8)

#To compile as a static self-contained binary run the following command
#cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS="-static -static-libgcc" -DCMAKE_FIND_LIBRARY_SUFFIXES=".a" ..
#otherwise
#cmake ..

# To run with Debug info
#cmake -DCMAKE_BUILD_TYPE=DEBUG ..
project (BioTools C CXX)

#set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++ -O3 -fopenmp -msse4.2 -fno-strict-aliasing -std=c++0x -Wall -pedantic -Wextra -Wunused")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -fopenmp -msse4.2 -fno-strict-aliasing -std=c++0x -Wall -pedantic -Wextra -Wunused")
set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDBINFO} -O2 -g")




#-std=c++11
add_subdirectory(doc)
#add_subdirectory(testsuit)



################################################
#         find necessary libraries             #
################################################

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

#set(BOOST_INCLUDEDIR /users/cn/mhatzou/src/lib/stupidPrefix/include/)
#set(BOOST_LIBRARYDIR /users/cn/mhatzou/src/lib/stupidPrefix/lib)

FIND_PACKAGE(Boost COMPONENTS system filesystem program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS( "-DHAS_BOOST" )

FIND_PACKAGE(OpenMP)
 find_package(OpenMP)
 if (OPENMP_FOUND)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
 endif (OPENMP_FOUND)


IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
  FIND_PACKAGE(Git)
  IF(GIT_FOUND)
    EXECUTE_PROCESS(
      COMMAND ${GIT_EXECUTABLE} describe --tags --always
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "MY_BUILD_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    MESSAGE( STATUS "Git version: ${MY_BUILD_VERSION}" )
  ELSE(GIT_FOUND)
    SET(MY_BUILD_VERSION 0)
  ENDIF(GIT_FOUND)
ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Version.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/Version.hpp @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})


# 
# ################################################
# #                    MSAA                      #
# ################################################
# 
 SET(msaa_src ./src/programs/msaa.cpp ./src/lib/utils/filesystem.cpp ./src/lib/utils/utils.cpp ./src/lib/utils/graph_algorithms.cpp ./src/lib/utils/ScoringMatrix.cpp ./src/lib/Sequence/Sequence.cpp ./src/lib/Sequence/SequenceSet.cpp ./src/lib/Sequence/Alignment.cpp ./src/lib/Sequence/SequenceSet_io.cpp ./src/lib/Sequence/Alignment_io.cpp ./src/lib/Sequence/aln_analysis.cpp)
 SET(msaa_exe msaa)
 ADD_EXECUTABLE(${msaa_exe} ${msaa_src} )
 target_link_libraries(${msaa_exe} 
   	${Boost_LIBRARIES}
  )
# 
# ################################################
# #                    aln_trimmer               #
# ################################################
# 
 SET(aln_trimmer_src ./src/programs/aln_trimmer.cpp ./src/lib/utils/filesystem.cpp ./src/lib/utils/utils.cpp ./src/lib/utils/graph_algorithms.cpp ./src/lib/utils/ScoringMatrix.cpp ./src/lib/Sequence/Sequence.cpp ./src/lib/Sequence/SequenceSet.cpp ./src/lib/Sequence/Alignment.cpp ./src/lib/Sequence/SequenceSet_io.cpp ./src/lib/Sequence/Alignment_io.cpp ./src/lib/Sequence/aln_analysis.cpp)
 SET(aln_trimmer_exe aln_trimmer)
 ADD_EXECUTABLE(${aln_trimmer_exe} ${aln_trimmer_src})
 target_link_libraries(${aln_trimmer_exe}
 	${Boost_LIBRARIES}
 )
# 
# 
# 
# 
# ################################################
# #                  setAnalyzer                 #
# ################################################

# SET(setanalyser_src ./src/programs/setAnalyser.cpp ./src/lib/utils/filesystem.cpp ./src/lib/utils/utils.cpp ./src/lib/Sequence/Sequence.cpp ./src/lib/Sequence/SequenceSet.cpp ./src/lib/Sequence/Alignment.cpp ./src/lib/Sequence/SequenceSet_io.cpp ./src/lib/Sequence/Alignment_io.cpp ./src/lib/Sequence/aln_analysis.cpp)
# SET(setanalyser_exe setAnalyser)
# ADD_EXECUTABLE(${setanalyser_exe} ${setanalyser_src})
# target_link_libraries(${setanalyser_exe} 
# 	${Boost_LIBRARIES}
# )
# 
# 
# 
# ################################################
# #                  maskHelper                 #
# ################################################
# 
# SET(maskHelper_src ./src/programs/maskHelper.cpp ./src/lib/utils/ ./src/lib/utils/filesystem.cpp ./src/lib/Sequence/Sequence.cpp ./src/lib/Sequence/SequenceSet.cpp ./src/lib/utils/utils.cpp ./src/lib/Sequence/SequenceSet_io.cpp )
# SET(maskHelper_exe maskHelper)
# ADD_EXECUTABLE(${maskHelper_exe} ${maskHelper_src})
# target_link_libraries(${maskHelper_exe} 
# 	${Boost_LIBRARIES}
# )
# 


################################################
#                    mega                      #
################################################

SET(mega_coffee_src ./src/programs/tea/tea.cpp
            ./src/lib/utils/utils.cpp ./src/lib/utils/Debug.cpp ./src/lib/utils/fast_math.cpp ./src/lib/utils/Library.cpp ./src/lib/utils/Matrix.cpp ./src/lib/utils/ScoringMatrix.cpp
            ./src/lib/TreeClustering/kmeans.cpp ./src/lib/TreeClustering/clustering.cpp ./src/lib/TreeClustering/Vector.cpp ./src/lib/TreeClustering/Tree.cpp
            ./src/lib/Sequence/Sequence.cpp ./src/lib/Sequence/SequenceSet.cpp ./src/lib/Sequence/SequenceSet_io.cpp ./src/lib/Sequence/aln_analysis.cpp ./src/lib/Sequence/Alignment.cpp ./src/lib/Sequence/Alignment_io.cpp  ./src/lib/Sequence/gotoh.cpp ./src/lib/Sequence/other_seq.cpp
            ./src/lib/Sequence/smith_waterman_sse2.cpp
            ./src/lib/HMM/HMM.cpp ./src/lib/HMM/fw_bw.cpp
            ./src/lib/StarClustering/StarClust.cpp
            ./src/lib/MSA/ProfileMSA.cpp ./src/lib/MSA/SequenceMSA.cpp ./src/lib/MSA/TreeMSA.cpp ./src/lib/MSA/LargeScaleMSA.cpp
            ./src/programs/aln_trimmer.cpp ./src/lib/utils/filesystem.cpp ./src/lib/utils/graph_algorithms.cpp ./src/lib/Sequence/aln_analysis.cpp
            #./src/lib/HHalign/src/hhalign_app.cpp
            )
SET(mega_coffee_exe mega_coffee)
#ADD_CUSTOM_TARGET(
#libhhalign.so.0.1
 #  COMMAND make
  # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/HHalign/src/
#)

ADD_EXECUTABLE(${mega_coffee_exe} ${mega_coffee_src} src/programs/aln_trimmer.h)
set_property(TARGET ${mega_coffee_exe} PROPERTY LINK_SEARCH_START_STATIC 1)
target_link_libraries(${mega_coffee_exe}
	${Boost_LIBRARIES}
)

include(ExternalProject)
ExternalProject_Add(hhalign
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/hhalign-clustal
   CONFIGURE_COMMAND ""
   BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/hhalign-clustal && ./configure CFLAGS=-g CXXFLAGS=-g LDFLAGS=-static LDFLAGS=-static-libgcc LDFLAGS=-static-libstdc++ --prefix=${CMAKE_CURRENT_SOURCE_DIR}/src/lib/hhalign-clustal/bin > /dev/null && make > /dev/null
   INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/hhalign-clustal && make install > /dev/null
)


add_dependencies(mega_coffee hhalign)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/hhalign-clustal/src/)
target_link_libraries(${mega_coffee_exe}
	${CMAKE_CURRENT_SOURCE_DIR}/src/lib/hhalign-clustal/src/.libs/libclustalo.a
)

#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/HHalign/src/)
#link_directories( ${tea_exe}
#  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/HHalign/src/
#)
#target_link_libraries(${tea_exe}
#	${CMAKE_CURRENT_SOURCE_DIR}/src/lib/HHalign/src/libhhalign.a
#)
#target_link_libraries(${tea_exe}
#	${CMAKE_CURRENT_SOURCE_DIR}/src/lib/HHalign/lib/ffindex/src/libffindex.a
#)
#add_dependencies(${tea_exe}  libhhalign.so.0)


install(TARGETS ${msaa_exe} ${maskHelper_exe} ${setanalyser_exe} ${mega_coffee_exe} DESTINATION .)




################################################
#                Alignment library             #
################################################

FILE (GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/*.cpp)

SET(aln_lib_src ${SOURCE_FILES})
add_library (biotools_aln ${aln_lib_src})
 

if (WITH_UNIT_TEST)
	add_subdirectory (tests)
	enable_testing ()
	add_test (NAME ClusteringTest COMMAND clustering_test)
	add_test (NAME HMMTest COMMAND HMM_test)
	add_test (NAME SequenceTest COMMAND sequence_test)
endif ()



