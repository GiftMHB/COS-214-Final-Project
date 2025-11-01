#ifndef CARE_STRATEGY_H
#define CARE_STRATEGY_H
#include <string>

class Plant;

class CareStrategy {
public:
    virtual ~CareStrategy() = default;
    virtual void applyCare(Plant* plant) = 0;
    virtual std::string getStrategyName() const = 0;
};

#endif