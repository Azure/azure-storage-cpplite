#pragma once

#ifdef _WIN32
#ifdef azure_storage_adls_EXPORTS
#define AZURE_STORAGE_ADLS_API __declspec(dllexport)
#else
#define AZURE_STORAGE_ADLS_API __declspec(dllimport)
#endif
#else /* ifdef _WIN32 */
#define AZURE_STORAGE_ADLS_API
#endif

#include <stdexcept>

#include "blob/blob_client.h"
#include "set_access_control_request.h"
#include "list_paths_request.h"

namespace azure { namespace storage_adls {
    using storage_account = azure::storage_lite::storage_account;
    using executor_context = azure::storage_lite::executor_context;

    struct list_filesystems_item
    {
        std::string name;
    };

    struct list_filesystems_result
    {
        std::vector<list_filesystems_item> filesystems;
        std::string continuation_token;
    };

    struct storage_exception : public std::exception
    {
        storage_exception(int code, std::string code_name, std::string message) : code(code), code_name(std::move(code_name)), message(std::move(message)) {}

        int code;
        std::string code_name;
        std::string message;
    };

    class adls_client final
    {
    public:
        AZURE_STORAGE_ADLS_API adls_client(std::shared_ptr<storage_account> account, int max_concurrency, bool exception_enabled = true);

        AZURE_STORAGE_ADLS_API void create_filesystem(const std::string& filesystem);
        AZURE_STORAGE_ADLS_API void delete_filesystem(const std::string& filesystem);
        AZURE_STORAGE_ADLS_API bool filesystem_exists(const std::string& filesystem);
        AZURE_STORAGE_ADLS_API void set_filesystem_properties(const std::string& filesystem, const std::vector<std::pair<std::string, std::string>>& properties);
        AZURE_STORAGE_ADLS_API std::vector<std::pair<std::string, std::string>> get_filesystem_properties(const std::string& filesystem);
        AZURE_STORAGE_ADLS_API list_filesystems_result list_filesystems_segmented(const std::string& prefix, const std::string& continuation_token = std::string(), const int max_results = 0);

        AZURE_STORAGE_ADLS_API void create_directory(const std::string& filesystem, const std::string& directory);
        AZURE_STORAGE_ADLS_API void delete_directory(const std::string& filesystem, const std::string& directory);
        AZURE_STORAGE_ADLS_API bool directory_exists(const std::string& filesystem, const std::string& directory);
        AZURE_STORAGE_ADLS_API void move_directory(const std::string& filesystem, const std::string& source_path, const std::string& destination_path);
        AZURE_STORAGE_ADLS_API void move_directory(const std::string& source_filesystem, const std::string& source_path, const std::string& destination_filesystem, const std::string& destination_path);
        AZURE_STORAGE_ADLS_API void set_directory_properties(const std::string& filesystem, const std::string& directory, const std::vector<std::pair<std::string, std::string>>& properties);
        AZURE_STORAGE_ADLS_API std::vector<std::pair<std::string, std::string>> get_directory_properties(const std::string& filesystem, const std::string& directory);
        AZURE_STORAGE_ADLS_API void set_directory_access_control(const std::string& filesystem, const std::string& directory, const access_control& acl);
        AZURE_STORAGE_ADLS_API access_control get_directory_access_control(const std::string& filesystem, const std::string& directory);
        AZURE_STORAGE_ADLS_API list_paths_result list_paths_segmented(const std::string& filesystem, const std::string& directory, bool recursive = false, const std::string& continuation_token = std::string(), const int max_results = 0);

        AZURE_STORAGE_ADLS_API void create_file(const std::string& filename, const std::string& file);
        AZURE_STORAGE_ADLS_API void append_data_from_stream(const std::string& filesystem, const std::string& file, uint64_t offset, std::istream& in_stream, uint64_t stream_len = 0);
        AZURE_STORAGE_ADLS_API void flush_data(const std::string& filesystem, const std::string& file, uint64_t offset);
        AZURE_STORAGE_ADLS_API void upload_file_from_stream(const std::string& filesystem, const std::string& file, std::istream& in_stream, const std::vector<std::pair<std::string, std::string>>& properties = std::vector<std::pair<std::string, std::string>>());
        AZURE_STORAGE_ADLS_API void download_file_to_stream(const std::string& filesystem, const std::string& file, std::ostream& out_stream);
        AZURE_STORAGE_ADLS_API void download_file_to_stream(const std::string& filesystem, const std::string& file, uint64_t offset, uint64_t size, std::ostream& out_stream);
        AZURE_STORAGE_ADLS_API void delete_file(const std::string& filesystem, const std::string& file);
        AZURE_STORAGE_ADLS_API bool file_exists(const std::string& filesystem, const std::string& file);
        AZURE_STORAGE_ADLS_API void move_file(const std::string& filesystem, const std::string& source_path, const std::string& destination_path);
        AZURE_STORAGE_ADLS_API void move_file(const std::string& source_filesystem, const std::string& source_path, const std::string& destination_filesystem, const std::string& destination_path);
        AZURE_STORAGE_ADLS_API void set_file_properties(const std::string& filesystem, const std::string& file, const std::vector<std::pair<std::string, std::string>>& properties);
        AZURE_STORAGE_ADLS_API std::vector<std::pair<std::string, std::string>> get_file_properties(const std::string& filesystem, const std::string& file);
        AZURE_STORAGE_ADLS_API void set_file_access_control(const std::string& filesystem, const std::string& file, const access_control& acl);
        AZURE_STORAGE_ADLS_API access_control get_file_access_control(const std::string& filesystem, const std::string& file);

        bool exception_enabled() const
        {
            return m_exception_enabled;
        }
    private:
        template<class RET, class FUNC>
        RET blob_client_adaptor(FUNC func);

        bool success() const
        {
            return !(!m_exception_enabled && errno != 0);
        }

    private:
        std::shared_ptr<azure::storage_lite::blob_client> m_blob_client;
        std::shared_ptr<storage_account> m_account;
        std::shared_ptr<executor_context> m_context;

        const bool m_exception_enabled;
    };

}}  // azure::storage_adls