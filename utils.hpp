/*
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexA-CppLib>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <cstdint>

namespace Utils {

//! Divides two integers and rounds the result up to the nearest multiple of divisor.
template<typename Tin, typename Tout>
static inline Tout intCeilDiv(Tin dividend, Tin divisor)
{
    return (dividend + divisor - 1) / divisor;
}

//! Check if the n-th bit is set in the value.
template<typename T>
static inline bool isBitSet(T value, uint8_t n)
{
    return (value >> n) & 1;
}

//! Sets the n-th bit in the value.
template<typename T>
static inline void setBit(T& value, uint8_t n)
{
    value |= 1 << n;
}

//! Clears the n-th bit in the value.
template<typename T>
static inline void clearBit(T& value, uint8_t n)
{
    value &= ~(1 << n);
}

}
