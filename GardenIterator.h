/**
 * @file GardenIterator.h
 * @brief Defines the GardenIterator class for traversing a collection of plants.
 */

#ifndef GARDENITERATOR_H
#define GARDENITERATOR_H

#include <vector>
#include "PlantIterator.h"

/**
 * @class GardenIterator
 * @brief Concrete iterator for traversing a collection of Plant pointers.
 */
class GardenIterator : public PlantIterator {
private:
    std::vector<Plant*> plants; /**< List of plants to iterate through. */
    size_t currentIndex;        /**< Index of the current plant. */

public:
    /**
     * @brief Constructs an iterator for the given list of plants.
     * @param list Vector of Plant pointers.
     */
    explicit GardenIterator(const std::vector<Plant*>& list);

    void next() override;
    Plant* current() const override;
    bool hasNext() const override;
};

#endif