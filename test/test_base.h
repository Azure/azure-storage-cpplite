#pragma once

#include "../include/blob/blob_client.h"

#include <string>

namespace as_test {

	std::string get_random_string(size_t size);

	class base {
    public:
		static microsoft_azure::storage::blob_client& test_blob_client(int size = 1);

		static const std::string& standard_storage_connection_string() {
			static std::string sscs = "DefaultEndpointsProtocol=http;EndpointSuffix=core.windows.net";
			return sscs;
		}

    private:
        static const std::shared_ptr<microsoft_azure::storage::storage_account> init_account(const std::string& connection_string);
        static std::map<std::string, std::string> parse_string_into_settings(const std::string& connection_string);
	};
}
