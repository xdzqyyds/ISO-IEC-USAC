cmake_minimum_required(VERSION 3.16.3)
#---------------------------------------------------------------------------------------------------
project(
    uniDrcBitstreamDecoder
    VERSION 1.0.0
    )

#---------------------------------------------------------------------------------------------------
add_library(
    ${PROJECT_NAME}
    STATIC
        include/uniDrcBitstreamDecoder_api.h
        src/uniDrcBitstreamDecoder.c
        src/uniDrcBitstreamDecoder.h
        src/uniDrcParser.c
        src/uniDrcParser.h
    )

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
    )

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        uniDrcCommon
        uniDrcCommon_tables
        readonlybitbuf
    PRIVATE
        $<$<PLATFORM_ID:Linux,Darwin>:m>
    )