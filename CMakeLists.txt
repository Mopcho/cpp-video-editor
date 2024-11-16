cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cpp-video-editor")

# Add source to this project's executable.
add_executable (cpp-video-editor "cpp-video-editor.cpp" "cpp-video-editor.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp-video-editor PROPERTY CPP_STANDARD 23)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Tells the compiler where the headers are
target_include_directories(${PROJECT_NAME} PRIVATE vendor/ffmpeg/include)

# Where to look for .lib or .a files when linking
target_link_directories(${PROJECT_NAME} PRIVATE vendor/ffmpeg/lib)

# Which libraries my target depends on and must be linked against
target_link_libraries(${PROJECT_NAME} PRIVATE avcodec avformat avutil)

# Add the .dll files in the same directory as the executable so it can find them
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/vendor/ffmpeg/bin
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
