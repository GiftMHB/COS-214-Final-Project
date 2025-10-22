#ifndef TREE_H
#define TREE_H

#include "Plant.h"

/**
 * @file Tree.h
 * @brief Defines the Tree class derived from Plant
 * @class Tree
 * @brief Represents a tree plant type with specific attributes
 */
class Tree : public Plant {
    private:
        std::string treeType; 
        bool isEvergreen;
        double trunkDiameter;
        double height;

    public:
        /**
         * @brief Constructs a Tree with the given attributes.
         * @param treeType The type of tree.
         * @param height The tree's height.
         * @param isEvergreen Whether the tree is evergreen.
         */
        Tree(std::string treeType, double height, bool isEvergreen, double trunckDiameter);
        ~Tree();//more parameters will be added later

        double getHeight();
        std::string getDescription();
        double getTrunkDiameter();
        void prune();
};

#endif