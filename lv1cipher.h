#ifndef LV1CIPHER_H
#define LV1CIPHER_H

#include "cipher.h"

class LV1Cipher : public Cipher {
    // Level 1 cipher takes english sourcetext as input and apply 4-way scoring cipher
    public:
        virtual ~LV1Cipher() = default;
        virtual std::string encrypt(const std::string& plaintext) override;
        virtual std::string decrypt(const std::string& ciphertext) override;
    private:

};

#endif // LV1CIPHER_H