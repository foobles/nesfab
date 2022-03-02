#ifndef SPAN_HPP
#define SPAN_HPP

#include <cstdint>
#include <ostream>

// Spans are intrevals representing memory regions.

struct span_t
{
    std::uint16_t addr;
    std::uint16_t size;
    
    std::uint16_t end() const { return addr + size; }
    constexpr explicit operator bool() const { return size; }

    bool contains(span_t const& o) const { return o.addr >= addr && o.end() <= end(); }
    bool intersects(span_t const& o) const { return o.end() > addr && end() > o.addr; }
};

std::ostream& operator<<(std::ostream& o, span_t span);

span_t aligned(span_t span, std::uint16_t size, std::uint16_t alignment);
span_t aligned_reverse(span_t span, std::uint16_t size, std::uint16_t alignment);

#endif