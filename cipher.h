#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <cstdint>
#include <sstream>
#include <stdexcept>
#include <map>

class Cipher {
    public:
        virtual ~Cipher() = default;
        virtual std::string encrypt(const std::string& plaintext) = 0;
        virtual std::string decrypt(const std::string& ciphertext) = 0;
};

#endif // CIPHER_H