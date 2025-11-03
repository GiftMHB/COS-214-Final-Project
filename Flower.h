#ifndef FLOWER_H
#define FLOWER_H

#include <string>
#include "Plant.h"

/**
 * @file Flower.h
 * @brief Defines the Flower class derived from Plant, representing a flowering plant
 * @class Flower
 * @brief Represents a flower plant with color, bloom season, petal count, and fragrance attributes
 */
class Flower : public Plant {
    private:
        std::string color;        
        std::string bloomSeason;
        int petalCount;
        bool fragrance;

    public:
        /**
         * @brief Constructs a new Flower object with the given attributes.
         * @param color The color of the flower.
         * @param bloomSeason The blooming season of the flower.
         * @param petalCount The number of petals.
         * @param fragrance Whether the flower is fragrant.
         */
        Flower(PlantInfo& info,string color,string bloomSeason,int petalCount,bool fragrance);
        ~Flower();

        std::string getColor();
        std::string getBloomSeason();
        int getPetalCount();
        bool hasFragrance();
        std::string getDescription()const override;;
};

#endif