#pragma once
#include <SDL.h>

template<typename Container, typename Iter>
static bool validateIter(const Container& c, Iter iter)
{
    const bool isValid{ iter != std::end(c) };

    SDL_assert(isValid);
    return isValid;
}