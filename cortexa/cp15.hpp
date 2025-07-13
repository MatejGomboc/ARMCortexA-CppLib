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
#include "barriers.hpp"

namespace CortexA::CP15 {
    
    // System Control Register
    union SCTLR {
        struct Bits {
            uint32_t M:1;         //!< MMU enable
            uint32_t A:1;         //!< Alignment check enable
            uint32_t C:1;         //!< Cache enable
            uint32_t reserved0:2;
            uint32_t CP15BEN:1;   //!< CP15 barrier enable
            uint32_t reserved1:1;
            uint32_t B:1;         //!< Endianness model
            uint32_t reserved2:2;
            uint32_t SW:1;        //!< SWP and SWPB enable
            uint32_t Z:1;         //!< Branch prediction enable
            uint32_t I:1;         //!< Instruction cache enable
            uint32_t V:1;         //!< Vectors bit
            uint32_t RR:1;        //!< Round Robin select
            uint32_t reserved3:2;
            uint32_t HA:1;        //!< Hardware Access flag enable
            uint32_t reserved4:1;
            uint32_t WXN:1;       //!< Write permission implies XN
            uint32_t UWXN:1;      //!< Unprivileged write permission implies PL1 XN
            uint32_t FI:1;        //!< Fast interrupts configuration enable
            uint32_t U:1;         //!< Alignment model
            uint32_t reserved5:1;
            uint32_t VE:1;        //!< Interrupt Vectors Enable
            uint32_t EE:1;        //!< Exception Endianness
            uint32_t reserved6:1;
            uint32_t NMFI:1;      //!< Non-maskable FIQ support
            uint32_t TRE:1;       //!< TEX remap enable
            uint32_t AFE:1;       //!< Access flag enable
            uint32_t TE:1;        //!< Thumb Exception enable
            uint32_t reserved7:1;
        } bits;
        
        uint32_t value = 0;
        
        SCTLR() = default;
        
        SCTLR(uint32_t new_value)
        {
            value = new_value;
        }
    };
    
    // Auxiliary Control Register
    union ACTLR {
        struct Bits {
            uint32_t implementation_defined:32;  //!< Implementation specific
        } bits;
        
        uint32_t value = 0;
        
        ACTLR() = default;
        
        ACTLR(uint32_t new_value)
        {
            value = new_value;
        }
    };
    
    // Coprocessor Access Control Register
    union CPACR {
        struct Bits {
            uint32_t CP0:2;       //!< Access rights for coprocessor 0
            uint32_t CP1:2;       //!< Access rights for coprocessor 1
            uint32_t CP2:2;       //!< Access rights for coprocessor 2
            uint32_t CP3:2;       //!< Access rights for coprocessor 3
            uint32_t CP4:2;       //!< Access rights for coprocessor 4
            uint32_t CP5:2;       //!< Access rights for coprocessor 5
            uint32_t CP6:2;       //!< Access rights for coprocessor 6
            uint32_t CP7:2;       //!< Access rights for coprocessor 7
            uint32_t CP8:2;       //!< Access rights for coprocessor 8
            uint32_t CP9:2;       //!< Access rights for coprocessor 9
            uint32_t CP10:2;      //!< Access rights for coprocessor 10 (VFP)
            uint32_t CP11:2;      //!< Access rights for coprocessor 11 (VFP)
            uint32_t CP12:2;      //!< Access rights for coprocessor 12
            uint32_t CP13:2;      //!< Access rights for coprocessor 13
            uint32_t TRCDIS:1;    //!< Disable CP14 access to trace registers
            uint32_t reserved:1;
            uint32_t D32DIS:1;    //!< Disable use of D16-D31 of VFP
            uint32_t ASEDIS:1;    //!< Disable Advanced SIMD
        } bits;
        
        uint32_t value = 0;
        
        CPACR() = default;
        
        CPACR(uint32_t new_value)
        {
            value = new_value;
        }
    };
    
    // CP15 access macros
    #define MRC(cp, op1, crn, crm, op2) ({ \
        uint32_t _val; \
        asm volatile("mrc p" #cp ", " #op1 ", %0, c" #crn ", c" #crm ", " #op2 \
            : "=r" (_val)); \
        _val; \
    })
    
    #define MCR(cp, op1, val, crn, crm, op2) \
        asm volatile("mcr p" #cp ", " #op1 ", %0, c" #crn ", c" #crm ", " #op2 \
            : : "r" (val))
    
    // SCTLR operations
    static inline SCTLR getSCTLR()
    {
        return SCTLR(MRC(15, 0, 1, 0, 0));
    }
    
    static inline void setSCTLR(SCTLR sctlr)
    {
        MCR(15, 0, sctlr.value, 1, 0, 0);
        InstrSyncBarrier();
    }
    
    // ACTLR operations
    static inline ACTLR getACTLR()
    {
        return ACTLR(MRC(15, 0, 1, 0, 1));
    }
    
    static inline void setACTLR(ACTLR actlr)
    {
        MCR(15, 0, actlr.value, 1, 0, 1);
        InstrSyncBarrier();
    }
    
    // CPACR operations
    static inline CPACR getCPACR()
    {
        return CPACR(MRC(15, 0, 1, 0, 2));
    }
    
    static inline void setCPACR(CPACR cpacr)
    {
        MCR(15, 0, cpacr.value, 1, 0, 2);
        InstrSyncBarrier();
    }
    
    // MMU operations
    static inline void enableMMU()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.M = 1;
        setSCTLR(sctlr);
    }
    
    static inline void disableMMU()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.M = 0;
        setSCTLR(sctlr);
    }
    
    // Cache operations
    static inline void enableICache()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.I = 1;
        setSCTLR(sctlr);
    }
    
    static inline void disableICache()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.I = 0;
        setSCTLR(sctlr);
    }
    
    static inline void enableDCache()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.C = 1;
        setSCTLR(sctlr);
    }
    
    static inline void disableDCache()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.C = 0;
        setSCTLR(sctlr);
    }
    
    // Branch prediction
    static inline void enableBranchPrediction()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.Z = 1;
        setSCTLR(sctlr);
    }
    
    static inline void disableBranchPrediction()
    {
        SCTLR sctlr = getSCTLR();
        sctlr.bits.Z = 0;
        setSCTLR(sctlr);
    }
    
    // TLB operations
    static inline void invalidateTLB()
    {
        MCR(15, 0, 0, 8, 7, 0);  // TLBIALL
        DataSyncBarrier();
        InstrSyncBarrier();
    }
    
    // Other useful operations
    static inline uint32_t getMPIDR()
    {
        return MRC(15, 0, 0, 0, 5);  // Multiprocessor Affinity Register
    }
    
    static inline uint32_t getMIDR()
    {
        return MRC(15, 0, 0, 0, 0);  // Main ID Register
    }
}
