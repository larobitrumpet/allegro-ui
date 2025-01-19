file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB SRC_FILES *.c)

add_library(allegro_ui STATIC ${SRC_FILES} ${HEADER_LIST})
target_include_directories(
	allegro_ui PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
target_include_directories(
	allegro_ui PRIVATE
	${ALLEGRO_INCLUDEDIR}
)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST}
)

target_sources(
	allegro_ui PUBLIC
	FILE_SET HEADERS
	BASE_DIRS ${PROJECT_SOURCE_DIR}/include
	FILES ${HEADER_LIST}
)

install(
	TARGETS allegro_ui
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	INCLUDES DESTINATION include
	FILE_SET HEADERS DESTINATION include
)
