#include <Memory.h>

namespace SVC_A01
{
    Memory::Memory() 
        :
        c_MaxAddress(255), // Max constant is 255 because this is an 8-bit CPU
        m_MemorySpace(new byte[c_MaxAddress])
    {
        clear()
    }

    Memory::~Memory()
    {
        if (m_MemorySpace != nullptr) {
            delete[] m_MemorySpace;
            m_MemorySpace = nullptr;
        }
    }

    const byte& Memory::Read(const bytes& p_Address)
    {
        return m_MemorySpace[p_Address];
    }

    void Memory::Write(const byte& p_Address, const byte& p_Value)
    {
        m_MemorySpace[p_Address] = p_Value;
    }
}