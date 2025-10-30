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
    if (i < 0 || i >= nCode) return false;
    return (static_cast<unsigned int>(codes) >> i) & 1U;
}

void DNA::setCode(const int i, bool v) {

}

size_t DNA::size() const {

    return 0;
}

size_t DNA::count() const {

    return 0;
}
unsigned int DNA::matchDNA(const DNA& other) const {
    
    return 0;
}

}   // namespace csen79
