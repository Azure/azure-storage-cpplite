#pragma once

#ifdef _WIN32
#ifdef azure_storage_lite_EXPORTS
#define AZURE_STORAGE_API __declspec(dllexport)
#else
#define AZURE_STORAGE_API __declspec(dllimport)
#endif
#else /* ifdef _WIN32 */
#define AZURE_STORAGE_API
#endif
