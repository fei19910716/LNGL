get_filename_component(target ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message(STATUS "starting build: ${target}")

add_library(${target} INTERFACE)

file(GLOB lib_files ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.lib)

target_link_libraries(${target} INTERFACE ${lib_files})

target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB dll_files ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.dll)
foreach(dll_file ${dll_files})
    copy_dll(${target} ${dll_file})
endforeach(dll_file ${dll_files})