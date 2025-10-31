/*
 * Names: Ashley Kaur, Ryan Vattuone, Joy Zhu
 * Emails: akaur3@scu.edu, rvattuone@scu.edu, jhzhu@scu.edu
 */
#include <bitset>
#include "rng.h"
#include "dna.h"

namespace csen79 {

// Student to implement all of these member functions
DNA::DNA(unsigned int v) {
    codes = static_cast<Gene>(v) & static_cast<Gene>(mask);
}

bool DNA::getCode(const int i) const {
    if (i < 0 || i >= nCode) return false;    // Checking if the bit position is within the valid range

    /* Shifting right and masking with 1U to isolate only the last bit
     * bit i = 1 --> result is 1, true
     * bit i = 0 --< result is 0, false
    */
    return (codes >> i) & 1U;    // using unsigned short
}

void DNA::setCode(const int i, bool v) {
    if (i < 0 || i >= nCode) return;    // Checking if the bit position is within the valid range

    if (v) {    // if v is true
        // Creating a mask with 1 in the ith position + ORing it with codes to only set bit i to 1
        codes |= (1U << i);
    }
    else {    // if v is false
        // Creating a mask with 1 in the ith position + ANDing the inverted mask with codes to only set that bit to 0
        codes &= ~(1U << i);
    }
    return;
}

size_t DNA::size() const {
    return nCode;
}

size_t DNA::count() const {
    size_t cnt = 0;
    unsigned int val = 0;
    val = codes;
    while (val != 0) {    // Traversing while val is valid
        if (val & 1U) {   // Checking if the lowest bit is 1
            ++cnt;
        }
        val >>= 1;        // Shifting val right by 1 to move on to the next bit
    }
    return cnt;
}
unsigned int DNA::matchDNA(const DNA& other) const {
    unsigned int cnt = 0;
    unsigned int sameBits = 0;
    /* codes ^ other.codes: XORing the bits for codes and other.codes, giving 1 if the bits are different and 0 if they match
     * ~(codes ^ other.codes): Now we'll get 1 where the bits match and 0 where they're different
     * Using bitwise AND to ensure we only look at the lower 16 bits since DNA only uses 16 codes (remember nCode is 16)
    */
    sameBits = ~(codes ^ other.codes) & mask;

    while (sameBits != 0) {
        if (sameBits & 1U) {    // Checking if the LSB is 1
            ++cnt;
        }
        sameBits >>= 1;    // Shifting sameBits right by 1 to test the next bit
    }
    return cnt;
}

}   // namespace csen79
