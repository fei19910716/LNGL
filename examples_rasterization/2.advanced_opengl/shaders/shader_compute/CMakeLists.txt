

file(GLOB dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)

# 构建所有samples
if(BUILD_ALL_SAMPLES)
    foreach(dir ${dirs})
        if(IS_DIRECTORY ${dir})
            add_subdirectory(${dir})
        endif()
    endforeach()
else()
    add_subdirectory(compute_image1d)
    add_subdirectory(compute_image2d)
    add_subdirectory(compute_ssbo)
    add_subdirectory(compute_gaussian_blur)
endif()

