#include <iostream>
#include <string>

#include "core/Core.h"
#include "core/Log.h"
#include "platform/Platform.h"

// Sink as a struct with .write()
struct ConsoleSink {
    void write(const Oasis::Log::Record& r) const
    {
        static constexpr std::string_view labels[] = {"TRACE", "INFO ", "WARN ", "ERROR"};
        std::cout << '[' << labels[static_cast<int>(r.level)] << "] "
                  << r.message << '\n';
    }
};

int main()
{
    std::cout << "=== Oasis Engine ===\n";

    // Struct-based sink
    auto console_id = Oasis::Log::add_sink(Oasis::Log::Sink{ConsoleSink{}});

    // Lambda-based sink (callable)
    std::string captured;
    auto capture_id = Oasis::Log::add_sink(Oasis::Log::Sink{
        [&captured](const Oasis::Log::Record& r) {
            captured += r.message;
            captured += '\n';
        }
    });

    Oasis::Core::Initialize();
    Oasis::Platform::Initialize();

    Oasis::Log::info("Engine started");
    Oasis::Log::warn("Low memory");
    Oasis::Log::error("Something went wrong");

    // Remove lambda sink — console still active
    Oasis::Log::remove_sink(capture_id);
    Oasis::Log::info("Only console sink active now");

    std::cout << "Captured log:\n" << captured;

    Oasis::Platform::Shutdown();
    Oasis::Core::Shutdown();

    Oasis::Log::remove_sink(console_id);
    return 0;
}
