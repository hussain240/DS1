//
// Created by hussa on 7/14/2024.
//

#ifndef DS1_PIRATESHIP_H
#define DS1_PIRATESHIP_H
#include "AVLtree.h"
#include <memory>
class ship;
class pirateTreasure;
class piratePlace;
class pirate;
class pirate{
protected:
    int pirateId;
    int *treasure;
    std::shared_ptr<ship> currentShip;
    std::shared_ptr<piratePlace>samePirate;
    std::shared_ptr<pirateTreasure>samePirate2;
public:
    pirate()=default;
    pirate(int pirateId,int *treasure, std::shared_ptr<ship> currentShip,std::shared_ptr<piratePlace>samePirate,std::shared_ptr<pirateTreasure>samePirate2);
    virtual ~pirate()=default;
    bool operator<(const pirate& other) const;
    bool operator>(const pirate& other) const;
    void setTreasure(int change);
    int getTreasure();
    void setShip(std::shared_ptr<ship> nextShip);
    void removeFromShip();
    std::shared_ptr<pirateTreasure> getPirateTreasure()const;
};



class pirateTreasure{
    int pirateId;
    int *treasure;
    std::shared_ptr<ship>currentShip;
public:
    pirateTreasure()=default;
    pirateTreasure(int pirateId,int *treasure, std::shared_ptr<ship>currentShip);
    bool operator<(const pirateTreasure& other) const;
    bool operator>(const pirateTreasure& other) const;
    int getShipTreasure()const;
    int getId()const;
};



class piratePlace{
    int pirateId;
    int treasure;
    std::shared_ptr<ship> currentShip;
    unsigned int place;
public:
    piratePlace()=default;
    piratePlace(int pirateId,int treasure, std::shared_ptr<ship> currentShip,unsigned int place);
    bool operator<(const piratePlace& other) const;
    bool operator>(const piratePlace& other) const;
    int getShipTreasure()const;
    int getId()const;
    int& getTreasure();
    void setShip(std::shared_ptr<ship> nextShip);
    void setTreasure(int change);

};



class ship{
    int shipId;
    int cannons;
    int ShTreasure;
    unsigned int lastPlace;
    AVLtree<std::shared_ptr<piratePlace>>* pirateinShip;
    AVLtree<std::shared_ptr<pirateTreasure>>* pirateByTreasure;

public:
    ship(int shipId,int cannons);
    ship()=default;
    ~ship();
    int sizeOfPirates()const;
    int getcannons()const;
    int getShTreasure()const;
    bool operator<(const ship& other) const;
    bool operator>(const ship& other) const;
    void insertPirate(std::shared_ptr<piratePlace>toAdd,int  pirateId,std::shared_ptr<pirateTreasure> toAdd2);
    int getLastPlace();
    int getRich()const;
    std::shared_ptr<piratePlace> getFirstPirate()const;
    void removePirate(std::shared_ptr<piratePlace>toRemove,std::shared_ptr<pirateTreasure>toRemove2);
    void changeTreasure(int change);
};


#endif //DS1_PIRATESHIP_H
