# Add Missing Food Items & Update Item Mappings (Beer & 15 Food Hazards)

## Overview
The user approved the plan with two specific requirements:
1. Order all 15 food hazards depending on **real-life food calories** (USDA / standard portion) and scale their player effects accordingly (stamina drain, speed slow %, duration).
2. Add a metric for **appearance frequency** (how often an item appears / spawn probability weight).
3. Replace item 13 (Cake) with **Beer** across all scripts, assets, source files, comments, and docs.

---

## 18-Item Spritesheet Inventory (`items_16.png`)
The `items_16.png` spritesheet contains 18 items (9 columns x 2 rows):
- **Collectibles (Money)**:
  - Frame 11: Dollar Bills stack (`ENTITY_COLLECTIBLE_BILLS`, `SPRITE_ITEM_BILLS`)
  - Frame 12: Faceted Diamond (`ENTITY_COLLECTIBLE_DIAMOND`, `SPRITE_ITEM_DIAMOND`)
- **Power-Up**:
  - Frame 9: Coffee Mug (`ENTITY_POWERUP_COFFEE`, `SPRITE_ITEM_COFFEE`)
- **15 Food Hazards** ordered strictly by real-life calorie content.

---

## Food Hazard Calorie & Balance Matrix (Strictly Calorie-Ordered)

| Calorie Rank | Food Hazard | Frame | Real-Life Calorie Content (USDA / Standard Serving) | Appearance Frequency (% & Weight) | Speed Slow % | Duration (frames / sec) | Stamina Drain | Gameplay Profile |
|:---:|:---|:---:|:---|:---:|:---:|:---:|:---:|:---|
| 1 | **Strawberry** | 4 | **~6 kcal** (1 large berry / ~32 kcal per 100g) | **Common (10%)** | -10% | 20f (~0.33s) | 4 | Micro-snack: quick nibble, negligible fatigue |
| 2 | **Carrot** | 15 | **~25 kcal** (1 medium raw 7" carrot) | **Common (9%)** | -12% | 24f (~0.40s) | 6 | Crunchy root: light healthy chew |
| 3 | **Candy** | 10 | **~40 kcal** (1-2 pieces hard wrapped candy) | **Common (8%)** | -14% | 28f (~0.47s) | 8 | Sugar spike: quick sticky jaw lock |
| 4 | **Cherries** | 5 | **~50 kcal** (cluster / small bowl ~10 cherries) | **Common (9%)** | -16% | 32f (~0.53s) | 10 | Tart berries: quick pause to spit pits |
| 5 | **Watermelon** | 7 | **~86 kcal** (1 fresh triangle wedge slice) | **Common (8%)** | -18% | 36f (~0.60s) | 12 | Juicy wedge: sloshing heavy water belly |
| 6 | **Corn** | 8 | **~90 kcal** (1 medium ear sweet corn) | **Uncommon (7%)** | -22% | 44f (~0.73s) | 15 | Cob chew: buttered corn stuck in teeth |
| 7 | **Sushi** | 16 | **~120 kcal** (2 nigiri pieces / small roll) | **Uncommon (7%)** | -25% | 50f (~0.83s) | 18 | Wasabi kick: nasal flare and rice heaviness |
| 8 | **Beer** | 13 | **~150 kcal** (12 fl oz mug of regular beer) | **Rare (4%)** | -35% | 120f (~2.00s) | 25 | Drunken buzz: long lingering disorientation |
| 9 | **Donut** | 14 | **~220 kcal** (1 glazed yeast ring donut) | **Uncommon (6%)** | -38% | 65f (~1.08s) | 30 | Glazed sugar rush & heavy crash |
| 10 | **Ice Cream** | 6 | **~250 kcal** (1 standard single-scoop waffle cone) | **Rare (4%)** | -55% | 100f (~1.67s) | 42 | Brain freeze: intense cold shock paralysis |
| 11 | **Drumstick** | 0 | **~270 kcal** (1 fried chicken leg with skin/breading) | **Uncommon (6%)** | -32% | 75f (~1.25s) | 28 | Greasy poultry: slippery fingers and greasy slump |
| 12 | **Pizza** | 1 | **~290 kcal** (1 regular slice pepperoni/cheese) | **Uncommon (6%)** | -30% | 70f (~1.17s) | 26 | Greasy slice: heavy molten cheese carb drag |
| 13 | **Hotdog** | 3 | **~320 kcal** (1 standard beef hotdog + bun) | **Uncommon (6%)** | -34% | 80f (~1.33s) | 32 | Stadium dog: dense processed meat & soft bun |
| 14 | **Pretzel** | 17 | **~390 kcal** (1 large Bavarian salted soft pretzel) | **Uncommon (6%)** | -36% | 85f (~1.42s) | 35 | Salty giant knot: dry throat, dense carb weight |
| 15 | **Burger** | 2 | **~540 kcal** (1 double beef cheeseburger with bun) | **Rare (4%)** | -50% | 110f (~1.83s) | 48 | Calorie bomb: ultimate food coma & exhaustion |

*Appearance Frequency Metrics:*
- Total probability sum = **100%**.
- **Common items (8-10%)**: Lighter snacks (Strawberry, Carrot, Candy, Cherries, Watermelon) appear frequently, offering maneuverability without rapid death.
- **Uncommon items (6-7%)**: Medium meals (Corn, Sushi, Donut, Drumstick, Pizza, Hotdog, Pretzel) provide moderate slowdowns.
- **Rare items (4% each)**: High-impact hazards (Beer buzz, Ice Cream brain freeze, Burger food coma) appear sparsely but demand player evasion.

---

## Proposed Changes

### 1. Sprites & Asset Generation
- **[scripts/convert_sprites.py](file:///home/dorito/Developer/arduboy/supermassive-whitehole/scripts/convert_sprites.py)**:
  - Correct line 392 comment: `// 13: Beer        14: Donut    15: Carrot       16: Sushi`.
  - Update `SPRITE_ITEM_BEER = 13` and add `SPRITE_ITEM_CAKE = 13` alias.
  - Re-run script to regenerate `assets/sprites.h`.
- **[assets/sprites.h](file:///home/dorito/Developer/arduboy/supermassive-whitehole/assets/sprites.h)**:
  - Automatically regenerated with updated comments and constants.

### 2. Entity Enums & Spawning
- **[src/game/entity.h](file:///home/dorito/Developer/arduboy/supermassive-whitehole/src/game/entity.h)**:
  - Order `EntityType` enum strictly by calorie rank (4 to 18):
    `STRAWBERRY` (4), `CARROT` (5), `CANDY` (6), `CHERRIES` (7), `WATERMELON` (8), `CORN` (9), `SUSHI` (10), `BEER` (11), `DONUT` (12), `ICECREAM` (13), `DRUMSTICK` (14), `PIZZA` (15), `HOTDOG` (16), `PRETZEL` (17), `BURGER` (18).
  - Add aliases: `ENTITY_FOOD_APPLE`, `ENTITY_FOOD_CAKE`, `ENTITY_FOOD_TACO`, `ENTITY_FOOD_CHICKEN`, `ENTITY_FOOD_FRIES`.
  - Update `ENTITY_FOOD_FIRST = 4`, `ENTITY_FOOD_LAST = 18`, `ENTITY_FOOD_COUNT = 15`.
  - Update comments.
- **[src/game/entity.cpp](file:///home/dorito/Developer/arduboy/supermassive-whitehole/src/game/entity.cpp)**:
  - `Entity::isFood()`: check `(type >= ENTITY_FOOD_STRAWBERRY && type <= ENTITY_FOOD_BURGER)`.
  - `EntityManager::spawn()`: set 8x8 hitboxes for all 15 food hazards.

### 3. Food Configuration & Appearance Frequencies
- **[src/game/config.h](file:///home/dorito/Developer/arduboy/supermassive-whitehole/src/game/config.h)**:
  - Add `FOOD_*_SLOW_DURATION`, `FOOD_*_SLOW_INTENSITY`, `STAMINA_FOOD_*_DRAIN`, and `FOOD_*_SIZE` for all 15 foods ordered by calories.
  - Add `FOOD_SPAWN_CUMULATIVE_THRESHOLDS[15]` array in PROGMEM representing the appearance frequency distribution.

### 4. Player Slow & Stamina Handling
- **[src/game/player.cpp](file:///home/dorito/Developer/arduboy/supermassive-whitehole/src/game/player.cpp)**:
  - Expand `Player::applyFoodSlow()` switch statement for all 15 food items with their exact durations, intensities, and stamina drain.

### 5. Game Loop & Rendering
- **[src/game/game.h](file:///home/dorito/Developer/arduboy/supermassive-whitehole/src/game/game.h)**:
  - Update line 276 comments to document all 15 food items in calorie order.
- **[src/game/game.cpp](file:///home/dorito/Developer/arduboy/supermassive-whitehole/src/game/game.cpp)**:
  - In `updatePlaying()`, roll random 0..99 and use `FOOD_SPAWN_CUMULATIVE_THRESHOLDS` to select the food entity based on appearance frequency.
  - In `renderEntities()`, map all 15 food types to their respective `SPRITE_ITEM_*` frames.

### 6. Documentation
- **[docs/gdd.md](file:///home/dorito/Developer/arduboy/supermassive-whitehole/docs/gdd.md)**:
  - Update food hazards section with full calorie table, effects, and appearance frequencies.
- **[docs/architecture.md](file:///home/dorito/Developer/arduboy/supermassive-whitehole/docs/architecture.md)**:
  - Update M2 description with all 15 foods.

---

## Verification Plan
1. `python3 scripts/convert_sprites.py` -> regenerates `assets/sprites.h`.
2. `./build.sh --build-only` -> compile and verify Flash/SRAM fit within 28,672 / 2,560 limits.
3. `./scripts/package_dist.sh` -> update web distribution.
4. Browser test at `http://localhost:8000/dist/web/` -> verify new food items spawn according to appearance frequencies, collisions trigger stamina drain and slow badges, and Beer/Burger/Ice Cream produce the expected heavy responses.
