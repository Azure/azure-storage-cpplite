cmake_minimum_required(VERSION 2.8)

project(azure_storage_test)

set(AZURE_STORAGE_TEST_HEADER
  catch2/catch.hpp
  test_constants.h
  test_base.h
  integration/blob_integration_base.h
)

set(AZURE_STORAGE_TEST_SOURCE
  test_constants.cpp
  test_base.cpp
  integration/blob_integration_base.cpp

  integration/blob_client_integration_test.cpp
)


add_executable(azure-storage-test ${AZURE_STORAGE_TEST_SOURCE})
target_include_directories(azure-storage-test INTERFACE ${AZURE_STORAGE_TEST_HEADER})

target_link_libraries(azure-storage-test azure-storage)