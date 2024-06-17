

#ifndef SHE_KEY_SLOT_H
#define SHE_KEY_SLOT_H


#include "she_integer.h"
#include "key_slots_base.h"

class SheKeySlot : public SheInteger {
public:
    SheKeySlot(size_t bit_size) : SheInteger(bit_size) {}

    inline void set(void* obj, KeySlotsBase::Slot value) {
        SheInteger::set(obj, static_cast<int>(value));
    }
};

#endif 