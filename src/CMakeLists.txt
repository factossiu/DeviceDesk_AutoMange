add_library(communication INTERFACE)

target_link_libraries(communication
    INTERFACE
        Qt6::Core
)

target_include_directories(communication
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/communication
)

target_sources(communication
    INTERFACE
        communication/message_header.h
)
