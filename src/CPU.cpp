#include <iostream>
#include <CPU.h>

namespace SVC_A01
{
    CPU::CPU(Memory* p_Memory)
        :
        c_ReservedAddress(0),
        c_BaseAddress(1),
        c_AddressCeiling(253),
        m_ProgramCounter(c_BaseAddress),
        m_Register0(0),
        m_Register1(0),
        m_OverflowError(false),
        m_UnderflowError(false),
        m_SignedMode(false),
        m_Memory(p_Memory),
        m_Halt(false)
    {
    }

    CPU::~CPU()
    {
        m_Memory = nullptr;
    }

    void CPU::Reset()
    {
        m_OverflowError = false;
        m_UnderflowError = false;
        m_SignedMode = false;
        m_Halt = false;
        m_ProgramCounter = c_BaseAddress;
    }

    const byte CPU::Fetch()
    {
        byte l_opCode = 0;
        l_opCode = m_Memory->Read(m_ProgramCounter);
        
        ++m_ProgramCounter;

        if (m_ProgramCounter > c_AddressCeiling) {
            Halt();
        }

        return l_opCode;
    }

    void CPU::Halt()
    {
        m_Halt = true;
    }

    void CPU::Add()
    {
        m_Register0 = m_Register0 + m_Register1;
    }

    void CPU::Beep()
    {
        std::cout << "\a";
    }

    void CPU::Store()
    {
        m_Register1 = m_Memory->Read(m_ProgramCounter);
        ++m_ProgramCounter; // Skip the memory location data
        m_Memory->Write(m_Register1, m_Register0);
    }

    void CPU::Print()
    {
        m_Register1 = m_Memory->Read(m_ProgramCounter);
        ++m_ProgramCounter;

        m_Register0 = m_Memory->Read(m_Register1);

        std::cout << (int) m_Register0 << std::endl;
    }

    void CPU::Decode(const byte& p_OpCode)
    {
        if (m_Halt) return;

        switch (p_OpCode) {
            case 0:
                Halt();
                break;
            case 1:
                m_Register0 = m_Memory->Read(m_ProgramCounter);
                ++m_ProgramCounter; // Skip past the data
            case 2:
                m_Register1 = m_Memory->Read(m_ProgramCounter);
                ++m_ProgramCounter; // Skip past the data
            case 3:
                Add();
                break;
            case 4:
                Beep();
                break;
            case 5:
                Store();
                break;
            case 6:
                Print();
                break;
        }
    }

    void CPU::Run()
    {
        // Keep going while we don't see a HALT
        while (!m_Halt) {
            m_Memory->Write(c_ReservedAddress, Fetch());
            Decode(m_Memory->Read(c_ReservedAddress));
        }
    }
}