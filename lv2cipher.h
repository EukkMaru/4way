#ifndef LV2CIPHER_H
#define LV2CIPHER_H

#include "cipher.h"

class LV2Cipher : public Cipher {
    // Level 2 cipher uses key to add a layer of encryption
    public:
        virtual ~LV2Cipher() = default;
        virtual std::string encrypt(const std::string& plaintext) override;
        virtual std::string decrypt(const std::string& ciphertext) override;
    private:
        uint32_t generateKey(const std::string& plaintext);
        uint32_t calculateKey(const std::string& ciphertext);
};

#endif // LV2CIPHER_H