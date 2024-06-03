#ifndef NODES_DEEP_HPP
#define NODES_DEEP_HPP

#include "utility.hpp"

struct Deep {
    std::optional<Deep*> getprefix(prefix_t prefix, bool create = false);
    void mark_complete();
    bool is_complete();
};

#endif