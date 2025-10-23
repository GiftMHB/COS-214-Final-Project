#ifndef CONCRETESTATES_H
#define CONCRETESTATES_H

#include "../develop/includes/PlantState.h"
#include "../develop/includes/Plant.h"
#include <iostream>
#include <memory>





class SeedlingState : public PlantState {

    private:

    static const int MIN_AGE = 7;

    static const int REQUIRED_WATER = 40;

    
public:
        
    void water(Plant* plant, int amount) override;

    void fertilize(Plant* plant, int amount) override;

    void addSunlight(Plant* plant, int amount) override;


    void grow(Plant* plant) override;
        
    
    void checkTransition(Plant* plant) override;

    

    
    std::string getStateName() const override{
        
        return "Seedling"; 
    
    
    }
    
    int getHealthPercentage() const override{
        
        return 100; 
    
    
    }
    
    bool canBeSold() const override{
        
        
        return false; 
    
    }



};





class GrowingState : public PlantState {
private:


    static const int MATURE_AGE = 30;

    static const int WILTING_THRESHOLD = 20;

    double growthRate = 1.5;



public:

        void water(Plant* plant, int amount) override;

        void fertilize(Plant* plant, int amount) override;

        void addSunlight(Plant* plant, int amount) override;

        void grow(Plant* plant) override;

        void checkTransition(Plant* plant) override;

        
        
        std::string getStateName() const override{ 
            
            return "Growing"; 
        
        }
       
        int getHealthPercentage() const override{ 
            
            return 85; 
        
        }
        
        bool canBeSold() const override{ 
            
            return false; 
        
        }

};





class MatureState : public PlantState {
private:



    static const int WILTING_AGE = 60;

    bool maintenanceRequired = true;




public:

    void water(Plant* plant, int amount) override;

    void fertilize(Plant* plant, int amount) override;



    void addSunlight(Plant* plant, int amount) override;

    void grow(Plant* plant) override;


    void checkTransition(Plant* plant) override;

    
    
    std::string getStateName() const override{
        
        return "Mature"; 
    
    }
    
    int getHealthPercentage() const override{
        
        return 100; 
    
    }
    
    bool canBeSold() const override{ 
        
        
        return true; 
    
    }


};





class WiltingState : public PlantState {
private:

    static const int MAX_RECOVERY_TIME = 5;

    int timeInState = 0;

    double recoveryChance = 0.7;




public:

    void water(Plant* plant, int amount) override;

    void fertilize(Plant* plant, int amount) override;

    void addSunlight(Plant* plant, int amount) override;

    void grow(Plant* plant) override;


    void checkTransition(Plant* plant) override;
        

    bool attemptRecovery(Plant* plant);









std::string getStateName() const override{ 
    
    return "Wilting"; 


}




    int getHealthPercentage() const override{ 
        
        return 45; 
    
    }



    bool canBeSold() const override{ 
        
        return false; 
    
    
    }


};






class DeadState : public PlantState {

    public:

    void water(Plant* plant, int amount) override;

    void fertilize(Plant* plant, int amount) override;


    void addSunlight(Plant* plant, int amount) override;


    void grow(Plant* plant) override;

    void checkTransition(Plant* plant) override;

    

    
    std::string getStateName() const override{ 
        
        return "Dead"; 
    
    }
  
    int getHealthPercentage() const override{ 
        
        return 0; 
    
    }
    
    
    bool canBeSold() const override{ 
        
        return false; 
    
    }


};

#endif
