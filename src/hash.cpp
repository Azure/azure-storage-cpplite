#include "hash.h"

#include "base64.h"

namespace azure {  namespace storage_lite {
#ifdef _WIN32
    hmac_sha256_hash_algorithm hmac_sha256_hash_provider::_algorithm;

    std::string hmac_sha256_hash_provider::hash_impl(const std::string &input, const std::vector<unsigned char> &key)
    {
        ULONG object_size = 0;
        ULONG size_length = 0;

        NTSTATUS status = BCryptGetProperty(_algorithm.handle(), BCRYPT_OBJECT_LENGTH, (PUCHAR)&object_size, sizeof(ULONG), &size_length, 0);
        if (status != 0)
        {
            throw std::system_error(status, std::system_category());
        }
        std::vector<UCHAR> hash_object(object_size);

        BCRYPT_HASH_HANDLE hash_handle;
        status = BCryptCreateHash(_algorithm.handle(), &hash_handle, (PUCHAR)hash_object.data(), (ULONG)hash_object.size(), (PUCHAR)key.data(), (ULONG)key.size(), 0);
        if (status != 0)
        {
            throw std::system_error(status, std::system_category());
        }

        status = BCryptHashData(hash_handle, (PUCHAR)input.data(), (ULONG)input.size(), 0);
        if (status != 0)
        {
            throw std::system_error(status, std::system_category());
        }

        status = BCryptGetProperty(hash_handle, BCRYPT_HASH_LENGTH, (PUCHAR)&object_size, sizeof(ULONG), &size_length, 0);
        if (status != 0)
        {
            throw std::system_error(status, std::system_category());
        }
        std::vector<UCHAR> hash(object_size);

        status = BCryptFinishHash(hash_handle, hash.data(), (ULONG)hash.size(), 0);
        if (status != 0 && status != 0xc0000008)
        {
            throw std::system_error(status, std::system_category());
        }

        status = BCryptDestroyHash(hash_handle);
        return to_base64(hash);
    }
#else
    std::string hash(const std::string &to_sign, const std::vector<unsigned char> &key)
    {
        unsigned int l = SHA256_DIGEST_LENGTH;
        unsigned char digest[SHA256_DIGEST_LENGTH];

#ifdef USE_OPENSSL
#if OPENSSL_VERSION_NUMBER < 0x10100000L
        HMAC_CTX ctx;
        HMAC_CTX_init(&ctx);
        HMAC_Init_ex(&ctx, key.data(), key.size(), EVP_sha256(), NULL);
        HMAC_Update(&ctx, (const unsigned char*)to_sign.c_str(), to_sign.size());
        HMAC_Final(&ctx, digest, &l);
        HMAC_CTX_cleanup(&ctx);
#else
        HMAC_CTX *ctx = HMAC_CTX_new();
        HMAC_CTX_reset(ctx);
        HMAC_Init_ex(ctx, key.data(), key.size(), EVP_sha256(), NULL);
        HMAC_Update(ctx, (const unsigned char*)to_sign.c_str(), to_sign.size());
        HMAC_Final(ctx, digest, &l);
        HMAC_CTX_free(ctx); 
#endif
#else
        gnutls_hmac_fast(GNUTLS_MAC_SHA256, key.data(), key.size(), (const unsigned char *)to_sign.data(), to_sign.size(), digest);
#endif

        return to_base64(std::vector<unsigned char>(digest, digest + l));
    }
#endif

}}  // azure::storage_lite
