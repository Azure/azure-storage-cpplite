cmake_minimum_required(VERSION 2.8)

project(azurestoragelite)

set(CMAKE_CXX_STANDARD 11)
if(APPLE)
  set(CMAKE_FIND_FRAMEWORK LAST)
endif()

# Add custom cmake modules to CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}" )

option(BUILD_TESTS "Build test codes" OFF)
option(BUILD_SAMPLES "Build sample codes" OFF)

set(AZURE_STORAGE_LITE_HEADER
  include/storage_EXPORTS.h

  include/base64.h
  include/common.h
  include/constants.h
  include/constants.dat
  include/executor.h
  include/hash.h
  include/retry.h
  include/utility.h

  include/tinyxml2.h
  include/xml_parser_base.h
  include/tinyxml2_parser.h
  include/xml_writer.h

  include/storage_account.h
  include/storage_credential.h
  include/storage_outcome.h
  include/storage_stream.h
  include/storage_url.h
  include/storage_errno.h

  include/storage_request_base.h
  include/get_blob_request_base.h
  include/put_blob_request_base.h
  include/delete_blob_request_base.h
  include/copy_blob_request_base.h
  include/create_container_request_base.h
  include/delete_container_request_base.h
  include/list_containers_request_base.h
  include/list_blobs_request_base.h
  include/get_block_list_request_base.h
  include/put_block_request_base.h
  include/get_blob_property_request_base.h
  include/get_container_property_request_base.h
  include/put_block_list_request_base.h
  include/get_container_property_request_base.h
  include/append_block_request_base.h
  include/put_page_request_base.h
  include/get_page_ranges_request_base.h

  include/http_base.h
  include/http/libcurl_http_client.h

  include/blob/blob_client.h
  include/blob/download_blob_request.h
  include/blob/create_block_blob_request.h
  include/blob/delete_blob_request.h
  include/blob/copy_blob_request.h
  include/blob/create_container_request.h
  include/blob/delete_container_request.h
  include/blob/list_containers_request.h
  include/blob/list_blobs_request.h
  include/blob/get_blob_property_request.h
  include/blob/get_container_property_request.h
  include/blob/get_block_list_request.h
  include/blob/put_block_request.h
  include/blob/put_block_list_request.h
  include/blob/append_block_request.h
  include/blob/put_page_request.h
  include/blob/get_page_ranges_request.h
)

set(AZURE_STORAGE_LITE_SOURCE
  src/base64.cpp
  src/constants.cpp
  src/hash.cpp
  src/utility.cpp

  src/tinyxml2.cpp
  src/tinyxml2_parser.cpp

  src/storage_account.cpp
  src/storage_credential.cpp
  src/storage_url.cpp

  src/get_blob_request_base.cpp
  src/put_blob_request_base.cpp
  src/delete_blob_request_base.cpp
  src/copy_blob_request_base.cpp
  src/create_container_request_base.cpp
  src/delete_container_request_base.cpp
  src/list_containers_request_base.cpp
  src/list_blobs_request_base.cpp
  src/get_blob_property_request_base.cpp
  src/get_block_list_request_base.cpp
  src/get_container_property_request_base.cpp
  src/put_block_request_base.cpp
  src/put_block_list_request_base.cpp
  src/append_block_request_base.cpp
  src/put_page_request_base.cpp
  src/get_page_ranges_request_base.cpp

  src/http/libcurl_http_client.cpp

  src/blob/blob_client.cpp
  src/blob/blob_client_wrapper.cpp
)

find_package(CURL REQUIRED)

option(USE_OPENSSL "Use OpenSSL instead of GnuTLS" OFF)

find_package(Threads REQUIRED)

if(UNIX AND NOT APPLE)
  pkg_search_module(UUID REQUIRED uuid)
else()
  find_package(UUID REQUIRED)
endif()

if (NOT ${USE_OPENSSL})
  find_package(GnuTLS REQUIRED)
  set(EXTRA_INCLUDE ${GNUTLS_INCLUDE_DIR})
  set(EXTRA_LIBRARIES ${GNUTLS_LIBRARIES})
else()
  if (APPLE AND NOT OPENSSL_ROOT_DIR)
    # Prefer a homebrew version of OpenSSL over the one in /usr/lib
    file(GLOB OPENSSL_BREW_ROOT /usr/local/Cellar/openssl/*)
    # check if there is a newer version available installed via brew
    if (OPENSSL_BREW_ROOT)
      # Prefer the latest (make the latest one first)
      list(REVERSE OPENSSL_BREW_ROOT)
      set(OPENSSL_ROOT_DIR ${OPENSSL_BREW_ROOT})
      unset(OPENSSL_BREW_ROOT)
    endif()
  endif()
  find_package(OpenSSL REQUIRED)
  add_definitions(-DUSE_OPENSSL)
endif()

set(WARNING "-Wall -Wextra -Werror -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_THREAD_LIBS_INIT} ${WARNING} ${CMAKE_CXX_FLAGS}")
include_directories(${PROJECT_SOURCE_DIR}/include ${CURL_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${UUID_INCLUDE_DIR} ${EXTRA_INCLUDE})

set(CMAKE_MACOSX_RPATH ON)
add_library(azure-storage-lite SHARED ${AZURE_STORAGE_LITE_HEADER} ${AZURE_STORAGE_LITE_SOURCE})

target_link_libraries(azure-storage-lite ${CURL_LIBRARIES} ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY} ${UUID_LIBRARIES} ${EXTRA_LIBRARIES})

if(BUILD_TESTS)
  add_subdirectory(test)
endif()

if(BUILD_SAMPLES)
  add_subdirectory(sample)
endif()

if (WIN32 OR UNIX)
  file(GLOB BLOB_HEADERS includes/blob/*.h)
  install(FILES ${BLOB_HEADERS} DESTINATION include/blob)

  file(GLOB HTTP_HEADERS includes/http/*.h)
  install(FILES ${HTTP_HEADERS} DESTINATION include/http)

  file(GLOB TODO_HEADERS includes/todo/*.h)
  install(FILES ${HTTP_HEADERS} DESTINATION todo/http)

  file(GLOB GENERAL_HEADERS includes/*.h)
  install(FILES ${GENERAL_HEADERS} DESTINATION include)

  file(GLOB GENERAL_DATA includes/*.dat)
  install(FILES ${GENERAL_DATA} DESTINATION include)
endif()

# Reconfigure final output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binaries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Binaries)

# Set version numbers centralized
set (AZURE_STORAGE_LITE_VERSION_MAJOR 0)
set (AZURE_STORAGE_LITE_VERSION_MINOR 1)
set (AZURE_STORAGE_LITE_VERSION_REVISION 0)

# Set output directories.
if(NOT DEFINED CMAKE_INSTALL_BINDIR)
  set(CMAKE_INSTALL_BINDIR bin)
endif()

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR lib)
endif()
