#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <cstdint>

class Cipher {
    public:
        virtual ~Cipher() = default;
        virtual std::string encrypt(const std::string& plaintext) = 0;
        virtual std::string decrypt(const std::string& ciphertext) = 0;
};

#endif // CIPHER_H