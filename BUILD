# Description:
#   azure-storage-cpplite

licenses(["notice"])

cc_library(
    name = "azure_storage_lite",
    srcs = [
      "src/logging.cpp",
      "src/base64.cpp",
      "src/constants.cpp",
      "src/hash.cpp",
      "src/utility.cpp",

      "src/tinyxml2.cpp",
      "src/tinyxml2_parser.cpp",

      "src/storage_account.cpp",
      "src/storage_credential.cpp",
      "src/storage_url.cpp",

      "src/get_blob_request_base.cpp",
      "src/put_blob_request_base.cpp",
      "src/delete_blob_request_base.cpp",
      "src/copy_blob_request_base.cpp",
      "src/create_container_request_base.cpp",
      "src/delete_container_request_base.cpp",
      "src/list_containers_request_base.cpp",
      "src/list_blobs_request_base.cpp",
      "src/get_blob_property_request_base.cpp",
      "src/get_block_list_request_base.cpp",
      "src/get_container_property_request_base.cpp",
      "src/put_block_request_base.cpp",
      "src/put_block_list_request_base.cpp",
      "src/append_block_request_base.cpp",
      "src/put_page_request_base.cpp",
      "src/get_page_ranges_request_base.cpp",

      "src/http/libcurl_http_client.cpp",

      "src/blob/blob_client.cpp",
      "src/blob/blob_client_wrapper.cpp",
      "include/storage_EXPORTS.h",

      "include/logging.h",
      "include/base64.h",
      "include/common.h",
      "include/constants.h",
      "include/executor.h",
      "include/hash.h",
      "include/retry.h",
      "include/utility.h",

      "include/tinyxml2.h",
      "include/xml_parser_base.h",
      "include/tinyxml2_parser.h",
      "include/xml_writer.h",

      "include/storage_account.h",
      "include/storage_credential.h",
      "include/storage_outcome.h",
      "include/storage_stream.h",
      "include/storage_url.h",

      "include/storage_request_base.h",
      "include/get_blob_request_base.h",
      "include/put_blob_request_base.h",
      "include/delete_blob_request_base.h",
      "include/copy_blob_request_base.h",
      "include/create_container_request_base.h",
      "include/delete_container_request_base.h",
      "include/list_containers_request_base.h",
      "include/list_blobs_request_base.h",
      "include/get_block_list_request_base.h",
      "include/put_block_request_base.h",
      "include/get_blob_property_request_base.h",
      "include/put_block_list_request_base.h",
      "include/get_container_property_request_base.h",
      "include/append_block_request_base.h",
      "include/put_page_request_base.h",
      "include/get_page_ranges_request_base.h",

      "include/http_base.h",
      "include/http/libcurl_http_client.h",

      "include/blob/blob_client.h",
      "include/blob/download_blob_request.h",
      "include/blob/create_block_blob_request.h",
      "include/blob/delete_blob_request.h",
      "include/blob/copy_blob_request.h",
      "include/blob/create_container_request.h",
      "include/blob/delete_container_request.h",
      "include/blob/list_containers_request.h",
      "include/blob/list_blobs_request.h",
      "include/blob/get_blob_property_request.h",
      "include/blob/get_container_property_request.h",
      "include/blob/get_block_list_request.h",
      "include/blob/put_block_request.h",
      "include/blob/put_block_list_request.h",
      "include/blob/append_block_request.h",
      "include/blob/put_page_request.h",
      "include/blob/get_page_ranges_request.h",
    ],
    textual_hdrs = [
        "include/constants.dat", 
    ],
    hdrs = [
        "include/blob/blob_client.h",
        "include/storage_errno.h",
    ],
    defines = [
        "USE_OPENSSL",
    ],
    includes = ["include"],
    visibility = ["//visibility:public"],
    linkopts = select({
        "@bazel_tools//src/conditions:darwin": [],
        "//conditions:default": [
            "-luuid",
        ]
    }),
    copts = [
        "-D_GLIBCXX_USE_CXX11_ABI=0",
        "-std=c++11",
    ],
    deps = [
        "@boringssl//:crypto",
        "@curl",
    ],
)

