/*
 * Names: Ashley Kaur, Ryan Vattuone, Joy Zhu
 * Emails: akaur3@scu.edu, rvattuone@scu.edu, jhzhu@scu.edu
 */
#include <bitset>
#include <stdexcept>
#include "rng.h"
#include "dna.h"
#include "life.h"

namespace csen79 {

// student to rewrite both
Life Life::cross(const Life& other) const {
    Life child;
    for(int c = 0; c < NChromo; c++) {
        for(size_t b = 0; b < dna[c].size(); b++) {
            bool use_this = (rand_int(0, 1) == 1);
            bool bit = use_this ? dna[c].getCode(static_cast<int>(b)) : other.dna.getCode(static_cast<int>(b));
            child.dna[c].setCode(static_cast<int>(b), bit);
        }
    }
    child.newLife();
    child.generation = std::max(this->generation, other.generation) + 1;
    return child;
}
const unsigned int Life::dnaMatch(int c, const DNA& other) const {
    
    return 0;
}

}   // namespace csen79
