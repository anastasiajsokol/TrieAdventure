#ifndef NODES_BITMASK_HPP
#define NODES_BITMASK_HPP

#include "utility.hpp"

struct Bitmask {
    std::optional<Bitmask*> getprefix(prefix_t prefix, bool create = false);
    void mark_complete();
    bool is_complete();
};

#endif