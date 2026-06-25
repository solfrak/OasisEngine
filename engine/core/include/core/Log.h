#pragma once

#include <concepts>
#include <cstdint>
#include <memory>
#include <source_location>
#include <string_view>

namespace Oasis::Log {

enum class Level : uint8_t { Trace, Info, Warn, Error };

struct Record {
    Level                level;
    std::string_view     message;
    std::source_location location;
};

// A sink may expose either a .write(const Record&) method or operator()(const Record&).
template<typename T>
concept WritableSink = requires(T& t, const Record& r) { t.write(r); };

template<typename T>
concept CallableSink = std::invocable<T, const Record&>;

template<typename T>
concept Sinkable = WritableSink<T> || CallableSink<T>;

// Type-erased sink wrapper — no virtual functions.
// Internally stores the concrete type via shared_ptr<void> and dispatches
// through a plain function pointer with the type baked in at construction time.
class Sink {
public:
    template<Sinkable T>
    explicit Sink(T t)
        : m_data(std::make_shared<T>(std::move(t)))
    {
        if constexpr (WritableSink<T>)
            m_dispatch = [](void* p, const Record& r) { static_cast<T*>(p)->write(r); };
        else
            m_dispatch = [](void* p, const Record& r) { (*static_cast<T*>(p))(r); };
    }

    void operator()(const Record& r) const { m_dispatch(m_data.get(), r); }

private:
    std::shared_ptr<void> m_data;
    void (*m_dispatch)(void*, const Record&) = nullptr;
};

using SinkId = uint32_t;

SinkId add_sink(Sink sink);
void   remove_sink(SinkId id);

// Default argument captures the call site — no macros needed.
void log(Level level, std::string_view message,
         std::source_location loc = std::source_location::current());

inline void trace(std::string_view msg, std::source_location loc = std::source_location::current()) { log(Level::Trace, msg, loc); }
inline void info (std::string_view msg, std::source_location loc = std::source_location::current()) { log(Level::Info,  msg, loc); }
inline void warn (std::string_view msg, std::source_location loc = std::source_location::current()) { log(Level::Warn,  msg, loc); }
inline void error(std::string_view msg, std::source_location loc = std::source_location::current()) { log(Level::Error, msg, loc); }

} // namespace Oasis::Log
