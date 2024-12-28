//
// Created by hussa on 7/14/2024.
//
#include "pirateShip.h"
pirate::pirate(int pirateId, int treasure, std::shared_ptr<ship> currentShip, unsigned int place):
pirateId(pirateId),treasure(treasure),currentShip(currentShip),place(place)  {}



void pirate::setTreasure(int change) {
    this->treasure+=change;
}

void pirate::setShip(std::shared_ptr<ship> nextShip) {
    this->currentShip=nextShip;
}

int pirate::getTreasure() {
   if (auto ship = this->currentShip.lock()) {
        return this->treasure + ship->getShTreasure();
    }
    return this->treasure;
}

int pirate::getId() const {
    return this->pirateId;
}

unsigned int pirate::getPlace() const {
    return this->place;
}

int pirate::getTreasurePure() {
    return this->treasure;
}

std::shared_ptr<ship> pirate::getShip() {
    return this->currentShip.lock();
}
void pirate::setPlace(unsigned int place)
{
    this->place=place;
}




ship::ship(int shipId, int cannons)  {
    this->pirateinShip=new AVLtree<std::shared_ptr<pirate>>();
    this->pirateByTreasure=new AVLtree<std::shared_ptr<pirate>>();
    this->ShTreasure=0;
    this->shipId=shipId;
    this->cannons=cannons;
    this->lastPlace=0;
}



ship::~ship() {
    delete pirateinShip;
    delete pirateByTreasure;
}

int ship::sizeOfPirates() const {
    return this->pirateinShip->size();
}

int ship::getcannons() const {
    return this->cannons;
}

int ship::getShTreasure() const {
    return this->ShTreasure;
}

void ship::insertPirate(std::shared_ptr<pirate> toAdd,int pirateId,std::shared_ptr<pirate> toAdd2) {
    int place=this->getLastPlace();
    this->pirateinShip->insert(toAdd,place,pirateId);
    toAdd->setPlace(place);
    this->pirateByTreasure->insert(toAdd2,toAdd2->getTreasurePure(),pirateId);
}

int ship::getLastPlace() {
    return this->lastPlace++;
}

int ship::getRich() const {
    return this->pirateByTreasure->getMaxId();
}

int ship::getFirstPirate() const {
    return this->pirateinShip->getMinId();
}

void ship::removePirate(std::shared_ptr<pirate> toRemove,std::shared_ptr<pirate>toRemove2) {
    this->pirateinShip->remove(toRemove,toRemove->getPlace(),toRemove->getId());
    this->pirateByTreasure->remove(toRemove2,toRemove2->getTreasurePure(),toRemove2->getId());
}

void ship::changeTreasure(int change) {
    this->ShTreasure+=change;
}

void ship::removePirateTreasure(std::shared_ptr<pirate>toRemove)  {
    this->pirateByTreasure->remove(toRemove,toRemove->getTreasurePure(),toRemove->getId());

}
void ship::insertPirateTreasure(std::shared_ptr<pirate>toInsert)  {
    this->pirateByTreasure->insert(toInsert,toInsert->getTreasurePure(),toInsert->getId());

}



//class pirateTreasure
/*pirateTreasure::pirateTreasure(int pirateId, int *treasure,std::shared_ptr<ship>currentShip):
        pirateId(pirateId),treasure(treasure),currentShip(currentShip){}

bool pirateTreasure::operator<(const pirateTreasure &other) const {
    ////need to add ship treasure//////
    if(this->treasure < other.treasure)
    {
        return true;
    }
    if(this->treasure > other.treasure)
    {
        return false;
    }
    if(this->treasure == other.treasure)
    {
        if(this->pirateId<other.pirateId)
        {
            return true;
        }
        if(this->pirateId>other.pirateId)
        {
            return false;
        }

    }
    return false;
}

bool pirateTreasure::operator>(const pirateTreasure &other) const {
    if(this->treasure > other.treasure)
    {
        return true;
    }
    if(this->treasure < other.treasure)
    {
        return false;
    }
    if(this->treasure == other.treasure)
    {
        if(this->pirateId>other.pirateId)
        {
            return true;
        }
        if(this->pirateId<other.pirateId)
        {
            return false;
        }

    }
    return false;
}

int pirateTreasure::getShipTreasure() const {
    return this->currentShip->getShTreasure();
}

int pirateTreasure::getId() const {
    return this->pirateId;
}
int  pirateTreasure::getTresure()const
{
    return *(this->treasure);
}



//class piratePlace
piratePlace::piratePlace(int pirateId, int treasure,std::shared_ptr<ship> currentShip,unsigned int place):
        pirateId(pirateId),treasure(treasure),currentShip(currentShip),place(place) {}

bool piratePlace::operator<(const piratePlace &other) const {
    if(this->place < other.place)
    {
        return true;
    }
    return false;
}
bool piratePlace::operator>(const piratePlace &other) const {
    if(this->place > other.place)
    {
        return true;
    }
    return false;
}

int piratePlace::getShipTreasure() const {
    return this->currentShip->getShTreasure();
}

int piratePlace::getId() const {
    return this->pirateId;
}

void piratePlace::setTreasure(int change) {
    this->treasure+=change;
}

void piratePlace::setShip(std::shared_ptr<ship> nextShip) {
    this->currentShip=nextShip;
}
int& piratePlace::getTreasure() {
    return this->treasure;
}*/
