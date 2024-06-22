#ifndef LV0CIPHER_H
#define LV0CIPHER_H

#include "cipher.h"
#include "koreanhandler.h"

class LV0Cipher : public Cipher {
    // Level 0 cipher decomposes Korean characters and turn them into english alphabet ciphers
    public:
        virtual ~LV0Cipher() = default;
        virtual std::string encrypt(const std::string& plaintext) override {
            // TODO
        }
        virtual std::string decrypt(const std::string& ciphertext) override {
            // TODO
        }
};

#endif // LV0CIPHER_H