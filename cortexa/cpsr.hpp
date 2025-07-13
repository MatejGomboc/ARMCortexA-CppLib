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

namespace CortexA {
    
    // Current Program Status Register
    union CPSR {
        struct Bits {
            uint32_t M:5;        //!< Mode field
            uint32_t T:1;        //!< Thumb execution state bit
            uint32_t F:1;        //!< FIQ mask bit
            uint32_t I:1;        //!< IRQ mask bit
            uint32_t A:1;        //!< Asynchronous abort mask bit
            uint32_t E:1;        //!< Endianness execution state bit
            uint32_t IT1:6;      //!< If-Then execution state bits 2-7
            uint32_t GE:4;       //!< Greater than or Equal flags
            uint32_t reserved:4;
            uint32_t J:1;        //!< Jazelle bit
            uint32_t IT0:2;      //!< If-Then execution state bits 0-1
            uint32_t Q:1;        //!< Saturation condition flag
            uint32_t V:1;        //!< Overflow condition code flag
            uint32_t C:1;        //!< Carry condition code flag
            uint32_t Z:1;        //!< Zero condition code flag
            uint32_t N:1;        //!< Negative condition code flag
        } bits;
        
        uint32_t value = 0;
        
        CPSR() = default;
        
        CPSR(uint32_t new_value)
        {
            value = new_value;
        }
    };
    
    // Processor modes
    enum class ProcessorMode : uint8_t {
        USR = 0x10,  //!< User mode (PL0)
        FIQ = 0x11,  //!< Fast Interrupt mode (PL1)
        IRQ = 0x12,  //!< Interrupt mode (PL1)
        SVC = 0x13,  //!< Supervisor mode (PL1)
        MON = 0x16,  //!< Monitor mode (PL1)
        ABT = 0x17,  //!< Abort mode (PL1)
        HYP = 0x1A,  //!< Hypervisor mode (PL2)
        UND = 0x1B,  //!< Undefined mode (PL1)
        SYS = 0x1F   //!< System mode (PL1)
    };
    
    static inline CPSR getCPSR()
    {
        CPSR cpsr;
        asm volatile("mrs %0, cpsr" : "=r" (cpsr.value));
        return cpsr;
    }
    
    static inline void setCPSR(CPSR cpsr)
    {
        asm volatile("msr cpsr, %0" : : "r" (cpsr.value) : "cc", "memory");
    }
    
    static inline ProcessorMode getMode()
    {
        return static_cast<ProcessorMode>(getCPSR().bits.M);
    }
    
    static inline void setMode(ProcessorMode mode)
    {
        asm volatile("msr cpsr_c, %0" : : "r" (static_cast<uint32_t>(mode)) : "memory");
    }
    
    static inline bool areInterruptsEnabled()
    {
        return getCPSR().bits.I == 0;
    }
    
    static inline bool areFastInterruptsEnabled()
    {
        return getCPSR().bits.F == 0;
    }
    
    static inline void enableInterrupts()
    {
        asm volatile("cpsie i" : : : "memory");
    }
    
    static inline void disableInterrupts()
    {
        asm volatile("cpsid i" : : : "memory");
    }
    
    static inline void enableFastInterrupts()
    {
        asm volatile("cpsie f" : : : "memory");
    }
    
    static inline void disableFastInterrupts()
    {
        asm volatile("cpsid f" : : : "memory");
    }
}
