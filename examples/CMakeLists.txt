include_directories("${CMAKE_SOURCE_DIR}/src")

if (WIN32)
        add_definitions(-DNOGDI)
endif (WIN32)

add_executable(explicit_messaging ExplicitMessagingExample.cpp)
target_link_libraries(explicit_messaging EIPScanner)

add_executable(file_object_example FileObjectExample.cpp)
target_link_libraries(file_object_example EIPScanner)

add_executable(identity_object_example IdentityObjectExample.cpp)
target_link_libraries(identity_object_example EIPScanner)

add_executable(implicit_messaging ImplicitMessagingExample.cpp)
target_link_libraries(implicit_messaging EIPScanner)

add_executable(parameter_object_example ParameterObjectExample.cpp)
target_link_libraries(parameter_object_example EIPScanner)

add_executable(discovery_example DiscoveryManagerExample.cpp)
target_link_libraries(discovery_example EIPScanner)
if (WIN32)
        target_link_libraries(discovery_example ws2_32)
endif (WIN32)