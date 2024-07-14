#include "pirates24b1.h"

Ocean::Ocean()
{
  pirateById = new AVLtree<std::shared_ptr<pirate>>();
  ships = new AVLtree<std::shared_ptr<ship>>();
}

Ocean::~Ocean()
{
    delete pirateById;
    delete ships;
}

StatusType Ocean::add_ship(int shipId, int cannons)
{
    if (shipId<=0 || cannons <0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (ships->find(shipId)->getData()) {
        return StatusType::FAILURE;
    }
    try {
        std::shared_ptr<ship> toAdd(new ship(shipId, cannons));
        ships->insert(toAdd,shipId);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

StatusType Ocean::remove_ship(int shipId)
{
    if(shipId<=0)
    {
        return StatusType::INVALID_INPUT;
    }

    try{
        std::shared_ptr<ship> toRemove=ships->find(shipId)->getData();
        if(toRemove== nullptr)
        {
            return StatusType::FAILURE;
        }
        else if(toRemove->sizeOfPirates()!=0)
        {
            return StatusType::FAILURE;
        }
        ships->remove(toRemove);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;

    }
    return StatusType::FAILURE;
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure)
{
    if(shipId<=0 || pirateId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    try{
        std::shared_ptr<ship>toShip=this->ships->find(shipId)->getData();
        if(toShip== nullptr)
        {
            return StatusType::FAILURE;
        }
        std::shared_ptr<pirate>toPirate=this->pirateById->find(pirateId)->getData();
        if(toPirate!= nullptr)
        {
            return StatusType::FAILURE;
        }
//////////////////////////////////////////////////////need to implement
        int last=toShip->getLastPlace();
        std::shared_ptr<piratePlace>pirateP(new piratePlace(pirateId,treasure,toShip,last));
        std::shared_ptr<pirateTreasure>pirateT(new pirateTreasure(pirateId,&(pirateP->getTreasure()),toShip));
        std::shared_ptr<pirate>toAdd(new pirate(pirateId,&(pirateP->getTreasure()),toShip,pirateP,pirateT));
        toShip->insertPirate(pirateP,last,pirateT);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;

    }

    return StatusType::FAILURE;
}

StatusType Ocean::remove_pirate(int pirateId)
{
    if(pirateId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    try{
        std::shared_ptr<pirate>topirate=this->pirateById->find(pirateId)->getData();
        if(topirate== nullptr)
        {
            return StatusType::FAILURE;
        }
        ////////////////////////need to implement///////////////////////
        topirate->removeFromShip();
        this->pirateById->remove(topirate);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;

    }
    return StatusType::FAILURE;
}

StatusType Ocean::treason(int sourceShipId, int destShipId)
{
    if(sourceShipId<=0 || destShipId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    try{
        //////////////////////////////////////////////////////need to implement
        std::shared_ptr<ship>sourceShip=this->ships->find(sourceShipId)->getData();
        std::shared_ptr<ship>toShip=this->ships->find(destShipId)->getData();
        if(sourceShip == nullptr || toShip== nullptr)
        {
            return StatusType::FAILURE;
        }
        if(sourceShip->sizeOfPirates()==0)
        {
            return StatusType::FAILURE;
        }
       std::shared_ptr<piratePlace>topirate= sourceShip->getFirstPirate();
        int dis=toShip->getShTreasure(),sour=sourceShip->getShTreasure();
        topirate->setTreasure(sour-dis);
        std::shared_ptr<pirate>search=this->pirateById->find(topirate->getId())->getData();
        search->setShip(toShip);
        std::shared_ptr<pirateTreasure>tre=search->getPirateTreasure();
        toShip->insertPirate(topirate,topirate->getId(),tre);
        //////////////////////////////need to remove topirate from sourceship
        sourceShip->removePirate(topirate,tre);

    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;

    }
    return StatusType::FAILURE;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change)
{
    if(pirateId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    try{
        std::shared_ptr<pirate>toPirate=this->pirateById->find(pirateId)->getData();
        if(toPirate== nullptr)
        {
            return StatusType::FAILURE;
        }
        toPirate->setTreasure(change);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

output_t<int> Ocean::get_treasure(int pirateId)
{
    if(pirateId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try{
        int treasure;
        std::shared_ptr<pirate>toget = this->pirateById->find(pirateId)->getData();
        if(toget== nullptr)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        treasure=toget->getTreasure();
        return output_t<int>(treasure);

    }
    catch (const std::bad_alloc& bad) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
    return 0;
}

output_t<int> Ocean::get_cannons(int shipId)
{
    if(shipId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try{
        std::shared_ptr<ship>toget= this->ships->find(shipId)->getData();
        if(toget== nullptr)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        return output_t<int>(toget->getcannons());
    }
    catch (const std::bad_alloc& bad)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);

    }
    return 0;
}

output_t<int> Ocean::get_richest_pirate(int shipId)
{
    if(shipId<=0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    try{
        std::shared_ptr<ship>toShip=this->ships->find(shipId)->getData();
        if(toShip== nullptr)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        //getRich is O(1)
        ////////////////////wrong this return the pirate with the biggest Id/////////////////
        return output_t<int>(toShip->getRich());
    }
    catch (const std::bad_alloc& bad)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);

    }
    return 0;
}

StatusType Ocean::ships_battle(int shipId1,int shipId2)
{
    if(shipId1<=0 || shipId2<=0 || shipId1==shipId2)
    {
        return StatusType::INVALID_INPUT;
    }
    try{
        std::shared_ptr<ship>ship1= this->ships->find(shipId1)->getData();
        if(ship1== nullptr)
        {
            return StatusType::FAILURE;
        }
        std::shared_ptr<ship>ship2= this->ships->find(shipId2)->getData();
        if(ship2== nullptr)
        {
            return StatusType::FAILURE;
        }
        ////////////////////////////////need to implement
        int cannons1=ship1->getcannons(),size1=ship1->sizeOfPirates();
        int cannons2=ship2->getcannons(),size2=ship2->sizeOfPirates();
        if(min(size1,cannons1)< min(size2,cannons2))
        {
            ship1->changeTreasure(-1 * ship2->sizeOfPirates());
            ship2->changeTreasure(ship1->sizeOfPirates());
        }
        if(min(size1,cannons1)> min(size2,cannons2))
        {
            ship1->changeTreasure( ship2->sizeOfPirates());
            ship2->changeTreasure(-1 * ship1->sizeOfPirates());
        }

        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;

    }
    return StatusType::FAILURE;
}

int Ocean::min(int num1, int num2) const {
    if(num1<num2)
    {
        return num1;
    }
    return num2;
}
int main()
{
    return 0;
}




