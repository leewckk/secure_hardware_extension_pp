

#include "memory_update_protocol.h"
#include "she_bytes.h"


using namespace CryptoPP;

int main() {

    // Example usage
    SheBytes new_key = {0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};
    SheBytes auth_key = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
    SheBytes uid = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e};
    SecurityFlags flags(0x3F);

    MemoryUpdateInfo update_info(new_key, auth_key, 0x0A, 0x05, 0x12345678, uid, flags);
    MemoryUpdateProtocol protocol(update_info);

    SheBytes m1 = protocol.get_m1();
    SheBytes m2 = protocol.get_m2();
    SheBytes m3 = protocol.get_m3();
    SheBytes m4 = protocol.get_m4();
    SheBytes m5 = protocol.get_m5();

    // Print the results
    std::cout << "M1: " << m1 << std::endl;
    std::cout << "M2: " << m2 << std::endl;
    std::cout << "M3: " << m3 << std::endl;
    std::cout << "M4: " << m4 << std::endl;
    std::cout << "M5: " << m5 << std::endl;

    return 0;
}
