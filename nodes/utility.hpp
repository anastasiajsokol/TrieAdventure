#ifndef NODES_TYPES_HPP
#define NODES_TYPES_HPP

#include <optional>
#include <cstddef>
#include <memory>
#include <array>

template <typename T>
const auto& make_pointer = std::make_shared<T>;

template <typename T>
using pointer_t = std::shared_ptr<T>;

using prefix_t = const char*;

// The c++ standard does not guarentee that the character encoding of a-z is continuous.
// this means 'b' - 'a' may not equal one, as we would want.
constexpr bool character_set_is_continious(){
    #define test(letter, number) (letter - 'a' == number)
    return test('a', 0) && test('b', 1) && test('c', 2) && test('d', 3) && test('e', 4) && test('f', 5) && test('g', 6) && test('h', 7) && test('i', 8) && test('j', 9) && test('k', 10) && test('l', 11) && test('m', 12) && test('n', 13) && test('o', 14) && test('p', 15) && test('q', 16) && test('r', 17) && test('s', 18) && test('t', 19) && test('u', 20) && test('v', 21) && test('w', 22) && test('x', 23) && test('y', 24) && test('z', 25);
    #undef test
}

// returns the true character index regardless of character encoding
// undefined for values that are not lowercase characters
constexpr std::size_t character_to_index(const char character){
    if constexpr (character_set_is_continious()){
        // if it is continious this is really fast and easy
        return character - 'a';
    } else {
        // otherwise switch for each possibility
        switch(character){
            case 'a': return 0; case 'b': return 1; case 'c': return 2; case 'd': return 3; case 'e': return 4;
            case 'f': return 5; case 'g': return 6; case 'h': return 7; case 'i': return 8; case 'j': return 9;
            case 'k': return 10; case 'l': return 11; case 'm': return 12; case 'n': return 13; case 'o': return 14;
            case 'p': return 15; case 'q': return 16; case 'r': return 17; case 's': return 18; case 't': return 19;
            case 'u': return 20; case 'v': return 21; case 'w': return 22; case 'x': return 23; case 'y': return 24;
            case 'z': return 25; default: return -1;
        }
    }
}

// inverse of character_to_index
constexpr char index_to_character(const std::size_t index){
    if constexpr (character_set_is_continious()){
        // if it is continious this is really fast and easy
        return index + 'a';
    } else {
        // otherwise switch for each possibility
        switch(index){
            case 0: return 'a'; case 1: return 'b'; case 2: return 'c'; case 3: return 'd'; case 4: return 'e';
            case 5: return 'f'; case 6: return 'g'; case 7: return 'h'; case 8: return 'i'; case 9: return 'j';
            case 10: return 'k'; case 11: return 'l'; case 12: return 'm'; case 13: return 'n'; case 14: return 'o';
            case 15: return 'p'; case 16: return 'q'; case 17: return 'r'; case 18: return 's'; case 19: return 't';
            case 20: return 'u'; case 21: return 'v'; case 22: return 'w'; case 23: return 'x'; case 24: return 'y';
            case 25: return 'z'; default: return '!';
        }
    }
}

#endif