#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <bit>

#include "Types/TypesListOperations.h"

class SystemInitContext;
class SystemUpdateContext;

class SystemManager final
{
public:
    SystemManager() = default;
    ~SystemManager() = default;
    SystemManager(const SystemManager&) = delete;
    SystemManager(SystemManager&&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;
    SystemManager& operator=(SystemManager&&) = delete;

    void init(SystemInitContext&);
    void update(SystemUpdateContext&);
    void shutdown();

    template<typename T>
    T& getSystem();

    template<typename SystemsList>
    void registerSystems();

private:
    std::unique_ptr<char[]> systems_;
    std::unordered_map<std::type_index, size_t> systemOffsetById_;
    size_t alignment_{0};
    size_t systemsCount_{0};
};

template<typename T>
T& SystemManager::getSystem()
{
    const auto iter{ systemOffsetById_.find(std::type_index{typeid(T)}) };

    if (iter == systemOffsetById_.end())
    {
        //throw
    }

    return *reinterpret_cast<T*>(systems_ + iter->second);
}

template<typename SystemsList>
void SystemManager::registerSystems()
{
    if (systems_)
    {
        return;
    }

    static_assert(std::enable_if_t<IsTypesList<SystemsList>::value, void>,
        "TypesList is expected!");

    static_assert(SystemsList::size > 0, "No systems to register!");
    checkDuplicates<SystemsList>();

    alignment_ = std::bit_ceil(SystemsList::getLargestTypeSize());
    systemsCount_ = SystemsList::size;

    systems_ = std::make_unique<char[]>(alignment_ * SystemsList::size);

    size_t nextAlignment{0};
    auto f{ [this] <typename... Ts>(TypesList<Ts...>)
    {
        ([this, &nextAlignment]
        {
            new(systems_.get() + nextAlignment) Ts{};
            systemOffsetById_.emplace(std::type_index{ typeid(Ts) }, nextAlignment);
            nextAlignment += alignment_;
        }(), ...);
    } };

    f(SystemsList{});
}
