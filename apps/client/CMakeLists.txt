add_executable(device_desk_client
    main.cpp
)

target_link_libraries(device_desk_client
    PRIVATE
        Qt6::Core
        Qt6::Network
        Qt6::Widgets
)

target_compile_definitions(device_desk_client
    PRIVATE
        QT_NO_KEYWORDS
)