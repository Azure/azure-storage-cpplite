#include "test_base.h"

// tell Catch to provide a main()
#define CATCH_CONFIG_MAIN
#include "./catch2/catch.hpp"

#include <unordered_map>
#include <sstream>
#include <iostream>
#include <vector>

namespace as_test {
	std::string get_random_string(size_t size) {
        static bool initialized = false;
        if (!initialized) {
            srand(time(NULL));
            initialized = true;
        }
		auto randchar = []() -> char
		{
            const char charset[] =
				"0123456789abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(size, 0);
		std::generate_n(str.begin(), size, randchar);
		return str;
	}

	microsoft_azure::storage::blob_client& base::test_blob_client(int size) {
		static std::unordered_map<int, std::shared_ptr<microsoft_azure::storage::blob_client>> bcs;
		if (bcs[size] == NULL)
		{
            bcs[size] = std::make_shared<microsoft_azure::storage::blob_client>(microsoft_azure::storage::blob_client(init_account(standard_storage_connection_string()), size));
		}
		return *bcs[size];
	}

    const std::shared_ptr<microsoft_azure::storage::storage_account> base::init_account(const std::string& connection_string) {
		auto settings = parse_string_into_settings(connection_string);
		auto credential = std::make_shared<microsoft_azure::storage::shared_key_credential>(microsoft_azure::storage::shared_key_credential(settings["AccountName"], settings["AccountKey"]));
		bool use_https = true;
		if (settings["DefaultEndpointsProtocol"] == "http")
		{
			use_https = false;
		}
		std::string blob_endpoint;
		if (!settings["BlobEndpoint"].empty())
		{
			blob_endpoint = settings["BlobEndpoint"];
		}

		return std::make_shared<microsoft_azure::storage::storage_account>(microsoft_azure::storage::storage_account(settings["AccountName"], credential, use_https, blob_endpoint));
	}

	std::map<std::string, std::string> base::parse_string_into_settings(const std::string& connection_string)
	{
		std::map<std::string, std::string> settings;
		std::vector<std::string> splitted_string;

		// Split the connection string by ';'
		{
			std::istringstream iss(connection_string);
			std::string s;
			while (getline(iss, s, ';')) {
				splitted_string.push_back(s);
			}
		}

		for (auto iter = splitted_string.cbegin(); iter != splitted_string.cend(); ++iter)
		{
			if (!iter->empty())
			{
				auto equals = iter->find('=');

				std::string key = iter->substr(0, equals);
				if (!key.empty())
				{
					std::string value;
					if (equals != std::string::npos)
					{
						value = iter->substr(equals + 1);
					}

					settings.insert(std::make_pair(std::move(key), std::move(value)));
				}
				else
				{
					throw std::logic_error("The format of connection string cannot be recognized.");
				}
			}
		}

		return settings;
	}
}
