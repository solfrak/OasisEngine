#include <iostream>

#include "core/Core.h"
#include "platform/Platform.h"

int main()
{
    std::cout << "=== Oasis Engine ===\n";

    Oasis::Core::Initialize();
    Oasis::Platform::Initialize();

    std::cout << "Hello, World!\n";

    Oasis::Platform::Shutdown();
    Oasis::Core::Shutdown();

    return 0;
}
