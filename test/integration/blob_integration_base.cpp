#include "blob_integration_base.h"

#include "../test_constants.h"

namespace as_test {
    std::string create_random_container(const std::string& prefix, microsoft_azure::storage::blob_client& client)
    {
        //Assume prefix is less than max prefix size.
        auto container_name = prefix + get_random_string(MAX_PREFIX_SIZE - prefix.size());
        auto result = client.create_container(container_name).get();
        if (!result.success())
        {
            return create_random_container(prefix, client);
        }
        return container_name;
    }

    std::vector<std::string> create_random_containers(const std::string& prefix, microsoft_azure::storage::blob_client& client, size_t count)
    {
        std::vector<std::string> results;
        for (size_t i = 0; i < count; ++i)
        {
            results.push_back(create_random_container(prefix, client));
        }
        return results;
    }
}
