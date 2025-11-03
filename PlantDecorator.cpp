#include "PlantDecorator.h"

// PlantDecorator implementation
//PlantDecorator::PlantDecorator(Plant* plant) 
 //   : Plant(plant->info), decoratedPlant(plant) {}  // Copy info for base ctor

PlantDecorator::PlantDecorator(Plant* plant)
    : Plant(*plant),  // Calls copy ctor to duplicate base state safely
      decoratedPlant(plant) {}

PlantDecorator::~PlantDecorator() {
    delete decoratedPlant;
}

std::string PlantDecorator::getDescription() const {
    return decoratedPlant->getDescription();
}

double PlantDecorator::getPrice() const {
    return decoratedPlant->getPrice();
}

void PlantDecorator::water(int amount) {
    decoratedPlant->water(amount);
}

void PlantDecorator::fertilize(int amount) {
    decoratedPlant->fertilize(amount);
}

void PlantDecorator::exposeToSunlight(int hours) {
    decoratedPlant->exposeToSunlight(hours);
}

void PlantDecorator::addSunlight(int amount) {
    decoratedPlant->addSunlight(amount);
}

void PlantDecorator::grow() {
    decoratedPlant->grow();
}

// PottedPlant implementation
PottedPlant::PottedPlant(Plant* plant, const std::string& type, const std::string& size)
    : PlantDecorator(plant), potType(type), potSize(size), potPrice(10.0) {}

std::string PottedPlant::getDescription() const {
    return PlantDecorator::getDescription() + " in a " + potSize + " " + potType + " pot";
}

double PottedPlant::getPrice() const {
    return PlantDecorator::getPrice() + potPrice;
}

std::string PottedPlant::getPotType() const {
    return potType;
}

void PottedPlant::repot(const std::string& newType, const std::string& newSize) {
    potType = newType;
    potSize = newSize;
}

// LabeledPlant implementation
LabeledPlant::LabeledPlant(Plant* plant, const std::string& text, const std::string& care)
    : PlantDecorator(plant), labelText(text), careInstructions(care), labelPrice(2.0) {}

std::string LabeledPlant::getDescription() const {
    return PlantDecorator::getDescription() + " with label: " + labelText;
}

double LabeledPlant::getPrice() const {
    return PlantDecorator::getPrice() + labelPrice;
}

std::string LabeledPlant::getCareInstructions() const {
    return careInstructions;
}

// GiftWrappedPlant implementation
GiftWrappedPlant::GiftWrappedPlant(Plant* plant, const std::string& style, const std::string& color)
    : PlantDecorator(plant), wrappingStyle(style), ribbonColor(color), giftMessage(""), wrappingPrice(5.0) {}

std::string GiftWrappedPlant::getDescription() const {
    return PlantDecorator::getDescription() + " gift-wrapped in " + wrappingStyle + " with " + ribbonColor + " ribbon";
}

double GiftWrappedPlant::getPrice() const {
    return PlantDecorator::getPrice() + wrappingPrice;
}

void GiftWrappedPlant::setGiftMessage(const std::string& message) {
    giftMessage = message;
}

std::string GiftWrappedPlant::getGiftMessage() const {
    return giftMessage;
}