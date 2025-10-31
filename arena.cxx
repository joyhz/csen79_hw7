/*
 * Names: Ashley Kaur, Ryan Vattuone, Joy Zhu
 * Emails: akaur3@scu.edu, rvattuone@scu.edu, jhzhu@scu.edu
 */
#include <bitset>
#include <vector>
#include <random>
#include <stdexcept>
#include "rng.h"
#include "dna.h"
#include "life.h"
#include "select.h"
#include "arena.h"

namespace csen79 {

/*
 * There are two way to keep scores.  We chose to do it individually.
 * Obviously, we could have picked random group of individuals and have them
 * "Compete" as a group.
 */
void Arena::compete() {
    for (auto& individual : population)
        for (int i = 0; i < EVENTPERROUND; i++) {
            competition.init();
            competition.play(individual); // Assuming play method modifies individual's score
        }
}

/*
 * Run after a round of competition, which can also be a "generation."
 * We select, arbitrarily, the upper half to preserve to the next generation.
 * Then we populate the rest with the offsprings of those winners.
 */
void Arena::evolve() {
    std::vector<Life> winners;
    std::vector<Life> nextGen;
    double avgScore = 0;
    winners.reserve(NPop);
    nextGen.reserve(NPop);
    
    // Select individuals with above-average scores
    long sumScore = 0;
    for (auto& individual : population)
        sumScore += individual.getScore();
    avgScore = static_cast<double>(sumScore) / static_cast<double>(NPop);   // average score
    for (auto& individual : population)
        if (static_cast<double>(individual.getScore()) >= avgScore)
            winners.push_back(individual);  // yes, make a copy

    // If no winners, keep at least one random individual
    if (winners.empty()) {
        winners.push_back(population[rand_int(0, NPop - 1)]);
    }
    
    // Build next generation --> keep winners, then fill up to NPop with offspring
    nextGen.reserve(NPop);

    // Add back winners
    for (size_t i = 0; i < winners.size() && nextGen.size() < static_cast<size_t>(NPop); ++i) {
        nextGen.push_back(winners[i]);
    }

    // Fill rest with offsprings from winners
    static constexpr int MUTATION_PER_THOUS = 10; // 10/1000 = 1% chance of random mutation (new random individual)
    while (nextGen.size() < static_cast<size_t>(NPop)) {
        int p1 = rand_int(0, static_cast<int>(winners.size()) - 1);
        int p2 = rand_int(0, static_cast<int>(winners.size()) - 1);
        Life child = winners[p1].cross(winners[p2]);

        // Mutation as completely new random life with small probability
        if (rand_int(0, 999) < MUTATION_PER_THOUS) {
            child = Life(); // random new individual
        }
        nextGen.push_back(std::move(child));
    }

    // Replace population with next generation and reset scores
    population.swap(nextGen);

    for (auto& individual : population) {
        individual.newLife();
    }
}

double Arena::matured() {
   double matches{0.0};
   for (auto& individual : population) {
         matches += competition.matchRatio(individual);
   }
    matches /= NPop;
    return matches;
}

}   // namespace csen79
