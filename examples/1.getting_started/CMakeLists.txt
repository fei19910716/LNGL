

file(GLOB dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)

# 构建所有samples
if(BUILD_ALL_SAMPLES)
    foreach(dir ${dirs})
        if(IS_DIRECTORY ${dir})
            add_subdirectory(${dir})
        endif()
    endforeach()
else()
    # add_subdirectory(1.1.hello_window)
    # add_subdirectory(1.2.hello_window_clear)
    add_subdirectory(2.1.hello_triangle)
    # add_subdirectory(2.2.hello_triangle_indexed)
    # add_subdirectory(2.3.hello_triangle_exercise1)
    # add_subdirectory(2.4.hello_triangle_exercise2)
    # add_subdirectory(2.5.hello_triangle_exercise3)
    # add_subdirectory(3.1.shaders_uniform)

    # add_subdirectory(3.2.shaders_interpolation)
    # add_subdirectory(3.3.shaders_class)
    # add_subdirectory(4.1.textures)
    # add_subdirectory(4.2.textures_combined)
    # add_subdirectory(4.4.textures_exercise2)
    # add_subdirectory(4.5.textures_exercise3)
    # add_subdirectory(4.6.textures_exercise4)

    # add_subdirectory(7.1.camera_circle)
endif()

