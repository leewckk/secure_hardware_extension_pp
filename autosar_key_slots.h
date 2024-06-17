
// This file contains AUTOSAR identification of memory slots.

#ifndef AUTOSAR_KEY_SLOTS_H
#define AUTOSAR_KEY_SLOTS_H

#include "key_slots_base.h" // 假设你有一个类似于 KeySlotsBase 的基类

class AutosarKeySlotsBase : public KeySlotsBase {
public:
    /**
     * Enum holds memory slot identification based on
     * `Specification of Secure Hardware Extensions, AUTOSAR FO R19-11`.
     * https://www.autosar.org/fileadmin/user_upload/standards/foundation/19-11/AUTOSAR_TR_SecureHardwareExtensions.pdf
     */

    enum Slot {
        SECRET_KEY = 0x0,
        MASTER_ECU_KEY = 0x1,
        BOOT_MAC_KEY = 0x2,
        BOOT_MAC = 0x3,
        KEY_1 = 0x4,
        KEY_2 = 0x5,
        KEY_3 = 0x6,
        KEY_4 = 0x7,
        KEY_5 = 0x8,
        KEY_6 = 0x9,
        KEY_7 = 0xA,
        KEY_8 = 0xB,
        KEY_9 = 0xC,
        KEY_10 = 0xD,
        RAM_KEY = 0xE
    };
};

#endif // AUTOSAR_KEY_SLOTS_H
