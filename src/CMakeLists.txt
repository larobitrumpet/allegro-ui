include_directories(../include)
file(GLOB SRC_FILES *.c)
add_library(allegro_ui STATIC ${SRC_FILES})
