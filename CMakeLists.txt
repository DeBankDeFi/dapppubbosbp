cmake_minimum_required(VERSION 3.11)
project(dapppubbosbp)

set(EOSIO_DEPENDENCY "1.1")
set(EOSIO_WASMSDK_DEPENDENCY "1.1")

set(CMAKE_CXX_STANDARD 14)

if(EOSIO_WASMSDK_ROOT STREQUAL "" OR NOT EOSIO_WASMSDK_ROOT)
    set(EOSIO_WASMSDK_ROOT "/usr/local/eosio.wasmsdk")
endif()

list(APPEND CMAKE_MODULE_PATH ${EOSIO_WASMSDK_ROOT}/lib/cmake)
include(EosioWasmToolchain)

add_executable(dapppubbosbp.wasm dapppubbosbp.hpp dapppubbosbp.cpp)

set(EOSIO_INSTALL_DIR /usr/local/eosio)
set(EOSIOCPP ${EOSIO_INSTALL_DIR}/bin/eosiocpp)
set(CONTRACT_ABI_FILE ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.abi)
set(CONTRACT_HPP_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.hpp)
add_custom_target(dapppubbosbp.abi ALL)
add_custom_command(
    TARGET dapppubbosbp.abi
    COMMAND ${EOSIOCPP} -g ${CONTRACT_ABI_FILE} ${CONTRACT_HPP_FILE}
)
