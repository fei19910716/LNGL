

file(GLOB dirs ${CMAKE_CURRENT_SOURCE_DIR}/*)

# 构建所有samples
if(BUILD_ALL_SAMPLES)
    foreach(dir ${dirs})
        if(IS_DIRECTORY ${dir})
            add_subdirectory(${dir})
        endif()
    endforeach()
else()
    add_subdirectory(1.1.lighting)
    add_subdirectory(1.2.lighting_textured)
    add_subdirectory(2.1.1.ibl_irradiance_conversion)
    add_subdirectory(2.1.2.ibl_irradiance)
    add_subdirectory(2.2.1.ibl_specular)
    add_subdirectory(2.2.2.ibl_specular_textured)
endif()

