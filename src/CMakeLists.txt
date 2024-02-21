if (USE_GLOB)
    file(GLOB_RECURSE SOURCES *.h *.cpp)
    add_library(${MODULE_NAME} STATIC ${SOURCES})
else ()
    set(HEADERS
    	tri-diag-matrix.h
        dense-matrix.h
        csr-matrix.h
        vector-operations.h
    )

    set(SOURCES)

    source_group("Header Files" FILES ${HEADERS})
    source_group("Source Files" FILES ${SOURCES})

    add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
