#include "pirates24b1.h"

Ocean::Ocean()
{
  pirateById = new AVLtree<std::shared_ptr<pirate>>() ;
  ships = new AVLtree<std::shared_ptr<ship>>() ;
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
    if(ships->size()==0)
    {
        return StatusType::FAILURE;
    }
    try{
        pair shipIdPair=pair(shipId,shipId);

        node<std::shared_ptr<ship>>* shipNode= ships->find(shipIdPair);

        if(shipNode== nullptr)
        {
            return StatusType::FAILURE;
        }
        auto shipObj=shipNode->value;
        if(shipObj->sizeOfPirates()!=0)
        {
            return StatusType::FAILURE;
        }
        ships->remove(shipObj,shipId,shipId);
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
    if(ships->size()==0)
    {
        return StatusType::FAILURE;
    }
    try{
        pair shipIdpair=pair(shipId,shipId);
        auto ShipNode =this->ships->find(shipIdpair);

        if(ShipNode == nullptr)
        {
            return StatusType::FAILURE;
        }
        pair a=pair(pirateId,pirateId);
        auto toPirate=pirateById->find(a);
        if(toPirate != nullptr)
        {
            return StatusType::FAILURE;
        }
        auto shipObj=ShipNode->value;

        int last = shipObj->getLastPlace();
        std::shared_ptr<pirate> pirateObj (new pirate(pirateId,treasure-shipObj->getShTreasure(),shipObj,last));
        this->pirateById->insert(pirateObj,pirateId,pirateId);
        shipObj->insertPirate(pirateObj,pirateId,pirateObj);
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
    if(pirateById->size()==0)
    {
        return StatusType::FAILURE;
    }
    try{

        pair pirateIdPair=pair(pirateId,pirateId);
        auto pirateNode= this->pirateById->find(pirateIdPair);

        if(pirateNode== nullptr)
        {
            return StatusType::FAILURE;
        }
        auto pirateObj=pirateNode->value;

       std::shared_ptr<ship> ship1= pirateObj->getShip();
       ship1->removePirate(pirateObj,pirateObj);
        this->pirateById->remove(pirateObj,pirateId,pirateId);
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
    try{
    auto sourceShipNode = ships->find(pair(sourceShipId, sourceShipId));
    auto destShipNode = ships->find(pair(destShipId, destShipId));


    if (sourceShipNode==nullptr || destShipNode==nullptr) {
        return StatusType::FAILURE; 
    }

    std::shared_ptr<ship> sourceShip = sourceShipNode->value;
    std::shared_ptr<ship> destShip = destShipNode->value;

    if (sourceShip==nullptr || destShip==nullptr) {
        return StatusType::FAILURE;
    }

    if (sourceShip->sizeOfPirates() == 0) {
        return StatusType::FAILURE; 
    }

    int longestStayingPirateId = sourceShip->getFirstPirate();
    pair a=pair(longestStayingPirateId, longestStayingPirateId);
    auto longestStayingPirate = pirateById->find(a) ->value;

        sourceShip->removePirate(longestStayingPirate, longestStayingPirate);
        longestStayingPirate->setShip(destShip);
        longestStayingPirate->setTreasure( sourceShip->getShTreasure() - destShip->getShTreasure());
         destShip->insertPirate(longestStayingPirate, longestStayingPirateId, longestStayingPirate);
         




        //longestStayingPirate->setTreasure( sourceShip->getShTreasure() - destShip->getShTreasure());

    return StatusType::SUCCESS;
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
    if(pirateById->size()==0)
    {
        return StatusType::FAILURE;
    }
    try{
        std::shared_ptr<pirate>toPirate = nullptr;
            pair a = pair(pirateId,pirateId);
            auto checkPirate= this->pirateById->find(a);
        if(checkPirate== nullptr)
            {
                return StatusType::FAILURE;
            }
        toPirate=checkPirate->value;
        toPirate->getShip()->removePirateTreasure(toPirate);
        toPirate->setTreasure(change);
        toPirate->getShip()->insertPirateTreasure(toPirate);
        
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
    if(pirateById->size()== 0) {
        return output_t<int>(StatusType::FAILURE);
    }
    try{
            pair pirateIdPair = pair(pirateId, pirateId);
            auto PirateNode = this->pirateById->find(pirateIdPair);

            if(PirateNode == nullptr) {
                return output_t<int>(StatusType::FAILURE);
            }
            auto Pirate = PirateNode->value;
            int treasure = Pirate->getTreasure();
            return output_t<int>(treasure);
    }

    catch (const std::bad_alloc& bad) {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> Ocean::get_cannons(int shipId){
    if(shipId <=0 )
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if(ships->size()==0)
    {
        return output_t<int>(StatusType::FAILURE);
    }
    try{

        pair shipIdPair=pair(shipId, shipId);
        auto shipNode=this->ships->find(shipIdPair);

        if(shipNode== nullptr)
        {
            return output_t<int>(StatusType::FAILURE);
        }

        auto shipObj = shipNode->value;
        return output_t<int>(shipObj->getcannons());
    }

    catch (const std::bad_alloc& bad)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

output_t<int> Ocean::get_richest_pirate(int shipId)
{
    if (shipId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    if (ships->size() == 0) {
        return output_t<int>(StatusType::FAILURE);
    }
    try {
        pair shipIdPair = pair(shipId, shipId);
        auto shipNode = ships->find(shipIdPair);
        if (shipNode == nullptr) {
            return output_t<int>(StatusType::FAILURE);
        }
        auto shipObj = shipNode->value;
        if (shipObj->sizeOfPirates() == 0) {
            return output_t<int>(StatusType::FAILURE);
        }
        return shipObj->getRich();

    } 
    catch (const std::bad_alloc& bad) 
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
}

StatusType Ocean::ships_battle(int shipId1,int shipId2)
{
    if(shipId1<=0 || shipId2<=0 || shipId1==shipId2)
    {
        return StatusType::INVALID_INPUT;
    }

    if(ships->size()<=1) {
         return StatusType::FAILURE;
    }

    try{
            pair ship1IdPair=pair(shipId1, shipId1);
            auto shipNode1= this->ships->find(ship1IdPair);

        if(shipNode1== nullptr)
        {
            return StatusType::FAILURE;
        }

            pair ship2IdPair=pair(shipId2, shipId2);
         auto ship2Node  =this->ships->find(ship2IdPair);

        if(ship2Node== nullptr)
        {
            return StatusType::FAILURE;
        }

        std::shared_ptr<ship>ship1=shipNode1->value;
        std::shared_ptr<ship>ship2=ship2Node->value;
        ////////////////////////////////need to implement
        int cannons1 = ship1->getcannons(), size1 = ship1->sizeOfPirates();
        int cannons2 = ship2->getcannons(),size2 = ship2->sizeOfPirates();
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

/// Test the treason function

/*#include "cassert"

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

    //StatusType result = ocean.treason(sourceShipId, destShipId);

   // int longestPiratesrcId = sourceShip->getFirstPirate();
    int longestPiratedestId = destShip->getFirstPirate();

    pair idpair =pair(longestPiratedestId,longestPiratedestId);
    auto longestPiratesrc = ocean.pirateById->find(idpair)->value;

    // Action: Perform treason


    // Verify: Check if the pirate was successfully transferred
    assert(result == StatusType::SUCCESS); // Ensure treason was successful
    assert(longestPiratesrcId != pirateId1); // Assuming pirateId1 was the longest-staying pirate
    assert(longestPiratedestId == pirateId1); // Ensure pirateId1 is now in the destination ship
    std::cout<<longestPiratesrc->getTreasurePure()<<std::endl;
        ocean.print_avl_tree();
    std::cout << "Test passed: Treason function works as expected." << std::endl;
}
*/
// int main() {
//     Ocean o;
//     o.add_ship(1,12);
//     o.add_ship(2,15);
//     o.add_pirate(5,1,1);
//     o.add_pirate(7,1,30);
//     // for(int i = 1 ; i < 8 ; i++){
//     //     o.add_pirate(i,1,i);
//     // }
//     //     for(int i = 8 ; i < 27 ; i++){
//     //     o.add_pirate(i,2,i);
//     // }

//     // for(int i = 1 ; i < 8 ; i++ ){
//     //     o.treason(1,2);
//     // }
//     // o.remove_pirate(26);

//     o.update_pirate_treasure(5,50);
//     o.update_pirate_treasure(7,50);
//     std:: cout << o.get_treasure(5).ans() << std ::endl;
//     std:: cout << o.get_richest_pirate(1).ans() << std ::endl;
//     std:: cout << "_____________________" << std ::endl;
//     // std:: cout << o.get_richest_pirate(2).ans() << std ::endl;
//     // std:: cout << "_____________________" << std ::endl;
//     o.ships->find(pair(1,1))->value->pirateByTreasure->print();



    
//     return 0;
// }