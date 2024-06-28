#include "lv0cipher.h"

const std::map<wchar_t, char> conversionTable = {
    {0x3131, 'R'},
    // TODO
};

bool isKorean(const wchar_t& c) {
    // Korean should be already converted to compatibility jamo
    return (c >= 0x3130 && c <= 0x318F);
}

bool isEnglish(const wchar_t& c) {
    return (c >= 0x0041 && c <= 0x005A) || (c >= 0x0061 && c <= 0x007A);
}

bool isCoherent(const std::wstring& src) {
    // <algorithm> is included in koreanhandler.h
    bool isKor = std::any_of(src.begin(), src.end(), isKorean);
    bool isEng = std::any_of(src.begin(), src.end(), isEnglish);
    return !(isKor && isEng);
}

std::vector<std::wstring> wsplit(const std::wstring& src) {
    std::vector<std::wstring> tokens;
    std::wstring token;

    std::wstringstream stream(src);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string toLowerString(const std::string& src) {
    std::string dst = src;
    std::transform(dst.begin(), dst.end(), dst.begin(), ::tolower);
    return dst;
}

std::string LV0Cipher::convert(const std::wstring& src) {
    std::vector<std::wstring> words = wsplit(src);
    for (const std::wstring& word : words) {
        if (!isCoherent(word)) {
            std::string culprit;
            culprit.assign(word.begin(), word.end());
            throw std::invalid_argument("LV0_convert: a word cannot have both Korean and English characters at the same time, word: " + culprit);
        }        
    }
    // Above check discards whitespaces, we cannot retrieve original character
    for (const wchar_t& c : src) {
        if (!isKorean(c)) continue;

    }
}

std::string LV0Cipher::encrypt(const std::string& plaintext) {
    


}

std::string LV0Cipher::decrypt(const std::string& ciphertext) {
    // TODO
}