#include <iostream>
#include <stdio.h>

#include <Memory.h>
#include <CPU.h>

using namespace std;
using namespace SVC_A01;

int main()
{
    cout << "Initializing memory...";

    Memory* memory = new Memory();

    cout << "Ready" << endl;
    cout << "Memory size: " << (int) memory->c_MaxAddress << endl;
    cout << "Adding our default machine code program..." << endl;

    // Load register 0 with a value of 1
    memory->Write(1, 1);
    memory->Write(2, 1);

    // Load register 1 with a value of 2
    memory->Write(3, 2);
    memory->Write(4, 2);
    
    memory->Write(5, 3); // Add

    // Store to 12
    memory->Write(6, 5);
    memory->Write(7, 12);

    memory->Write(10, 4); // Beep   
    memory->Write(11, 0); // Halt

    cout << "Do you want to list the memory? [Y/y for yes, press any key for no] ";
    
    char answer = getchar();

    if (answer == '\n') {
        answer = 'N';
    }

    if (answer == 'y' || answer == 'Y') {
        for (byte currentAddress = 0; currentAddress < memory->c_MaxAddress; ++currentAddress) {
            cout << "Address [" << (int) currentAddress << "] = " << (int) memory->Read(currentAddress) << endl;
        }
    }

    cout << "Creating the CPU instance...";
    
    CPU* cpu = new CPU(memory);

    cout << "Ready" << endl;
    cout << "Starting..." << endl;

    cpu->Run();

    cout << "Complete" << endl;

    delete cpu, memory;
}