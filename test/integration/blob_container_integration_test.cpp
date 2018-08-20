#include "blob_integration_base.h"

#include "../catch2/catch.hpp"

TEST_CASE("Create containers", "[container],[blob_service]")
{
    microsoft_azure::storage::blob_client client = as_test::base::test_blob_client();
    std::string prefix = as_test::get_random_string(10);
    SECTION("Create container with number and character name successfully") {
        auto container_name = prefix + as_test::get_random_string(10);
        auto first_outcome = client.create_container(container_name).get();
        REQUIRE(first_outcome.success());
        auto second_outcome = client.get_container_property(container_name);
        REQUIRE(second_outcome.success());
        REQUIRE_FALSE(second_outcome.response().etag.empty());
        client.delete_container(container_name).wait();
    }

    SECTION("Create container with uppercase name unsuccessfully") {
        auto container_name = "ABD" + prefix + as_test::get_random_string(10);
        auto first_outcome = client.create_container(container_name).get();
        REQUIRE_FALSE(first_outcome.success());
        REQUIRE(first_outcome.error().code == "400");
        REQUIRE(first_outcome.error().code_name == "InvalidResourceName");
        auto second_outcome = client.get_container_property(container_name);
        REQUIRE(second_outcome.success());
        REQUIRE(second_outcome.response().etag.empty());
    }

    SECTION("Create container with dash in name successfully") {
        auto container_name = prefix + "-" + as_test::get_random_string(10);
        auto first_outcome = client.create_container(container_name).get();
        REQUIRE(first_outcome.success());
        auto second_outcome = client.get_container_property(container_name);
        REQUIRE(second_outcome.success());
        REQUIRE_FALSE(second_outcome.response().etag.empty());
        client.delete_container(container_name).wait();
    }
}

TEST_CASE("Delete containers", "[container],[blob_service]")
{
    microsoft_azure::storage::blob_client client = as_test::base::test_blob_client();
    std::string prefix = as_test::get_random_string(10);
    SECTION("Delete existing container successfully") {
        auto container_name = prefix + as_test::get_random_string(10);
        auto first_outcome = client.create_container(container_name).get();
        REQUIRE(first_outcome.success());
        auto second_outcome = client.get_container_property(container_name);
        REQUIRE(second_outcome.success());
        REQUIRE_FALSE(second_outcome.response().etag.empty());
        auto third_outcome = client.delete_container(container_name).get();
        REQUIRE(third_outcome.success());
    }

    SECTION("Delete in-existing container successfully") {
        auto container_name = prefix + as_test::get_random_string(10);
        auto first_outcome = client.delete_container(container_name).get();
        REQUIRE_FALSE(first_outcome.success());
    }
}

TEST_CASE("Get Container Property", "[container], [blob_service]")
{
    microsoft_azure::storage::blob_client client = as_test::base::test_blob_client();
    std::string prefix = as_test::get_random_string(10);
    SECTION("Get container property from existing container") {
        auto container_name = prefix + as_test::get_random_string(10);
        auto first_outcome = client.create_container(container_name).get();
        REQUIRE(first_outcome.success());
        auto second_outcome = client.get_container_property(container_name);
        REQUIRE(second_outcome.success());
        REQUIRE_FALSE(second_outcome.response().etag.empty());
        client.delete_container(container_name).wait();
    }

    SECTION("Get container property from non-existing container") {
        auto container_name = prefix + as_test::get_random_string(10);
        auto first_outcome = client.get_container_property(container_name);
        REQUIRE(first_outcome.success());
    }
}

TEST_CASE("List containers", "[container],[blob_service]")
{
    microsoft_azure::storage::blob_client client = as_test::base::test_blob_client();
    std::string prefix_1 = as_test::get_random_string(10);
    std::string prefix_2 = as_test::get_random_string(10);
    unsigned container_size = 5;
    std::vector<std::string> containers;
    for (unsigned i = 0; i < container_size; ++i)
    {
        auto container_name_1 = prefix_1 + as_test::get_random_string(10);
        auto container_name_2 = prefix_2 + as_test::get_random_string(10);
        client.create_container(container_name_1).wait();
        client.create_container(container_name_2).wait();
        containers.push_back(container_name_1);
        containers.push_back(container_name_2);
    }

    SECTION("List containers successfully") {
        auto list_containers_outcome = client.list_containers("").get();
        REQUIRE(list_containers_outcome.success());
        auto result_containers = list_containers_outcome.response().containers;
        REQUIRE(result_containers.size() == 2); // Current max result is hard-coded to 2
    }

    SECTION("List containers with prefix successfully") {
        {
            auto list_containers_outcome = client.list_containers(prefix_1).get();
            REQUIRE(list_containers_outcome.success());
            auto result_containers = list_containers_outcome.response().containers;
            REQUIRE(result_containers.size() == 2); // Current max result is hard-coded to 2
            for (auto container : result_containers)
            {
                REQUIRE(std::find(containers.begin(), containers.end(), container.name) != containers.end());
                REQUIRE(container.name.substr(0, prefix_1.size()) == prefix_1);
            }
        }

        {
            auto list_containers_outcome = client.list_containers(prefix_2).get();
            REQUIRE(list_containers_outcome.success());
            auto result_containers = list_containers_outcome.response().containers;
            REQUIRE(result_containers.size() == 2); // Current max result is hard-coded to 2
            for (auto container : result_containers)
            {
                REQUIRE(std::find(containers.begin(), containers.end(), container.name) != containers.end());
                REQUIRE(container.name.substr(0, prefix_2.size()) == prefix_2);
            }
        }

        {
            auto list_containers_outcome = client.list_containers(as_test::get_random_string(20)).get();
            REQUIRE(list_containers_outcome.success());
            REQUIRE(list_containers_outcome.response().containers.size() == 0);
        }
    }

    SECTION("List containers with invalid prefix successfully") {
        auto list_containers_outcome = client.list_containers("1~invalid~~%d_prefix").get();
        REQUIRE(list_containers_outcome.success());
        REQUIRE(list_containers_outcome.response().containers.empty());
    }

    for (auto container : containers)
    {
        client.delete_container(container).wait();
    }
}
