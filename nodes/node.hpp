#ifndef NODES_NODE_HPP
#define NODES_NODE_HPP

#include "utility.hpp"

// The basic node implementation, which is similar to the one discussed in class
struct Node {
    std::array<pointer_t<Node>, 26> children;
    bool terminal;

    std::optional<Node*> getprefix(prefix_t prefix, bool create = false){
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
            children[index] = make_pointer<Node>();
            
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

#endif