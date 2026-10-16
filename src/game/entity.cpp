// =============================================================================
// entity.cpp — Entity & EntityManager Implementation
// =============================================================================
//
// MILESTONE: M2 (Entity Spawning & Collision Detection)
//
// FOR IMPLEMENTING AGENTS:
//   Implement all methods as documented in entity.h.
//   Key points:
//   - spawn() must find first ENTITY_NONE slot and configure it
//   - despawn() just calls entity.reset()
//   - Keep it simple — entities are static data, logic lives in Game/Physics
//
// =============================================================================

#include "entity.h"

// -----------------------------------------------------------------------------
// Entity::reset()
// -----------------------------------------------------------------------------
void Entity::reset() {
    x = 0;
    y = 0;
    type = ENTITY_NONE;
    width = 0;
    height = 0;
    active = false;
}

// -----------------------------------------------------------------------------
// Entity::isFood()
// -----------------------------------------------------------------------------
bool Entity::isFood() const {
    return (type >= ENTITY_FOOD_FIRST && type <= ENTITY_FOOD_LAST);
}

// -----------------------------------------------------------------------------
// Entity::isCollectible()
// -----------------------------------------------------------------------------
bool Entity::isCollectible() const {
    return (type == ENTITY_COLLECTIBLE_DIAMOND || type == ENTITY_COLLECTIBLE_BILLS);
}

// -----------------------------------------------------------------------------
// Entity::isPowerup()
// -----------------------------------------------------------------------------
bool Entity::isPowerup() const {
    return (type == ENTITY_POWERUP_COFFEE);
}

// =============================================================================
// EntityManager implementation
// =============================================================================

void EntityManager::init() {
    for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
        entities[i].reset();
    }
}

bool EntityManager::spawn(EntityType type, fp32_t x, fp32_t y) {
    for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
        if (!entities[i].active) {
            entities[i].type = type;
            entities[i].x = x;
            entities[i].y = y;
            entities[i].active = true;

            // Set size based on type
            if (type == ENTITY_COLLECTIBLE_DIAMOND || type == ENTITY_COLLECTIBLE_BILLS) {
                entities[i].width = COLLECTIBLE_SIZE;
                entities[i].height = COLLECTIBLE_SIZE;
            } else if (type == ENTITY_POWERUP_COFFEE) {
                entities[i].width = POWERUP_COFFEE_SIZE;
                entities[i].height = POWERUP_COFFEE_SIZE;
            } else if (type >= ENTITY_FOOD_FIRST && type <= ENTITY_FOOD_LAST) {
                entities[i].width = 8;
                entities[i].height = 8;
            } else {
                entities[i].reset();
                return false;
            }
            return true;
        }
    }
    return false;
}

// -----------------------------------------------------------------------------
// EntityManager::despawn()
// -----------------------------------------------------------------------------
void EntityManager::despawn(uint8_t index) {
    if (index < MAX_ENTITIES) {
        entities[index].reset();
    }
}

// -----------------------------------------------------------------------------
// EntityManager::countActive()
// -----------------------------------------------------------------------------
uint8_t EntityManager::countActive() const {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MAX_ENTITIES; i++) {
        if (entities[i].active) {
            count++;
        }
    }
    return count;
}
