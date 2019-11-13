#pragma once

#include "blob/blob_client.h"

namespace azure { namespace storage_adls {
    using storage_account = azure::storage_lite::storage_account;
    using executor_context = azure::storage_lite::executor_context;

    struct list_filesystem_item
    {
        std::string name;
        // Other properties
    };

    struct list_filesystem_result
    {
        std::vector<list_filesystem_item> filesystems;
        std::string continuation_token;
    };

    struct list_path_item
    {
        std::string name;
        // Other properties
    };

    struct list_path_result
    {
        std::vector<list_path_item> paths;
        std::string continuation_token;
    };

    class adls_client final
    {
    public:
        adls_client(std::shared_ptr<storage_account> account, int max_concurrency) : m_account(account) {}

        void create_filesystem(const std::string& filesystem);
        void delete_filesystem(const std::string& filesystem);
        bool filesystem_exists(const std::string& filesystem);
        void set_filesystem_properties(const std::string& filesystem, const std::vector<std::pair<std::string, std::string>>& properties);
        std::vector<std::pair<std::string, std::string>> get_filesystem_properties(const std::string& filesystem);
        list_filesystem_result list_filesystems_segmented(const std::string& prefix, const std::string& continuation_token = std::string(), const int max_results = 5);

        void create_directory(const std::string& filesystem, const std::string& directory);
        void delete_directory(const std::string& filesystem, const std::string& directory);
        bool directory_exists(const std::string& filesystem, const std::string& directory);
        void set_directory_properties(const std::string& filesystem, const std::string& directory, const std::vector<std::pair<std::string, std::string>>& properties);
        std::vector<std::pair<std::string, std::string>> get_directory_properties(const std::string& filesystem, const std::string& directory);
        void set_directory_access_control(const std::string& filesystem, const std::string& directory, const std::string& acl);
        std::string get_directory_access_control(const std::string& filesystem, const std::string& directory);
        list_path_result list_paths_segmented(const std::string& filesystem, const std::string& directory, bool recursive = false, const std::string& continuation_token = std::string(), const int max_results = 5);

        void append_data_from_stream(const std::string& filesystem, const std::string& file, size_t offset, std::istream& istream);
        void flush_data(const std::string& filesystem, const std::string& file, size_t offset);
        void upload_file_from_stream(const std::string& filesystem, const std::string& file, std::istream& in_stream, const std::vector<std::pair<std::string, std::string>>& properties = std::vector<std::pair<std::string, std::string>>());
        void download_file_to_stream(const std::string& filesystem, const std::string& file, std::ostream& out_stream);
        void download_file_to_stream(const std::string& filesystem, const std::string& file, size_t offset, size_t size, std::ostream& out_stream);
        void delete_file(const std::string& filesystem, const std::string& file);
        bool file_exists(const std::string& filesystem, const std::string& file);
        void set_file_properties(const std::string& filesystem, const std::string& file, const std::vector<std::pair<std::string, std::string>>& properties);
        std::vector<std::pair<std::string, std::string>> get_file_properties(const std::string& filesystem, const std::string& file);
        void set_file_access_control(const std::string& filesystem, const std::string& file, const std::string& acl);
        std::string get_file_access_control(const std::string& filesystem, const std::string& file);

    private:
        std::shared_ptr<azure::storage_lite::blob_client_wrapper> m_blob_client;
        std::shared_ptr<storage_account> m_account;
        std::shared_ptr<executor_context> m_context;
    };


}}  // azure::storage_adls