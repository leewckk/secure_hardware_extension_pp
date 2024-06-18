cmake_minimum_required(VERSION 3.0.0)
project(secure_hardware_extension VERSION 0.1.0 LANGUAGES C CXX)

add_executable(secure_hardware_extension 
    test_program.cpp 
    memory_update_protocol.cpp 
    memory_update_info.cpp
    memory_update_messages.cpp
    she_bytes.cpp 
    secure_flags.cpp
    crypto_common.cpp 
    she_constants.cpp)

target_link_libraries(secure_hardware_extension cryptopp)

