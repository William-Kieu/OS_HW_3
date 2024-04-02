#include <iostream>
#include <unordered_map> // including this library in order to implement the page/frame table


std::unordered_map<int, int> page_frame; // inits page frame table datastructure


void translation(int address) { //takes logical address and translates into physical address
	int page_number = (address >> 8) & 0xFF; // Extracting page number, shifts 8 bits to the right and performas a masking operation which will result as the first two hexadecimals of the input logical address
	int offset = address & 0xFF;            // Masks the bits with FF to retain offset

if (page_frame.find(page_number) == page_frame.end()) { // fault handling to see if page number is found in the page frame, if not it throws that there is an error
    std::cout << "Page fault occurred for logical address: 0x" << std::hex << address << std::endl;
    return; //breaks and exits the function
}

	int frame = page_frame[page_number]; // retrieves corresponding frame number from map
	int physical_address = (frame << 8) + offset; // LSL 8 bits to translate into physical address from indexed frame, adds offset from logical address

    std::cout << "Logical Address: 0x" << std::hex << address << std::endl;
    std::cout << "Page Number: 0x" << std::hex << page_number << std::endl; //first two hexadecimal of logical address
	std::cout << "Offset: 0x" << std::hex << offset << std::endl; // last two hexadecimal of logical address
    std::cout << "Physical Address: 0x" << std::hex << physical_address << std::endl << std::endl; // retrieved first two addresses from physical in addition to offset

}

int main() {

    page_frame[0x1D] = 0x1A; // Inits page frame mappings of physical frame numbers
    page_frame[0x2B] = 0x1F; // Inits page frame mappings of physical frame numbers
    page_frame[0x15] = 0x12; // Inits page frame mappings of physical frame numbers
    page_frame[0x25] = 0xA2; // Inits page frame mappings of physical frame numbers


    int logical_addresses[] = { 0x1D7F, 0x2BCD, 0x1578 , 0x44AD}; // 0x44AD will be out of range of the page frame table, since 0x44 is missing from the page_frame[] declarations

    for (int address : logical_addresses) {
        translation(address);
    }

    return 0;
}
