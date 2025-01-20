cmake_minimum_required(VERSION 3.10)

project(
	allegro_ui
	VERSION 0.1.0
	DESCRIPTION "A little UI library for use with the Allegro library"
	LANGUAGES C
)

option(ALLEGRO_STATIC "If the Allegro library being built against is a static library" OFF)
option(ALLEGRO_MONOLITH "If the Allegro library being built against is monolith" OFF)
option(WANT_EXAMPLES "Build examples" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_C_STANDARD 23)
	set(CMAKE_EXTENTIONS OFF)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

find_package(lucu REQUIRED)

find_package(PkgConfig REQUIRED)

if (${ALLEGRO_STATIC})
	if (${ALLEGRO_MONOLITH})
		pkg_check_modules(ALLEGRO REQUIRED allegro_monolith-static-5)
	else()
		pkg_check_modules(
			ALLEGRO REQUIRED
			allegro-static-5
			allegro_primitives-static-5
			allegro_font-static-5
			allegro_ttf-static-5
		)
		list(
			APPEND ALLEGRO_INCLUDEDIR
			${ALLEGRO_allegro-5_INCLUDEDIR}
			${ALLEGRO_allegro_primitives-5_INCLUDEDIR}
			${ALLEGRO_allegro_font-5_INCLUDEDIR}
			${ALLEGRO_allegro_ttf-5_INCLUDEDIR}
		)
	endif()
else()
	if (${ALLEGRO_MONOLITH})
		pkg_check_modules(ALLEGRO REQUIRED allegro_monolith-5)
	else()
		pkg_check_modules(
			ALLEGRO REQUIRED
			allegro-5
			allegro_primitives-5
			allegro_font-5
			allegro_ttf-5
		)
		list(
			APPEND ALLEGRO_INCLUDEDIR
			${ALLEGRO_allegro-5_INCLUDEDIR}
			${ALLEGRO_allegro_primitives-5_INCLUDEDIR}
			${ALLEGRO_allegro_font-5_INCLUDEDIR}
			${ALLEGRO_allegro_ttf-5_INCLUDEDIR}
		)
	endif()
endif()

add_subdirectory(src)

if (${WANT_EXAMPLES})
	add_subdirectory(examples)
endif()
