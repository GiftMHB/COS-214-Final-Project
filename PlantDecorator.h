#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

#include "Plant.h"
#include <string>

// Abstract Decorator
class PlantDecorator : public Plant {
protected:
    Plant* decoratedPlant;

public:
    PlantDecorator(Plant* plant);
    virtual ~PlantDecorator();
    
    // Override Plant methods to delegate to decorated plant
    virtual std::string getDescription() const override;
    virtual double getPrice() const override;
    virtual void water(int amount) override;
    virtual void fertilize(int amount) override;
    virtual void grow() override;
};

// Concrete Decorators
class PottedPlant : public PlantDecorator {
private:
    std::string potType;
    std::string potSize;
    double potPrice;

public:
    PottedPlant(Plant* plant, const std::string& type, const std::string& size);
    
    std::string getDescription() const override;
    double getPrice() const override;
    
    std::string getPotType() const;
    void repot(const std::string& newType, const std::string& newSize);
};

class LabeledPlant : public PlantDecorator {
private:
    std::string labelText;
    std::string careInstructions;
    double labelPrice;

public:
    LabeledPlant(Plant* plant, const std::string& text, const std::string& care);
    
    std::string getDescription() const override;
    double getPrice() const override;
    
    std::string getCareInstructions() const;
};

class GiftWrappedPlant : public PlantDecorator {
private:
    std::string wrappingStyle;
    std::string ribbonColor;
    std::string giftMessage;
    double wrappingPrice;

public:
    GiftWrappedPlant(Plant* plant, const std::string& style, const std::string& color);
    
    std::string getDescription() const override;
    double getPrice() const override;
    
    void setGiftMessage(const std::string& message);
    std::string getGiftMessage() const;
};

#endif // PLANTDECORATOR_H