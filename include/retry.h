#pragma once

#include <chrono>
#include <algorithm>
#include <math.h>

#include "storage_EXPORTS.h"

#include "http_base.h"
#include "utility.h"

#pragma push_macro("min")
#undef min

namespace azure {  namespace storage_lite {

    class retry_info final
    {
    public:
        retry_info(bool should_retry, std::chrono::seconds interval)
            : m_should_retry(should_retry),
            m_interval(interval) {}

        bool should_retry() const
        {
            return m_should_retry;
        }

        std::chrono::seconds interval() const
        {
            return m_interval;
        }

    private:
        bool m_should_retry;
        std::chrono::seconds m_interval;
    };

    class retry_context final
    {
    public:
        retry_context()
            : m_numbers(0),
            m_result(0) {}

        retry_context(int numbers, http_base::http_code result)
            : m_numbers(numbers),
            m_result(result) {}

        int numbers() const
        {
            return m_numbers;
        }

        http_base::http_code result() const
        {
            return m_result;
        }

        void add_result(http_base::http_code result)
        {
            m_result = result;
            m_numbers++;
        }

    private:
        int m_numbers;
        http_base::http_code m_result;
    };

    class retry_policy_base
    {
    public:
        virtual ~retry_policy_base() {}
        virtual retry_info evaluate(const retry_context &context) const = 0;
    };

    class retry_policy final : public retry_policy_base
    {
    public:

        retry_policy(const int maximum_retries = 3, const std::chrono::seconds base_timeout = std::chrono::seconds{10})
            : m_maximum_retries(maximum_retries),
            m_base_timeout(base_timeout)
        {
        }

        retry_info evaluate(const retry_context &context) const override
        {
            if (context.numbers() >= m_maximum_retries ||
                !can_retry(context.result()))
            {
                return retry_info(false, std::chrono::seconds(0));
            }

            return retry_info(true, calculate_new_delay(context));
        }

    private:
        bool can_retry(http_base::http_code code) const
        {
            return retryable(code);
        }

        std::chrono::seconds calculate_new_delay(const retry_context &context)
        {
            // (1 << N) == 2^N
            return ((context.numbers() == 0) ? 0 : (m_base_timeout * (1 << context.numbers())));
        }

        const int m_maximum_retries;
        const std::chrono::seconds m_base_timeout;
    };

}}  // azure::storage_lite

#pragma pop_macro("min")
