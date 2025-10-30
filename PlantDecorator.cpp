// PlantDecorator.cpp
#include "PlantDecorator.h"

// PlantDecorator implementation
PlantDecorator::PlantDecorator(Plant* plant) : decoratedPlant(plant) {}

PlantDecorator::~PlantDecorator() {
    delete decoratedPlant; // Assuming ownership; beware: this may need adjustment based on memory management in the full system
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

void PlantDecorator::grow() {
    decoratedPlant->grow();
}

// PottedPlant implementation
PottedPlant::PottedPlant(Plant* plant, const std::string& type, const std::string& size)
    : PlantDecorator(plant), potType(type), potSize(size), potPrice(10.0) {} // Example price; adjust as needed

std::string PottedPlant::getDescription() const {
    return decoratedPlant->getDescription() + " in a " + potSize + " " + potType + " pot";
}

double PottedPlant::getPrice() const {
    return decoratedPlant->getPrice() + potPrice;
}

std::string PottedPlant::getPotType() const {
    return potType;
}

void PottedPlant::repot(const std::string& newType, const std::string& newSize) {
    potType = newType;
    potSize = newSize;
    // Could adjust potPrice here if needed
}

// LabeledPlant implementation
LabeledPlant::LabeledPlant(Plant* plant, const std::string& text, const std::string& care)
    : PlantDecorator(plant), labelText(text), careInstructions(care), labelPrice(2.0) {} // Example price

std::string LabeledPlant::getDescription() const {
    return decoratedPlant->getDescription() + " with label: " + labelText;
}

double LabeledPlant::getPrice() const {
    return decoratedPlant->getPrice() + labelPrice;
}

std::string LabeledPlant::getCareInstructions() const {
    return careInstructions;
}

// GiftWrappedPlant implementation
GiftWrappedPlant::GiftWrappedPlant(Plant* plant, const std::string& style, const std::string& color)
    : PlantDecorator(plant), wrappingStyle(style), ribbonColor(color), giftMessage(""), wrappingPrice(5.0) {} // Example price

std::string GiftWrappedPlant::getDescription() const {
    return decoratedPlant->getDescription() + " gift-wrapped in " + wrappingStyle + " with " + ribbonColor + " ribbon";
}

double GiftWrappedPlant::getPrice() const {
    return decoratedPlant->getPrice() + wrappingPrice;
}

void GiftWrappedPlant::setGiftMessage(const std::string& message) {
    giftMessage = message;
}

std::string GiftWrappedPlant::getGiftMessage() const {
    return giftMessage;
}