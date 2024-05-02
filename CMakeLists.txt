cmake_minimum_required(VERSION 3.10)

project(allegro_ui)

option(ALLEGRO_STATIC "If the Allegro library being built against is a static library" OFF)
option(ALLEGRO_MONOLITH "If the Allegro library being built against is monolith" OFF)
option(WANT_EXAMPLES "Build examples" OFF)

add_subdirectory(src)
if (${WANT_EXAMPLES})
	add_subdirectory(examples)
endif()
