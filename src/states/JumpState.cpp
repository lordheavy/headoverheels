#include "JumpState.hpp"
#include "FallState.hpp"
#include "Behavior.hpp"
#include "Item.hpp"
#include "FreeItem.hpp"
#include "PlayerItem.hpp"
#include "Mediator.hpp"

namespace isomot
{

BehaviorState* JumpState::instance = 0;
  
//--------------------------------------------------------------------------------------------------
JumpState::JumpState() : BehaviorState()
{
  
}

//--------------------------------------------------------------------------------------------------
JumpState::~JumpState()
{
  
}

//--------------------------------------------------------------------------------------------------
BehaviorState* JumpState::getInstance()
{
  if(instance == 0)
  {
    instance = new JumpState();
  }
  
  return instance;
}

//--------------------------------------------------------------------------------------------------
bool JumpState::jump(Behavior* behavior, StateId* substate, const std::vector<JumpMotion>& jumpMatrix, int* jumpIndex)
{
  bool changedData = false;
  StateId displaceStateId = StateWait;
  PlayerItem* playerItem = dynamic_cast<PlayerItem*>(behavior->getItem());
  Mediator* mediator = playerItem->getMediator();
  
  // Movimiento vertical.
  if(!playerItem->addZ(jumpMatrix[*jumpIndex].second))
  {
    // Si no ha podido ascender levanta a todos los elementos que pudiera tener encima.
    if(jumpMatrix[*jumpIndex].second > 0)
    {
      // Para todo elemento que pueda tener encima.
      while(!mediator->isCollisionStackEmpty())
      {
        // Identificador del primer elemento de la pila de colisiones.
        int id = mediator->popCollision();
        
        // El elemento tiene que ser un elemento libre o uno rejilla.
        if((id >= FirstFreeId && (id & 1)) || (id >= FirstGridId && !(id & 1)))
        {
          Item* item = mediator->findItem(id);
          
          // Si el elemento se ha encontrado y es un elemento mortal entonces el jugador muere.
          if(item != 0)
          {
            if(item->isMortal() && playerItem->getShieldTime() <= 0)
            {
              playerItem->getBehavior()->changeStateId(StateStartDestroy);
            }
            // Si no es mortal y es un elemento libre levanta a los elementos que pudiera tener encima.
            else
            {
              FreeItem* freeItem = dynamic_cast<FreeItem*>(item);
              
              if(freeItem != 0)
              {
                // Levanta recursivamente a todos los elementos.
                lift(playerItem, freeItem, jumpMatrix[*jumpIndex].second - (*jumpIndex > 0 && *jumpIndex % 2 == 0 ? 1 : 2));
              }     
            }
          }
        }
      }
      
      // Ahora ya puede ascender.
      playerItem->addZ(jumpMatrix[*jumpIndex].second - (*jumpIndex > 0 && *jumpIndex % 2 == 0 ? 1 : 2));
    }
  }
  
  // El salto es diferente dependiento de la dirección.
  switch(playerItem->getDirection())
  {
    case North:
      // Movimiento hacia el norte.
      changedData = playerItem->addX(-jumpMatrix[*jumpIndex].first);
      displaceStateId = StateDisplaceNorth;
      break;
      
    case South:
      // Movimiento hacia el sur.
      changedData = playerItem->addX(jumpMatrix[*jumpIndex].first);
      displaceStateId = StateDisplaceSouth;
      break;
      
    case East:
      // Movimiento hacia el este.
      changedData = playerItem->addY(-jumpMatrix[*jumpIndex].first);
      displaceStateId = StateDisplaceEast;
      break;
      
    case West:
      // Movimiento hacia el sur.
      changedData = playerItem->addY(jumpMatrix[*jumpIndex].first);
      displaceStateId = StateDisplaceWest;
      break;
      
    default:
      ;
  }
  
  // En caso de colisión en los ejes X o Y se desplaza a los elementos implicados.
  if(!changedData)
  {
    this->propagateStateAdjacentItems(playerItem, displaceStateId);
  }
  // En caso de que el elemento se haya movido se comprueba si hay que desplazar los elementos
  // que pueda tener encima.
  // El desplazamiento a partir de la cuarta fase del salto se establece para que el 
  // jugador pueda librarse de un elemento que tenga encima.
  else if(changedData && *jumpIndex > 4)
  {
    this->propagateStateTopItems(playerItem, displaceStateId);
  }

  // Se pasa a la siguiente fase del salto.
  (*jumpIndex)++;
  
  // Si se han completado todas las fases, el salto termina.
  if(*jumpIndex >= int(jumpMatrix.size()))
  {
    changeState(behavior, FallState::getInstance());
    
    *jumpIndex = 0;
    *substate = StateFall;
  }
  
  return changedData;
}

//--------------------------------------------------------------------------------------------------
void JumpState::lift(FreeItem* sender, FreeItem* freeItem, int z)
{
  // El elemento debe poder cambiar de estado.
  if(freeItem->getBehavior() != 0)
  {
    // Si el elemento es volátil se le comunica que se está empujando.
    if(freeItem->getBehavior()->getId() == VolatileTouchBehavior || freeItem->getBehavior()->getId() == SpecialBehavior)
    {
      freeItem->getBehavior()->changeStateId(StateDisplaceUp, sender);
    }
    // Si el elemento no es el ascensor entonces se levanta.
    else if(freeItem->getBehavior()->getId() != ElevatorBehavior)
    {
      // Si no se puede levantar, se toma el elemento con el que choca para levantarlo.
      if(!freeItem->addZ(z))
      {
        Mediator* mediator = freeItem->getMediator();
        
        // Para todo elemento que pueda tener encima.
        while(!mediator->isCollisionStackEmpty())
        {
          FreeItem* topItem = dynamic_cast<FreeItem*>(mediator->findItem(mediator->popCollision()));
          
          if(topItem != 0)
          {
            // Levanta recursivamente a todos los elementos.
            lift(sender, topItem, z);
          }
        }
        
        // Ahora ya puede ascender.
        freeItem->addZ(z);
      }
    }
  }
}

}
