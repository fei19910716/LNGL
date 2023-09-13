

file(GLOB dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)

# 构建所有samples
if(BUILD_ALL_SAMPLES)
    foreach(dir ${dirs})
        if(IS_DIRECTORY ${dir})
            add_subdirectory(${dir})
        endif()
    endforeach()
else()
    add_subdirectory(1.1.hello_window)
    add_subdirectory(1.2.hello_window_clear)
    add_subdirectory(2.1.hello_triangle)
    add_subdirectory(2.2.hello_triangle_indexed)
    add_subdirectory(3.1.shaders_uniform)
    add_subdirectory(3.2.vertex_attribute)



    add_subdirectory(6.1.mvp)
    add_subdirectory(6.2.mvp_depth)
    add_subdirectory(7.1.camera_lookat)
    add_subdirectory(7.2.camera_keyboard)
    add_subdirectory(7.3.camera_mouse)
endif()

