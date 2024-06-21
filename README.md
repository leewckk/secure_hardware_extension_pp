

## Secure Hardware Extension



This is a implementation of AUTOSAR Secure Hardware Extension.

Features:

* Generate M1 ~ M5 from some key values
* Parse M1 M2 Memory update protocol messages in order to get the update information.



## Environment



* linux 

* crypto++





## Examples



````go


#include "autosar_key_slots.h"
#include "memory_update_info.h"
#include "memory_update_messages.h"
#include "memory_update_protocol.h"
#include "secure_flags.h"
#include "she_bytes.h"
#include "she_constants.h"
#include <crypto++/cryptlib.h>


using namespace CryptoPP;


class SecureConfig {
public :

    SecureConfig(
        const AutoSarkeySlots new_key_slot, 
        const SheBytes new_key,
        const AutoSarkeySlots auth_key_id,
        const SheBytes auth_key,
        const SheBytes uid = SheBytes(15, 0x00),
        const SecurityFlags flags = SecurityFlags(0x00),
        const int counter = 1
    ): 
    new_key_slot_(new_key_slot),
    new_key_(new_key),
    auth_key_id_(auth_key_id),
    auth_key_(auth_key),
    uid_(uid),
    flags_(flags),
    counter_(counter)
    {}


    // Getter functions
    AutoSarkeySlots get_new_key_slot() const {
        return new_key_slot_;
    }

    SheBytes get_new_key() const {
        return new_key_;
    }

    AutoSarkeySlots get_auth_key_id() const {
        return auth_key_id_;
    }

    SheBytes get_auth_key() const {
        return auth_key_;
    }

    SheBytes get_uid() const {
        return uid_;
    }

    SecurityFlags get_flags() const {
        return flags_;
    }

    int get_counter() const {
        return counter_;
    }

protected:
    AutoSarkeySlots new_key_slot_;
    SheBytes new_key_;
    AutoSarkeySlots auth_key_id_;
    SheBytes auth_key_;
    SheBytes uid_;
    SecurityFlags flags_;
    int counter_;

};


int main(int argc, char** argv) {

    std::vector<SecureConfig> secureConfigList;

    secureConfigList.push_back(SecureConfig(MASTER_ECU_KEY, SheBytes(16, 0x00), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(BOOT_MAC, SheBytes(16, 0xCC), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(BOOT_MAC_KEY, SheBytes(16, 0xCC), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(KEY_1, SheBytes(16, 0x11), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(KEY_2, SheBytes(16, 0x22), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(KEY_3, SheBytes(16, 0x33), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(KEY_4, SheBytes(16, 0x44), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(KEY_5, SheBytes(16, 0x55), MASTER_ECU_KEY, SheBytes(16, 0x00)));
    secureConfigList.push_back(SecureConfig(KEY_6, SheBytes(16, 0x66), MASTER_ECU_KEY, SheBytes(16, 0x00)));


    std::cout<<"KEY_UPDATE_ENC_C: "<< SheConstants::KEY_UPDATE_ENC_C<<std::endl;
    std::cout<<"KEY_UPDATE_MAC_C: "<< SheConstants::KEY_UPDATE_MAC_C<<std::endl;

    for(SecureConfig config: secureConfigList){
        MemoryUpdateInfo info(config.get_new_key(), 
                                config.get_auth_key(), 
                                config.get_new_key_slot(), 
                                config.get_auth_key_id(), 
                                config.get_counter(), 
                                config.get_uid(), 
                                config.get_flags());
        
        MemoryUpdateProtocol protocol(info);

        std::cout<<"key slot: " << config.get_new_key_slot()<< std::endl;

        std::cout<< "M1: " << protocol.get_m1() << std::endl;
        std::cout<< "M2: " << protocol.get_m2() << std::endl;
        std::cout<< "M3: " << protocol.get_m3() << std::endl;
        std::cout<< "M4: " << protocol.get_m4() << std::endl;
        std::cout<< "M5: " << protocol.get_m5() << std::endl;

        std::cout<<"\r\n";

        MemoryUpdateInfo memoryUpdateInfo = MemoryUpdateProtocol::decrypt_using_messages(MemoryUpdateMessages(config.get_auth_key(), protocol.get_m1(), protocol.get_m2()));
        std::cout<<"memory update info: \r\n"<<memoryUpdateInfo<<std::endl;

        std::cout<<"\r\n\r\n\r\n";
    }

    return 0;
}
````







