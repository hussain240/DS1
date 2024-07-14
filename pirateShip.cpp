//
// Created by hussa on 7/14/2024.
//
#include "pirateShip.h"
pirate::pirate(int pirateId, int *treasure,  std::shared_ptr<ship> currentShip,std::shared_ptr<piratePlace>samePirate,std::shared_ptr<pirateTreasure>samePirate2):
        pirateId(pirateId),treasure(treasure),currentShip(currentShip),samePirate(samePirate),samePirate2(samePirate2){}

bool pirate::operator<(const pirate &other) const {
    if(this->pirateId < other.pirateId)
    {
        return true;
    }
    return false;
}
bool pirate::operator>(const pirate &other) const {
    if(this->pirateId > other.pirateId)
    {
        return true;
    }
    return false;
}



void pirate::setTreasure(int change) {
    *(this->treasure)+=change;
}

void pirate::setShip(std::shared_ptr<ship> nextShip) {
    this->currentShip=nextShip;
}

int pirate::getTreasure() {
    return *(this->treasure)+this->currentShip->getShTreasure();
}

void pirate::removeFromShip() {
    this->currentShip->removePirate(this->samePirate, this->samePirate2);
}

std::shared_ptr<pirateTreasure> pirate::getPirateTreasure() const {
    return this->samePirate2;
}



//class pirateTreasure
pirateTreasure::pirateTreasure(int pirateId, int *treasure,std::shared_ptr<ship>currentShip):
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
}
ship::ship(int shipId, int cannons)  {
    this->pirateinShip=new AVLtree<std::shared_ptr<piratePlace>>();
    this->pirateByTreasure=new AVLtree<std::shared_ptr<pirateTreasure>>();
    this->ShTreasure=0;
    this->shipId=shipId;
    this->cannons=cannons;
    this->lastPlace=0;
}

bool ship::operator<(const ship &other) const {
    if( this->shipId < other.shipId)
    {
        return true;
    }
    return false;
}

bool ship::operator>(const ship &other) const {
    if( this->shipId > other.shipId)
    {
        return true;
    }
    return false;
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

void ship::insertPirate(std::shared_ptr<piratePlace> toAdd,int pirateId,std::shared_ptr<pirateTreasure> toAdd2) {
    this->pirateinShip->insert(toAdd,pirateId);
    this->pirateByTreasure->insert(toAdd2,pirateId);
}

int ship::getLastPlace() {
    return this->lastPlace++;
}

int ship::getRich() const {
    return this->pirateByTreasure->getmax()->getId();
}

std::shared_ptr<piratePlace> ship::getFirstPirate() const {
    return this->pirateinShip->getmin();
}

void ship::removePirate(std::shared_ptr<piratePlace> toRemove,std::shared_ptr<pirateTreasure>toRemove2) {
    this->pirateinShip->remove(toRemove);
    this->pirateByTreasure->remove(toRemove2);
}

void ship::changeTreasure(int change) {
    this->ShTreasure-=change;
}
