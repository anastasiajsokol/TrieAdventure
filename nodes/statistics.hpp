#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#include "utility.hpp"

// Expansion of the basic trie node to allow for the collection of statistics data
struct StatisticsNode {
    std::array<pointer_t<StatisticsNode>, 26> children;
    bool terminal = false;

    std::size_t size() const;
    std::size_t count_children() const;
    std::size_t count_descendants() const;
    void record_histogram(std::array<std::size_t, 26> &histogram) const;

    // the methods below implement the basic node interface
    // they should NOT need to be modified

    std::optional<StatisticsNode*> getprefix(prefix_t prefix, bool create = false){
        if(!*prefix){
            // if we reached the end of the prefix then the current node is the result
            return this;
        }

        // in most - but not all - encodings just *prefix - 'a' is equivalent
        std::size_t index = character_to_index(*prefix);

        if(children[index]){
            // if the next character exists, go there
            // increment prefix to go to the next letter
            return children[index]->getprefix(prefix + 1, create);
        } else if(create){
            // since the next character does not exist and create is set make a new child
            children[index] = make_pointer<StatisticsNode>();
            
            // then continue on as before
            return children[index]->getprefix(prefix + 1, create);
        }

        // since we covered all the possible next steps, out search failed
        return std::nullopt;
    }

    // marks the current node as a complete word
    void mark_complete(){
        terminal = true;
    }

    // check if the current node is a complete word
    bool is_complete() const {
        return terminal;
    }
};

// !REMOVE BEFORE PUBLISHING AS AN ASSIGNMENT!

#include <numeric>

std::size_t StatisticsNode::size() const {
    return std::accumulate(
        std::begin(children),
        std::end(children),
        std::size_t(terminal),
        [](std::size_t sum, const pointer_t<StatisticsNode> next) -> std::size_t {
            return sum + (next ? next->size() : 0);
        }
    );
}

std::size_t StatisticsNode::count_children() const {
    return std::accumulate(
        std::begin(children),
        std::end(children),
        0,
        [](std::size_t sum, const pointer_t<StatisticsNode> next) -> std::size_t {
            return sum + !!next;
        }
    );
}

std::size_t StatisticsNode::count_descendants() const {
    return std::accumulate(
        std::begin(children),
        std::end(children),
        count_children(),
        [](std::size_t sum, const pointer_t<StatisticsNode> next) -> std::size_t {
            return sum + (next ? next->count_descendants() : 0);
        }
    );
}

void StatisticsNode::record_histogram(std::array<std::size_t, 26> &histogram) const {
    ++histogram[count_children()];
    for(const pointer_t<StatisticsNode> &child : children){
        if(child){
            child->record_histogram(histogram);
        }
    }
}

#endif