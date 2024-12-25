set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
#Qt==========================
include_directories(${BOOST_INCLUDEDIR})
link_directories(${Boost_LIBRARY_DIRS})

add_definitions(-DTK_TXR_ALGO_DLM_LIB)

include_directories(
	${Qt5Core_INCLUDE_DIRS}
	)
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
file(GLOB_RECURSE CURRENT_SOURCES  *.cpp *.cu)
source_group("Include" FILES ${CURRENT_HEADERS}) 
source_group("Source" FILES ${CURRENT_SOURCES})

add_library(txr_algo_dlm SHARED ${CURRENT_HEADERS} ${CURRENT_SOURCES})

target_link_libraries(txr_algo_dlm PRIVATE
   Qt5::Core
   Qt5::Gui
   )

INSTALL (FILES 
    txr_algo_dlm_define.h
    txr_algo_dlm.h
    DESTINATION include)

install(TARGETS txr_algo_dlm DESTINATION 
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)