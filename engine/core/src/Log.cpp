#include "core/Log.h"

#include <mutex>
#include <unordered_map>

namespace Oasis::Log {

namespace {

struct Registry {
    std::mutex                       mutex;
    std::unordered_map<SinkId, Sink> sinks;
    SinkId                           next_id = 1;
};

Registry& registry()
{
    static Registry s_registry;
    return s_registry;
}

} // namespace

SinkId add_sink(Sink sink)
{
    auto& reg = registry();
    std::lock_guard lock(reg.mutex);
    const SinkId id = reg.next_id++;
    reg.sinks.emplace(id, std::move(sink));
    return id;
}

void remove_sink(SinkId id)
{
    auto& reg = registry();
    std::lock_guard lock(reg.mutex);
    reg.sinks.erase(id);
}

void log(Level level, std::string_view message, std::source_location loc)
{
    const Record record{level, message, loc};
    auto& reg = registry();
    std::lock_guard lock(reg.mutex);
    for (auto& [id, sink] : reg.sinks)
        sink(record);
}

} // namespace Oasis::Log
