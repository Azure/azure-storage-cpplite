# Azure Storage Storage C++ Client Library (Lite)

## About

The Azure Storage Client Library for C++ allows you to build applications against Microsoft Azure Storage's blob service. This is a minimum dependency version that provide basic object storage. For an overview of Azure Storage, see [Introduction to Microsoft Azure Storage](http://azure.microsoft.com/en-us/documentation/articles/storage-introduction/).

## Features
The full supported Azure Storage API can be found in the following list, please be aware that only part of the functionality of some APIs are supported:
- [List Containers](https://docs.microsoft.com/en-us/rest/api/storageservices/list-containers2).
- [Create Container](https://docs.microsoft.com/en-us/rest/api/storageservices/create-container).
- [Get Container Properties](https://docs.microsoft.com/en-us/rest/api/storageservices/get-container-properties).
- [Delete Container](https://docs.microsoft.com/en-us/rest/api/storageservices/delete-container).
- [List Blobs](https://docs.microsoft.com/en-us/rest/api/storageservices/list-blobs).
- [Put Blob](https://docs.microsoft.com/en-us/rest/api/storageservices/put-blob).
- [Get Blob](https://docs.microsoft.com/en-us/rest/api/storageservices/get-blob).
- [Get Blob Properties](https://docs.microsoft.com/en-us/rest/api/storageservices/get-blob-properties).
- [Delete Blob](https://docs.microsoft.com/en-us/rest/api/storageservices/delete-blob).
- [Copy Blob](https://docs.microsoft.com/en-us/rest/api/storageservices/copy-blob).
- [Put Block](https://docs.microsoft.com/en-us/rest/api/storageservices/put-block).
- [Put Block List](https://docs.microsoft.com/en-us/rest/api/storageservices/put-block-list).
- [Get Block List](https://docs.microsoft.com/en-us/rest/api/storageservices/get-block-list).
- [Put Page](https://docs.microsoft.com/en-us/rest/api/storageservices/put-page).
- [Get Page Ranges](https://docs.microsoft.com/en-us/rest/api/storageservices/get-page-ranges).
- [Append Block](https://docs.microsoft.com/en-us/rest/api/storageservices/append-block).

## Installation

### Clone the latest code from this repository:
```
git clone https://github.com/azure/azure-storage-cpplite.git
```
### Install the dependencies, e.g. on Ubuntu:
```
sudo apt-get install libssl-dev libcurl4-openssl-dev cmake g++
```
Or, on Red Hat OS:
```
sudo yum install openssl-devel.x86_64 libcurl-devel.x86_64 cmake.x86_64 gcc-c++.x86_64
```
Please be aware that RHEL6 comes with gcc version 4.4.7, which does not meet the requirement of this SDK. In order to use this SDK, [devtoolset](http://linux.web.cern.ch/linux/devtoolset/#install) needs to be installed properly.
### Build and install azure-storage-cpplite:
```
cd azure-storage-cpplite
mkdir build.release
cd build.release
CXX=g++ cmake .. -DCMAKE_BUILD_TYPE=Release -DUSE_OPENSSL=true
sudo make install
```
### Use GNUTLS instead of OpenSSL:
Alternatively, you can use GNUTLS instead of OpenSSL. Simply install GNUTLS and remove the argument `-DUSE_OPENSSL` during build.

## Usage
Simply include the header files after installing the library, everything is good to go. For a more comprehensive sample, please see [sample](https://github.com/azure/azure-storage-cpplite/blob/master/sample/sample.cpp).
To build the sample, add `-DBUILD_SAMPLES=true` when building the repository.
```
#include "storage_credential.h"
#include "storage_account.h"
#include "blob/blob_client.h"

// Your settings
std::string account_name = "YOUR_ACCOUNT_NAME";
std::string account_key = "YOUR_ACCOUNT_KEY";
bool use_https = true;
std::string blob_endpoint = "CUSTOMIZED_BLOB_ENDPOINT";
int connection_count = 2;

// Setup the client
azure::storage_lite::shared_key_credential credential(account_name, account_key);
azure::storage_lite::storage_account(account_name, credential, use_https, blob_endpoint);
azure::storage_lite::blob_client client(storage_account, connection_count);

// Start using
auto outcome = client.create_container("YOUR_CONTAINER_NAME");
```
## License
This project is licensed under MIT.
 
## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.microsoft.com.

When you submit a pull request, a CLA-bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., label, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

When contributing to this client library, there are following ground rules:
1. All source code change should be clearly addressing issues or adding new features, and should be covered with test.
2. Coding style should match with the existing code.
3. Any contribution should not degrade performance or complex functionality.
4. Introducing new dependency should be done with much great caution. Any new dependency should introduce significant performance improvement or unblock critical user scenario.

### Build Test
Download [Catch2 single header version](https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp) and put it in the folder `.\test\catch2\`.
Add `-DBUILD_TESTS=true` when building the repository.
Please modify the [connection string here](https://github.com/katmsft/azure-storage-cpplite/blob/master/test/test_base.h#L18) to successfully run the tests. All the test uses standard Azure Storage account.
#### *Please note that in order to run test, a minimum version of g++ 5.1 is required.*

### Dependencies
- Project dependencies:
  - GNUTLS(or Openssl v7.35.0)
  - libcurl v1.0.1
  - CMake v2.8.12.2
  - g++ v4.8.2
- Dev dependency: catch2.
