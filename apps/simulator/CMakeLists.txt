add_executable(device_simulator
    main.cpp
)

target_link_libraries(device_simulator
    PRIVATE
        Qt6::Core
        Qt6::Network
)