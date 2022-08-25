cmake_minimum_required(VERSION 3.10)
project(arithmetic-coding)

set(CMAKE_C_STANDARD 11)


include_directories(
    ${CMAKE_SOURCE_DIR}/codings/
    ${CMAKE_SOURCE_DIR}/src/helpers/
)

add_executable(detcap
   src/detcap/main.c
   src/helpers/helpers.c
)
target_link_libraries(detcap pthread)


link_directories(${CMAKE_SOURCE_DIR}/src/performance)
add_executable(genrand
   src/performance/genrand.c
)
target_link_libraries(genrand pcg_random)


include_directories(${CMAKE_SOURCE_DIR}/rtPerfLog/include/)
link_directories(${CMAKE_SOURCE_DIR}/rtPerfLog/build)

add_executable(performance-an32
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-an32 PRIVATE AN32=1)
target_link_libraries(performance-an32 rtperflog)

add_executable(performance-an64
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-an64 PRIVATE AN64=1)
target_link_libraries(performance-an64 rtperflog)


add_executable(performance-twocmp32
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-twocmp32 PRIVATE TWOCMP32=1)
target_link_libraries(performance-twocmp32 rtperflog)

add_executable(performance-twocmp64
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-twocmp64 PRIVATE TWOCMP64=1)
target_link_libraries(performance-twocmp64 rtperflog)

add_executable(performance-onecmp32
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-onecmp32 PRIVATE ONECMP32=1)
target_link_libraries(performance-onecmp32 rtperflog)

add_executable(performance-onecmp64
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-onecmp64 PRIVATE ONECMP64=1)
target_link_libraries(performance-onecmp64 rtperflog)

add_executable(performance-none64
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-none64 PRIVATE NONE64=1)
target_link_libraries(performance-none64 rtperflog)

add_executable(performance-none32
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-none32 PRIVATE NONE32=1)
target_link_libraries(performance-none32 rtperflog)

add_executable(performance-res32
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-res32 PRIVATE RES32=1)
target_link_libraries(performance-res32 rtperflog)

add_executable(performance-res64
   src/performance/main.c
   src/helpers/helpers.c
)
target_compile_definitions(performance-res64 PRIVATE RES64=1)
target_link_libraries(performance-res64 rtperflog)


add_executable(val-mul
   mul_validation/main.c
   mul_validation/mul100.c
   src/helpers/helpers.c
)
target_link_libraries(val-mul rtperflog)

add_executable(val-mul-enc
   mul_validation/main_enc.c
   mul_validation/mul100.c
   mul_validation/mul100_enc.c
   src/helpers/helpers.c
)
target_link_libraries(val-mul-enc rtperflog)
if( VAL_TIME )
target_compile_definitions(val-mul PUBLIC DO_TIME_MEAS)
target_compile_definitions(val-mul-enc PUBLIC DO_TIME_MEAS)
endif()

add_executable(gentable
   mul_validation/gentable.c
   src/helpers/helpers.c
)