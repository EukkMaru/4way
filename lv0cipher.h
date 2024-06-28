#ifndef LV0CIPHER_H
#define LV0CIPHER_H

#include "cipher.h"
#include "koreanhandler.h"

class LV0Cipher : public Cipher {
    // Level 0 cipher decomposes Korean characters and turn them into english alphabet ciphers
    public:
        virtual ~LV0Cipher() = default;
        std::string convert(const std::wstring& src);
        virtual std::string encrypt(const std::string& plaintext) override;
        virtual std::string decrypt(const std::string& ciphertext) override;
    private:

};

#endif // LV0CIPHER_H