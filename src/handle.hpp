#ifndef HANDLE_HPP
#define HANDLE_HPP

// handle_t is a 'strong typedef' for integer types.
// It supports the same operations that pointers support.

// EXAMPLE
//   Instead of doing:
//     using my_index_type = int;
//   Do:
//     using my_index_type = handle_t<int, struct some_unique_tag>;

#include <functional>
#include <ostream>

#include "robin/hash.hpp"

template<typename Int, typename Tag, Int Null = 0, bool GT = false>
struct handle_t
{
    using int_type = Int;
    using tag_type = Tag;
    int_type value = Null;

    static constexpr Int null = Null;

    constexpr explicit operator bool() const 
    { 
        if(GT)
            return value > Null;
        else
            return value != Null; 
    }

    constexpr auto operator<=>(handle_t const&) const = default;
    constexpr bool operator!() const { return !operator bool(); }

    handle_t& operator++() { ++value; return *this; }
    handle_t operator++(int) { handle_t h = *this; ++value; return h; }
    handle_t& operator--() { --value; return *this; }
    handle_t operator--(int) { handle_t h = *this; --value; return h; }

    handle_t& operator+=(int_type b) { value += b; return *this; }
    handle_t& operator-=(int_type b) { value -= b; return *this; }

    friend constexpr handle_t operator+(handle_t a, int_type b) 
        { return { a.value + b }; }
    friend constexpr handle_t operator+(int_type a, handle_t b) 
        { return { a + b.value }; }

    friend constexpr handle_t operator-(handle_t a, int_type b) 
        { return { a.value - b }; }
    friend constexpr handle_t operator-(int_type a, handle_t b)
        { return { a - b.value }; }
    friend constexpr int_type operator-(handle_t a, handle_t b) 
        { return { a.value - b.value }; }

    std::size_t hash() const { return rh::hash_finalize(value); }
};

template<typename Int, typename Tag>
std::ostream& operator<<(std::ostream& os, handle_t<Int, Tag> handle)
{
    os << "{" << handle.value << "}";
    return os;
}

template<typename T>
struct handle_hash_t
{
    using argument_type = T;
    using result_type = std::size_t;
    result_type operator()(argument_type const& handle) const noexcept { return handle.hash(); }
};

namespace std
{
    template<typename Int, typename Tag, Int Null, bool GT>
    struct hash<handle_t<Int, Tag, Null, GT>> 
    : public handle_hash_t<handle_t<Int, Tag, Null, GT>>
    {};
}

#endif
