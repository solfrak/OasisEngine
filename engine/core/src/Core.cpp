#include "core/Core.h"

#include <iostream>

namespace Oasis::Core {

void Initialize()
{
    std::cout << "[Core] Initialized\n";
}

void Shutdown()
{
    std::cout << "[Core] Shutdown\n";
}

} // namespace Oasis::Core
