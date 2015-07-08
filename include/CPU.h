#ifndef CPU_PROCESSOR
#define CPU_PROCESSOR

#include "Memory.h"

namespace SVC_A01
{
    class CPU
    {
        public:
            const byte c_ReservedAddress;
            const byte c_BaseAddress;
            const byte c_AddressCeiling;

        private:
            byte m_ProgramCounter;
            byte m_Register0;
            byte m_Register1;

            bool m_OverflowError;
            bool m_UnderflowError;
            bool m_SignedMode;
            bool m_Halt;

            Memory* m_Memory;

            const byte Fetch();

            void Decode(const byte& p_OpCode);
            void Halt();
            void Add();
            void Beep();
            void Store();
            void Print();

        public:
            CPU(Memory* p_Memory);
            ~CPU();

            void Reset();
            void Run();
    };
}

#endif