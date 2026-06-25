#include "platform/Platform.h"

#include <iostream>

namespace Oasis::Platform {

void Initialize()
{
    std::cout << "[Platform] Initialized\n";
}

void Shutdown()
{
    std::cout << "[Platform] Shutdown\n";
}

} // namespace Oasis::Platform
