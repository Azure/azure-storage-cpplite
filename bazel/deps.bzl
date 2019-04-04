load(
  "@bazel_tools//tools/build_defs/repo:git.bzl", 
  "git_repository",
  "new_git_repository",
)

load(
    "@bazel_tools//tools/build_defs/repo:http.bzl",
    "http_archive",
    "http_file",
)

def azure_storage_cpplite_dependencies():

  if not "boringssl" in native.existing_rules():
    http_archive(
        name = "boringssl",
        sha256 = "1188e29000013ed6517168600fc35a010d58c5d321846d6a6dfee74e4c788b45",
        strip_prefix = "boringssl-7f634429a04abc48e2eb041c81c5235816c96514",
        urls = [
            "https://mirror.bazel.build/github.com/google/boringssl/archive/7f634429a04abc48e2eb041c81c5235816c96514.tar.gz",
            "https://github.com/google/boringssl/archive/7f634429a04abc48e2eb041c81c5235816c96514.tar.gz",
        ],
    )

  if not "curl" in native.existing_rules():
    http_archive(
        name = "curl",
        build_file = "//bazel:curl.BUILD",
        sha256 = "e9c37986337743f37fd14fe8737f246e97aec94b39d1b71e8a5973f72a9fc4f5",
        strip_prefix = "curl-7.60.0",
        urls = [
            "https://mirror.bazel.build/curl.haxx.se/download/curl-7.60.0.tar.gz",
            "https://curl.haxx.se/download/curl-7.60.0.tar.gz",
        ],
    )
  if not "zlib" in native.existing_rules():
    http_archive(
      name = "zlib",
      build_file = "//bazel:zlib.BUILD",
      sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
      strip_prefix = "zlib-1.2.11",
      urls = [
          "https://mirror.bazel.build/zlib.net/zlib-1.2.11.tar.gz",
          "https://zlib.net/zlib-1.2.11.tar.gz",
      ],
  )

