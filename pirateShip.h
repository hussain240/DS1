//
// Created by hussa on 7/14/2024.
//

#ifndef DS1_PIRATESHIP_H
#define DS1_PIRATESHIP_H
#include "AVLtree.h"
#include <memory>
class ship;
class pirate;
class pirate{
protected:
    int pirateId;
    int treasure;
    unsigned int place;
    std::shared_ptr<ship> currentShip;
public:
    pirate()=default;
    pirate(int pirateId,int treasure, std::shared_ptr<ship> currentShip,unsigned int place);
    virtual ~pirate()=default;
    void setTreasure(int change);
    int getTreasure();
    int getTreasurePure();
    unsigned int getPlace()const;
    int getId()const;
    void setShip(std::shared_ptr<ship> nextShip);
    std::shared_ptr<ship> getShip();
};


class ship{
    int shipId;
    int cannons;
    int ShTreasure;
    unsigned int lastPlace;
    AVLtree<std::shared_ptr<pirate>>* pirateinShip;
    AVLtree<std::shared_ptr<pirate>>* pirateByTreasure;

public:
    ship(int shipId,int cannons);
    ship()=default;
    ~ship();
    int sizeOfPirates()const;
    int getcannons()const;
    int getShTreasure()const;
    void insertPirate(std::shared_ptr<pirate>toAdd,int  pirateId,std::shared_ptr<pirate> toAdd2);
    int getLastPlace();
    int getRich()const;
    int getFirstPirate()const;
    void removePirate(std::shared_ptr<pirate>toRemove,std::shared_ptr<pirate>toRemove2);
    void changeTreasure(int change);
};



/*class pirateTreasure{
    int pirateId;
    int *treasure;
    std::shared_ptr<ship>currentShip;
public:
    pirateTreasure()=default;
    pirateTreasure(int pirateId,int *treasure, std::shared_ptr<ship>currentShip);
    bool operator<(const pirateTreasure& other) const;
    bool operator>(const pirateTreasure& other) const;
    int getShipTreasure()const;
    int getTresure()const;
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

};*/



/*class ship{
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
};*/


#endif //DS1_PIRATESHIP_H
