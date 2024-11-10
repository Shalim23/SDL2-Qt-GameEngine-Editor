#pragma once
#include <cassert>

template<typename Container, typename Iter>
static bool validateIter(const Container& c, Iter iter)
{
    const bool isValid{ iter != std::end(c) };

    assert(isValid && "Failed to validate requested iterator!");
    return isValid;
}