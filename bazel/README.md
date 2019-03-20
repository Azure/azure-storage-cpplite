# Building with bazel

[Install Bazel](https://docs.bazel.build/versions/master/install.html)

## Building for development

```bash
bazel build //...
```

## Adding as dependency

In your WORKSPACE file or other as you manage dependencies
```
http_archive(
  name = "com_github_azure_azure_storage_cpplite",
 strip_prefix = "azure-storage-cpplite-master",
 urls = [
     "https://github.com/azure/azure-storage-cpplite/archive/master.zip",
     "https://mirror.bazel.build/github.com/azure/azure-storage-cpplite/archive/master.zip",
 ],
)
```

In your build target
```
cc_binary(
  name = "mybinary",
  srcs = [
    "main.cc"
  ],
  deps = [
    "@com_github_azure_azure_storage_cpplite//:azure_storage_cpplite",
  ],
)
```
