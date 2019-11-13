cmake_minimum_required(VERSION 2.8)

project(azure_storage_adls)

set(AZURE_STORAGE_ADLS_SOURCES
  include/adls_client.h
  src/adls_client.cpp
)

add_library(azure_storage_adls ${AZURE_STORAGE_ADLS_SOURCES})

target_link_libraries(azure_storage_adls azure-storage-lite)