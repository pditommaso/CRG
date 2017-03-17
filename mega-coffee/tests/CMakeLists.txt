
# boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)

FIND_PACKAGE(Boost 1.53 COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
ADD_DEFINITIONS( "-DHAS_BOOST" )



SET(clustering_tests_src ./clustering/clustering_test.cpp ../src/lib/Clustering/Tree.cpp )
SET(clustering_tests_exe clustering_test)
ADD_EXECUTABLE(${clustering_tests_exe} ${clustering_tests_src})
target_link_libraries(${clustering_tests_exe} 
	${Boost_LIBRARIES} biotools_aln
)
	
SET(sequence_tests_src ./Sequence/sequence_test.cpp)
SET(sequence_tests_exe sequence_test)
ADD_EXECUTABLE(${sequence_tests_exe} ${sequence_tests_src})
target_link_libraries(${sequence_tests_exe} 
	${Boost_LIBRARIES} biotools_aln
)

SET(HMM_tests_src ./HMM/fwbw_test.cpp)
SET(HMM_tests_exe HMM_test)
ADD_EXECUTABLE(${HMM_tests_exe} ${HMM_tests_src})
target_link_libraries(${HMM_tests_exe} 
	${Boost_LIBRARIES} biotools_aln

)