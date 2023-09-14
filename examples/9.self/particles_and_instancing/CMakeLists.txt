

file(GLOB dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)

# 构建所有samples
if(BUILD_ALL_SAMPLES)
    foreach(dir ${dirs})
        if(IS_DIRECTORY ${dir})
            add_subdirectory(${dir})
        endif()
    endforeach()
else()
    # add_subdirectory(1.1.instancing)
    # add_subdirectory(1.2.instancing_instanced_arrays)
    # add_subdirectory(1.3.instancing_instanced_arrays_mat4)

    add_subdirectory(0.billboard)
    add_subdirectory(2.1.particles)
    add_subdirectory(2.2.particles_instancing)
    add_subdirectory(2.3.particles_transform_feedback)
endif()

