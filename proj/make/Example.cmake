add_executable("Example"
  "../../Example/Example.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Example" PROPERTIES
    OUTPUT_NAME "Example_Debug"
    ARCHIVE_OUTPUT_DIRECTORY "/home/ziyad/Documents/TinyShaders/bin/Debug"
    LIBRARY_OUTPUT_DIRECTORY "/home/ziyad/Documents/TinyShaders/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY "/home/ziyad/Documents/TinyShaders/bin/Debug"
  )
endif()
target_include_directories("Example" PRIVATE
  $<$<CONFIG:Debug>:/home/ziyad/Documents/TinyShaders/Include>
  $<$<CONFIG:Debug>:/home/ziyad/Documents/TinyShaders/Example>
  $<$<CONFIG:Debug>:/home/ziyad/Documents/TinyShaders/Example/Include>
)
target_compile_definitions("Example" PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
)
target_link_directories("Example" PRIVATE
)
target_link_libraries("Example"
  $<$<CONFIG:Debug>:GL>
  $<$<CONFIG:Debug>:X11>
  $<$<CONFIG:Debug>:Xrandr>
  $<$<CONFIG:Debug>:Xinerama>
)
target_compile_options("Example" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O0>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Example" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Example" PROPERTIES
    OUTPUT_NAME "Example"
    ARCHIVE_OUTPUT_DIRECTORY "/home/ziyad/Documents/TinyShaders/bin/Release"
    LIBRARY_OUTPUT_DIRECTORY "/home/ziyad/Documents/TinyShaders/bin/Release"
    RUNTIME_OUTPUT_DIRECTORY "/home/ziyad/Documents/TinyShaders/bin/Release"
  )
endif()
target_include_directories("Example" PRIVATE
  $<$<CONFIG:Release>:/home/ziyad/Documents/TinyShaders/Include>
  $<$<CONFIG:Release>:/home/ziyad/Documents/TinyShaders/Example>
  $<$<CONFIG:Release>:/home/ziyad/Documents/TinyShaders/Example/Include>
)
target_compile_definitions("Example" PRIVATE
)
target_link_directories("Example" PRIVATE
)
target_link_libraries("Example"
  $<$<CONFIG:Release>:GL>
  $<$<CONFIG:Release>:X11>
  $<$<CONFIG:Release>:Xrandr>
  $<$<CONFIG:Release>:Xinerama>
)
target_compile_options("Example" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-std=c++20>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Example" PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()