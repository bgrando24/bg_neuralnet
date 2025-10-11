#include <iostream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

int main()
{
    std::cout << "Hello, world!" << std::endl;
    spdlog::info("Hello from spdlog!");

    nlohmann::json j = {{"msg", "json works"}, {"n", 42}};
    spdlog::info("JSON: {}", j.dump());

    spdlog::info("All good!");
    return 0;
}