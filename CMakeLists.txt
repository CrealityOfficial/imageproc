set(SRCS imageproc.cpp
		 include/imageproc/imageproc.h
		 )

if(NOT WIN32)
	add_compile_options(-fPIC)
	add_definitions(-DHAVE_PTHREADS)
endif()

set(LIBS )

if(TARGET  OpenMP::OpenMP_CXX)
	message(STATUS "build imageproc use openmp")
	list(APPEND LIBS OpenMP::OpenMP_CXX)
endif()

__add_real_target(imageproc lib SOURCE ${SRCS}
                            LIB ${LIBS}
                            INC ${CMAKE_CURRENT_SOURCE_DIR}/include
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CC_INSTALL_IMAGEPROC)
	__install_directory_specif(${CMAKE_CURRENT_SOURCE_DIR}/include/ imageproc)
endif()
