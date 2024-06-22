#include "koreanhandler.h"

// Define constants for Korean unicode character blocks:
// 1100~11FF, 3130~318F (Jamo)
// AC00~D7AF (Syllables)
#define JAMO_START 0x1100
#define JAMO_END 0x11FF
#define JAMO_START_COMPATIBILITY 0x3130
#define JAMO_END_COMPATIBILITY 0x318F
#define SYLLABLE_START 0xAC00
#define SYLLABLE_END 0xD7AF
#define VOWEL_START 0x314F
#define VOWEL_END 0x3163
#define CONS_START 0x3131
#define CONS_END 0x314E

const std::map<wchar_t, wchar_t> topMap = {
    {0x1100, 0x3131}, //ㄱ
    {0x1101, 0x3132}, //ㄲ
    {0x1102, 0x3134}, //ㄴ
    {0x1103, 0x3137}, //ㄷ
    {0x1104, 0x3138}, //ㄸ
    {0x1105, 0x3139}, //ㄹ
    {0x1106, 0x3141}, //ㅁ
    {0x1107, 0x3142}, //ㅂ
    {0x1108, 0x3143}, //ㅃ
    {0x1109, 0x3145}, //ㅅ
    {0x110A, 0x3146}, //ㅆ
    {0x110B, 0x3147}, //ㅇ
    {0x110C, 0x3148}, //ㅈ
    {0x110D, 0x3149}, //ㅉ
    {0x110E, 0x314A}, //ㅊ
    {0x110F, 0x314B}, //ㅋ
    {0x1110, 0x314C}, //ㅌ
    {0x1111, 0x314D}, //ㅍ
    {0x1112, 0x314E}, //ㅎ
};
const std::map<wchar_t, wchar_t> midMap = {
    {0x1161, 0x314F}, //ㅏ
    {0x1162, 0x3150}, //ㅐ
    {0x1163, 0x3151}, //ㅑ
    {0x1164, 0x3152}, //ㅒ
    {0x1165, 0x3153}, //ㅓ
    {0x1166, 0x3154}, //ㅔ
    {0x1167, 0x3155}, //ㅕ
    {0x1168, 0x3156}, //ㅖ
    {0x1169, 0x3157}, //ㅗ
    {0x116A, 0x3158}, //ㅘ
    {0x116B, 0x3159}, //ㅙ
    {0x116C, 0x315A}, //ㅚ
    {0x116D, 0x315B}, //ㅛ
    {0x116E, 0x315C}, //ㅜ
    {0x116F, 0x315D}, //ㅝ
    {0x1170, 0x315E}, //ㅞ
    {0x1171, 0x315F}, //ㅟ
    {0x1172, 0x3160}, //ㅠ
    {0x1173, 0x3161}, //ㅡ
    {0x1174, 0x3162}, //ㅢ
    {0x1175, 0x3163}, //ㅣ
};
const std::map<wchar_t, wchar_t> bottomMap = {
    {0x11A8, 0x3131}, //ㄱ
    {0x11A9, 0x3132}, //ㄲ
    {0x11AA, 0x3133}, //ㄳ
    {0x11AB, 0x3134}, //ㄴ
    {0x11AC, 0x3135}, //ㄵ
    {0x11AD, 0x3136}, //ㄶ
    {0x11AE, 0x3137}, //ㄷ
    {0x11AF, 0x3139}, //ㄹ
    {0x11B0, 0x313A}, //ㄺ
    {0x11B1, 0x313B}, //ㄻ
    {0x11B2, 0x313C}, //ㄼ
    {0x11B3, 0x313D}, //ㄽ
    {0x11B4, 0x313E}, //ㄾ
    {0x11B5, 0x313F}, //ㄿ
    {0x11B6, 0x3140}, //ㅀ
    {0x11B7, 0x3141}, //ㅁ
    {0x11B8, 0x3142}, //ㅂ
    {0x11B9, 0x3144}, //ㅄ
    {0x11BA, 0x3145}, //ㅅ
    {0x11BB, 0x3146}, //ㅆ
    {0x11BC, 0x3147}, //ㅇ
    {0x11BD, 0x3148}, //ㅈ
    {0x11BE, 0x314A}, //ㅊ
    {0x11BF, 0x314B}, //ㅋ
    {0x11C0, 0x314C}, //ㅌ
    {0x11C1, 0x314D}, //ㅍ
    {0x11C2, 0x314E}, //ㅎ
};

const std::map<wchar_t, std::pair<wchar_t, wchar_t>> splitMap = {
    {0x3132, {0x3131, 0x3131}}, //ㄲ
    {0x3133, {0x3131, 0x3145}}, //ㄳ
    {0x3135, {0x3134, 0x3148}}, //ㄵ
    {0x3136, {0x3134, 0x314E}}, //ㄶ
    {0x3138, {0x3137, 0x3137}}, //ㄸ
    {0x313A, {0x3139, 0x3131}}, //ㄺ
    {0x313B, {0x3139, 0x3141}}, //ㄻ
    {0x313C, {0x3139, 0x3142}}, //ㄼ
    {0x313D, {0x3139, 0x3145}}, //ㄽ
    {0x313E, {0x3139, 0x314C}}, //ㄾ
    {0x313F, {0x3139, 0x314D}}, //ㄿ
    {0x3140, {0x3139, 0x314E}}, //ㅀ
    {0x3143, {0x3142, 0x3142}}, //ㅃ
    {0x3144, {0x3142, 0x3145}}, //ㅄ
    {0x3146, {0x3145, 0x3145}}, //ㅆ
    {0x3149, {0x3148, 0x3148}}, //ㅉ
    
    {0x3158, {0x3157, 0x314F}}, //ㅘ
    {0x3159, {0x3157, 0x3150}}, //ㅙ
    {0x315A, {0x3157, 0x3163}}, //ㅚ
    {0x315D, {0x315C, 0x3153}}, //ㅝ
    {0x315E, {0x315C, 0x3154}}, //ㅞ
    {0x315F, {0x315C, 0x3163}}, //ㅟ
    {0x3162, {0x3161, 0x3163}}, //ㅢ
};

template<typename T, typename U> T findByVal(const std::map<T, U> m, const U& value) {
    // Use in try catch
    for (const auto& pair : m) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    throw std::runtime_error("Not found");
}

int getIdxByVal(const std::map<wchar_t, wchar_t>& m, const wchar_t& value) {
    int idx = 0;
    for (const auto& pair : m) {
        if (pair.second == value) {
            return idx;
        }
        idx++;
    }
    throw std::runtime_error("Not found");
}


bool isJamo(const wchar_t& src) {
    return (src >= JAMO_START && src <= JAMO_END);
}

bool isCompatibilityJamo(const wchar_t& src) {
    return (src >= JAMO_START_COMPATIBILITY && src <= JAMO_END_COMPATIBILITY);
}

bool isSyllable(const wchar_t& src) {
    return (src >= SYLLABLE_START && src <= SYLLABLE_END);
}

bool isVowel(const wchar_t& src) {
    // Only works for compatibility jamo
    return (src >= VOWEL_START && src <= VOWEL_END);
}

wchar_t convertJamo(const wchar_t& jamo) {
    // * Convert normal jamo to compatibility jamo
    if (jamo >= 0x1100 && jamo <= 0x1112) {
        return topMap.at(jamo);
    } else if (jamo >= 0x1161 && jamo <= 0x1175) {
        return midMap.at(jamo);
    } else if (jamo >= 0x11A8 && jamo <= 0x11C2) {
        return bottomMap.at(jamo);
    } else {
        return jamo;
    }
}

std::pair<wchar_t, wchar_t> splitDouble(wchar_t src) {
    // ! Src should have already been converted to compatibility jamo
    if (!isCompatibilityJamo(src)) src = convertJamo(src);
    if (!isCompatibilityJamo(src)) throw std::invalid_argument("splitDouble: src is not a compatibility jamo");

    return splitMap.at(src);
}

wchar_t combineDouble(const std::pair<wchar_t, wchar_t>& src) {
    wchar_t result;
    try {
        result = findByVal(splitMap, src);
    } catch (const std::exception& e) {
        throw std::invalid_argument("combineDouble: src is not a double jamo, src: " + std::to_string(src.first) + " " + std::to_string(src.second));
    }

    return result;
}

wchar_t construct2(const std::pair<wchar_t, wchar_t>& src) {
    if (src.first < CONS_START || src.first > CONS_END || src.second < VOWEL_START || src.second > VOWEL_END) {
        throw std::invalid_argument("construct2: src is not a double component syllable");
    }
    int idx = getIdxByVal(topMap, src.first) * 588 + getIdxByVal(midMap, src.second) * 28;
    return SYLLABLE_START + static_cast<wchar_t>(idx);
}

wchar_t construct(const std::vector<wchar_t>& src) {
    if (src.size() != 2 && src.size() != 3) {
        throw std::invalid_argument("construct3: src is not a double or triple component syllable");
    }
    int idx = getIdxByVal(topMap, src[0]) * 588 + getIdxByVal(midMap, src[1]) * 28;
    return SYLLABLE_START + static_cast<wchar_t>(src.size() == 3 ? idx + getIdxByVal(bottomMap, src[2]) + 1 : idx);
}

std::vector<wchar_t> decompose(const wchar_t& src) {
    // If src is jamo and not a syllable, there is nothing to decompose
    if (isCompatibilityJamo(src)) {
        return std::vector<wchar_t>{src};
    } else if (isJamo(src)) { // However normal jamo must be converted to compatibility jamo
        return std::vector<wchar_t>{convertJamo(src)};
    }

    // If src is not a jamo nor a syllable
    if (!isSyllable(src)) {
        return std::vector<wchar_t>{src};
    }

    // If src is a syllable
    wchar_t relativeIdx = src - SYLLABLE_START; // 0xAC00 - 0xD7A3 to 0x0000 - 0x2BA3
    wchar_t topIdx = relativeIdx / 588;
    wchar_t midIdx = (relativeIdx % 588) / 28;
    wchar_t botIdx = ((relativeIdx % 588) % 28) - 1;

    std::vector<wchar_t> result = { topMap.at(topIdx + 0x1100) };
    wchar_t v; // ! 우짤티비
    v = midIdx + 0x1161;
    if (splitMap.find(convertJamo(v)) != splitMap.end()) {
        result.push_back(splitDouble(v).first);
        result.push_back(splitDouble(v).second);
    } else {
        result.push_back(midMap.at(v));
    }
    if (botIdx < bottomMap.size()) result.push_back(bottomMap.at(botIdx + 0x11A8));

    return result;
}

wchar_t compose(const std::vector<wchar_t>& src) {
    // if src is empty
    if (src.empty()) throw std::invalid_argument("compose: src is empty");
    // if src doesn't start with consonant, it should be a single vowel char
    if (src[0] < CONS_START || src[0] > CONS_END) {
        switch (src.size()) {
            case 1:
                return src[0];
            case 2:
                return combineDouble(std::make_pair(src[0], src[1]));
            default:
                throw std::invalid_argument("compose: invalid type of src");
        }
    }
    // if src starts with consonant, it's either a single consonant char or a full syllable
    // single consonant char can only be up to 2 components, but a full syllable can also be made of 2 components
    // if length is 1 it is 100% consonant, if length is 2 we have to check
    if (src.size() == 1) {
        return src[0];
    } else if (src.size() == 2) {
        //if src[1] is a vowel, it's a full syllable else it's a single consonant
        if (src[1] >= VOWEL_START && src[1] <= VOWEL_END) {
            // There should be single consonant + single vowel
            return construct2(std::make_pair(src[0], src[1]));
        } else {
            return combineDouble(std::make_pair(src[0], src[1]));
        }
    } else {
        // if length is > 2 it's always a full syllable
        // It can be top+mid OR top+mid+bot, src's length is unknown
        // We have to iterate through src and divide them into top, mid, bot (if exists)
        std::vector<wchar_t> top, mid, bot;
        std::vector<wchar_t>::const_iterator it = src.begin();
        bool reachedMid = false; // Set to true when mid is found
        while (it != src.end()) {
            if (*it >= CONS_START && *it <= CONS_END) {
                reachedMid ? bot.push_back(*it) : top.push_back(*it);
            } else if (*it >= VOWEL_START && *it <= VOWEL_END) {
                mid.push_back(*it);
                reachedMid = true;
            } else {
                throw std::invalid_argument("compose: invalid type of src");
            }
            it++;
        }
        if (top.size() > 2 || mid.size() > 2 || bot.size() > 2) {
            throw std::invalid_argument("compose: too many components in src, top: " + std::to_string(top.size()) + ", mid: " + std::to_string(mid.size()) + ", bot: " + std::to_string(bot.size()));
        }

        wchar_t topL = top.size() == 1 ? top[0] : combineDouble(std::make_pair(top[0], top[1]));
        wchar_t midL = mid.size() == 1 ? mid[0] : combineDouble(std::make_pair(mid[0], mid[1]));
        int botL = [&bot]() -> int {
            if (bot.empty()) return -1;
            return bot.size() == 1 ? bot[0] : combineDouble(std::make_pair(bot[0], bot[1]));
        }();
        
        std::vector<wchar_t> arg = [&]() -> std::vector<wchar_t> {
        return (botL != -1) ? std::vector<wchar_t>{topL, midL, static_cast<wchar_t>(botL)}
                            : std::vector<wchar_t>{topL, midL};
        }();
        return construct(arg);
    }
}

/*

! Test Code !

#include <iostream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>

int main() {
    using namespace std;
    wstring test_orig = L"동해물과 백두산이 마르고 닳도록 하나님이 보우하사 우리나라 만세";
    for (const wchar_t& c : test_orig) {
        cout << c << " ";
    }
    cout << endl << endl;
    
    vector<vector<wchar_t>> test;
    for (const wchar_t& c : test_orig) {
        test.push_back(decompose(c));
    }

    for (const vector<wchar_t>& c : test) {
        for (const wchar_t& d : c) {
            cout << d << " ";
        }
    }

    cout << endl << endl;

    wstring result;
    for (const vector<wchar_t>& c : test) {
        result += compose(c);
    }
    
    for (const wchar_t& c : result) {
        cout << c << " ";
    }

    cout << endl << "Comparison: " << ((test_orig == result) ? "true" : "false") << endl;

    return 0;
}

*/