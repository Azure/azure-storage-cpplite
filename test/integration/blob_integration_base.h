#pragma once

#include "../test_base.h"

namespace as_test {
    std::string create_random_container(const std::string& prefix, microsoft_azure::storage::blob_client& client);
    
    std::vector<std::string> create_random_containers(const std::string& prefix, microsoft_azure::storage::blob_client& client, size_t count);
}
