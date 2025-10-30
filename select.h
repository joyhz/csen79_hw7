/*
 * Names: Ashley Kaur, Ryan Vattuone, Joy Zhu
 * Emails: akaur3@scu.edu, rvattuone@scu.edu, jhzhu@scu.edu
 */
#ifndef SELECT_H
#define SELECT_H

namespace csen79 {

class Select {
    DNA favors[Life::NChromo];
    int maxMatches[Life::NChromo];
public:
    Select();
    void init() { /* Initialize the game event */ }
    void play(Life& player);
    double matchRatio(const Life& player);
};

} // namespace csen79

#endif // SELECT_H
