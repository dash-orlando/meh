find_package(OpenGL REQUIRED)

add_executable(meh_gui meh_gui.cxx MehViewer.cxx MehViewer.hpp)
target_link_libraries(meh_gui pmp_vis igfl logic)
