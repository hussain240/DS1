#include "pirates24b1.h"
//#include "pirateShip.cpp"
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
    try {
        if(this->ships->size()!=0)
        {
            pair a=pair(shipId,shipId);
            if (ships->find(a)!=nullptr) {
                 return StatusType::FAILURE;
            }
        }
        std::shared_ptr<ship> toAdd(new ship(shipId, cannons));
        ships->insert(toAdd,shipId,shipId);
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
        std::shared_ptr<ship> toRemove=nullptr;
        if(ships->size()!=0)
        {
            pair a=pair(shipId,shipId);
            toRemove =ships->find(a)->value;
        }
        if(toRemove== nullptr)
        {
            return StatusType::FAILURE;
        }
        else if(toRemove->sizeOfPirates()!=0)
        {
            return StatusType::FAILURE;
        }
        ships->remove(toRemove,shipId,shipId);
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
        std::shared_ptr<ship>toShip=nullptr;
        if(ships->size()!=0)
        {
            pair shipIdpair=pair(shipId,shipId);
           toShip =this->ships->find(shipIdpair)->value;
        }
        if(toShip== nullptr)
        {
            return StatusType::FAILURE;
        }
        std::shared_ptr<pirate>toBeAddedPirate=nullptr;
        if(pirateById->size()!=0)
        {
           pair shipIdpair = pair(pirateId, pirateId);
            auto foundPirateNode = this->pirateById->find(shipIdpair);
            if (foundPirateNode != nullptr) { // pirate was found in pirateById
                return StatusType::FAILURE;
            }
        }

//////////////////////////////////////////////////////need to implement
        
        int last=toShip->getLastPlace();

        toBeAddedPirate = std::make_shared<pirate>(pirateId,treasure,toShip,last);
        this->pirateById->insert(toBeAddedPirate,pirateId,pirateId);
        toShip->insertPirate(toBeAddedPirate,pirateId,toBeAddedPirate);
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

        std::shared_ptr<pirate>topirate=nullptr;
        if(pirateById->size()!=0)
        {
            pair a=pair(pirateId,pirateId);
            topirate=this->pirateById->find(a)->value;
        }
        if(topirate== nullptr)
        {
            return StatusType::FAILURE;
        }
        ////////////////////////need to implement///////////////////////
        topirate->getShip()->removePirate(topirate,topirate);
        this->pirateById->remove(topirate,pirateId,pirateId);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;

    }
    return StatusType::FAILURE;
}

StatusType Ocean::treason(int sourceShipId, int destShipId) {
    if (sourceShipId <= 0 || destShipId <= 0 || destShipId == sourceShipId) {
        return StatusType::INVALID_INPUT;
    }
    auto sourceShipNode = ships->find(pair(sourceShipId, sourceShipId));
    auto destShipNode = ships->find(pair(destShipId, destShipId));

    // Check if the ships were found
    if (!sourceShipNode || !destShipNode) {
        return StatusType::FAILURE; // Ship not found
    }

    std::shared_ptr<ship> sourceShip = sourceShipNode->value;
    std::shared_ptr<ship> destShip = destShipNode->value;

    // Additional null checks for the shared_ptr instances
    if (!sourceShip || !destShip) {
        return StatusType::FAILURE; // Ship not found or invalid
    }

    if (sourceShip->sizeOfPirates() == 0) {
        return StatusType::FAILURE; // No pirates on source ship
    }

    int longestStayingPirateId = sourceShip->getFirstPirate();
    auto longestStayingPirate = pirateById->find(pair(longestStayingPirateId
            , longestStayingPirateId)) ->value;


    sourceShip->removePirate(longestStayingPirate, longestStayingPirate);


    longestStayingPirate->setShip(destShip);


    destShip->insertPirate(longestStayingPirate, longestStayingPirateId, longestStayingPirate);

    longestStayingPirate->setTreasure( sourceShip->getShTreasure() - destShip->getShTreasure());

    return StatusType::SUCCESS;

}


StatusType Ocean::update_pirate_treasure(int pirateId, int change)
{
    if(pirateId<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    try{
        std::shared_ptr<pirate>toPirate=nullptr;
        if(pirateById->size()!=0)
        {
            pair a = pair(pirateId,pirateId);
             toPirate= this->pirateById->find(a)->value;
        }
        if(toPirate== nullptr)
        {
            return StatusType::FAILURE;
        }
        toPirate->setTreasure(change);
        //////////////////////////need to remove from pirateByTreasure and insert again////////////
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
        std::shared_ptr<pirate>toget =nullptr;
        if(pirateById->size()!=0)
        {
            pair a=pair(pirateId,pirateId);
            toget= this->pirateById->find(a)->value;
        }
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
        std::shared_ptr<ship>toget=nullptr;
        if(ships->size()!=0)
        {
            pair a=pair(shipId,shipId);
            toget=this->ships->find(a)->value;
        }
    
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

        std::shared_ptr<ship>toShip=nullptr;
        if(ships->size()!=0)
        {
            pair a=pair(shipId,shipId);
            toShip= this->ships->find(a)->value;
        }
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
        std::shared_ptr<ship>ship1=nullptr;
        if(ships->size()!=0)
        {
            pair a=pair(shipId1,shipId1);
              ship1= this->ships->find(a)->value;
        }
        if(ship1== nullptr)
        {
            return StatusType::FAILURE;
        }
        std::shared_ptr<ship>ship2=nullptr;
        if(ships->size()!=0)
        {
            pair b=pair(shipId2,shipId2);
          ship2=this->ships->find(b)->value;
        }
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
void Ocean::print_avl_tree() const
{
    ships->print();
}

/// Test the treason function

#include "cassert"

void testTreasonFunction() {
    Ocean ocean;
    int sourceShipId = 1;
    int destShipId = 2;
    int pirateId1 = 101;
    int pirateId2 = 102;
    int treasure = 50;

    // Setup: Add ships and pirates
    ocean.add_ship(sourceShipId, 5); // Add source ship
    ocean.add_ship(destShipId, 5);   // Add destination ship
    ocean.add_pirate(pirateId1, sourceShipId, treasure); // Add first pirate
    ocean.add_pirate(pirateId2, sourceShipId, treasure); // Add second pirate, assuming pirateId1 stays longer than pirateId2


    std::shared_ptr<ship> sourceShip = (ocean.ships)->find(pair(sourceShipId, sourceShipId))->value;
    std::shared_ptr<ship> destShip = (ocean.ships)->find(pair(destShipId, destShipId))->value;

    sourceShip->changeTreasure(5);
    destShip->changeTreasure(4);

    StatusType result = ocean.treason(sourceShipId, destShipId);

    int longestPiratesrcId = sourceShip->getFirstPirate();
    int longestPiratedestId = destShip->getFirstPirate();

    pair idpair =pair(longestPiratedestId,longestPiratedestId);
    auto longestPiratesrc = ocean.pirateById->find(idpair)->value;

    // Action: Perform treason


    // Verify: Check if the pirate was successfully transferred
    assert(result == StatusType::SUCCESS); // Ensure treason was successful
    assert(longestPiratesrcId != pirateId1); // Assuming pirateId1 was the longest-staying pirate
    assert(longestPiratedestId == pirateId1); // Ensure pirateId1 is now in the destination ship
    std::cout<<longestPiratesrc->getTreasurePure()<<std::endl;

    std::cout << "Test passed: Treason function works as expected." << std::endl;
}

int main() {
    testTreasonFunction();
    return 0;
}
