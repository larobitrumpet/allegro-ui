add_executable(example_1 example_1.c)
add_executable(example_2 example_2.c)
add_executable(example_3 example_3.c)

target_include_directories(example_1 PRIVATE ../include ${ALLEGRO_INCLUDEDIR})
target_include_directories(example_2 PRIVATE ../include ${ALLEGRO_INCLUDEDIR})
target_include_directories(example_3 PRIVATE ../include ${ALLEGRO_INCLUDEDIR})

target_link_libraries(example_1 PRIVATE allegro_ui lucu::lucu ${ALLEGRO_LINK_LIBRARIES})
target_link_libraries(example_2 PRIVATE allegro_ui lucu::lucu ${ALLEGRO_LINK_LIBRARIES})
target_link_libraries(example_3 PRIVATE allegro_ui lucu::lucu ${ALLEGRO_LINK_LIBRARIES})
