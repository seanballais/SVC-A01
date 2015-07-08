#ifndef CPU_MEMORY
#define CPU_MEMORY

namespace SVC_A01
{
    typedef unsigned char byte;

    class Memory
    {
        public:
            const byte c_MaxAddress;

        private:
            byte* m_MemorySpace;

        public:
            Memory();
            ~Memory();
            void Clear();
            const byte& Read(const byte& p_Address);
            void Write(const byte& p_Address, const byte& p_Value);
    };
}