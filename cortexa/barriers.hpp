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

namespace CortexA {
    static inline void DataSyncBarrier()
    {
        asm volatile("dsb sy" : : : "memory");
    }

    static inline void DataMemBarrier()
    {
        asm volatile("dmb sy" : : : "memory");
    }

    static inline void InstrSyncBarrier()
    {
        asm volatile("isb sy" : : : "memory");
    }

    static inline void CompilerBarrier()
    {
        asm volatile("" : : : "memory");
    }

    // Cortex-A specific barriers
    static inline void DataSyncBarrierInnerShareable()
    {
        asm volatile("dsb ish" : : : "memory");
    }

    static inline void DataSyncBarrierOuterShareable()
    {
        asm volatile("dsb osh" : : : "memory");
    }

    static inline void DataSyncBarrierNonShareable()
    {
        asm volatile("dsb nsh" : : : "memory");
    }

    static inline void DataMemBarrierInnerShareable()
    {
        asm volatile("dmb ish" : : : "memory");
    }

    static inline void DataMemBarrierOuterShareable()
    {
        asm volatile("dmb osh" : : : "memory");
    }

    static inline void DataMemBarrierNonShareable()
    {
        asm volatile("dmb nsh" : : : "memory");
    }
}
