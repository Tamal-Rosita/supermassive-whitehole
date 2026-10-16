# Supermassive Whitehole — Game Design Document

## Overview

| | |
|---|---|
| **Title** | Supermassive Whitehole |
| **Platform** | Arduboy (128×64, 1-bit, ATmega32u4) |
| **Jam** | [1-Bit Jam 14](https://itch.io/jam/1-bit-jam-14) |
| **Genre** | Top-down arcade survival / score attack |
| **Controls** | D-pad (8-dir) + A (accelerate) + B (brake) |

A fat man runs on a pseudo-3D top-down infinite plane, dodging delicious food (Pizza, Burger, Donut, and brain-freezing Ice Cream) and fleeing a pursuing supermassive whitehole. Inspired by the car control in [Crates](https://jessemillar.itch.io/crates).

---

## Core Mechanics

### Human-on-Foot Controls (Agile Steering & Small Impulse)
- **D-pad (8 directions + idle)**: Steers agilely with direct human responsiveness. Humans turn on foot much faster than wheeled vehicles, redirecting velocity in 2–3 frames.
- **A button (Gas / Walk input)**: Delivers a small, grounded impulse per stride (initial step impulse of 0.25 px/frame, steady 0.040 px/frame build-up), avoiding rocket-like vehicle acceleration.
- **Small Inertia Feedback (`PLAYER_INERTIA = 0.25`)**: Preserves the tactile weight and physical presence of a running fat man without the uncontrollable wide skidding of a car.
- **Natural Foot Drag (`PLAYER_FRICTION = 0.040`)**: Releasing A brings the player to a smooth, natural stop within ~20 frames (~0.33 sec / 2–3 strides) instead of gliding on ice.
- **B button (Brake)**: Active foot-plant deceleration (`PLAYER_BRAKE_FRICTION = 0.12`), bringing the runner to a rapid emergency stop in ~8 frames.

### Blackhole Entity
Properties translated from real black hole physics:
- **Mass**: Gravitational pull strength on nearby entities (constant)
- **Spin**: Visual rotation effect (cosmetic only)
- **Charge**: Attraction radius — how far gravity reaches (increases over time)

The blackhole tracks the player's position at a speed that linearly increases over time.

### Food Obstacles
| Type | Shape | Slow Duration | Slow Intensity |
|------|-------|---------------|----------------|
| Pizza | Triangle | 0.5 sec | −15% speed |
| Burger | Square | 1.0 sec | −30% speed |
| Donut | Circle | 1.5 sec | −50% speed |

### Collectibles & Scoring
- **Diamond Gem**: Faceted gemstone (+10 points base * combo multiplier)
- **Dollar Bills**: Stack of cash with `$` glyph (+25 points base * combo multiplier)
- Streak combo multiplier: consecutive diamond/bills/power-up collections without hitting food increase multiplier (1x..4x), awarding up to +100 points per item
- Passive score: +1 point per second survived
- High score persisted to EEPROM

### Whitehole Risk-Reward Money Distribution
- **Whitehole Orbit Proximity**: 80% of money items (Diamonds and Bills) spawn in an orbital ring around the whitehole, creating high risk/reward tension.
- **Attraction Force Safety Clearance**: Items spawn at $R \ge \text{FP\_TO\_INT}(bhCharge) + \text{MONEY\_BH\_SAFE\_BUFFER}$ (starts at $30 + 20 = 50$ px), ensuring neither the collectible nor the player gets pulled in by the whitehole's gravitational force (M3) during pickup.
- **Decaying Distribution Curve**: Within the orbit ring ($R \in [R_{safe\_min}, R_{safe\_min} + 40]$), spawn distance uses a decaying density function ($\Delta r = \min(u_1, u_2)$) where 75% of money spawns in the inner half of the ring, concentrating loot close to the danger zone.
- **Dynamic Growth Compatibility**: As the whitehole's mass and charge grow over time (M3), the safe spawning perimeter automatically scales outwards.

### Power-Ups
- **Coffee Mug**: Grants +35% turbo speed and +50% acceleration burst for 3 seconds (180 frames) and cleanses any active food slow debuff immediately.

### Spacing & Item Density
- Generous spawn interval (initial 180 frames / ~3.0s, down to 60 frames / ~1.0s)
- Guaranteed `MIN_ITEM_SEPARATION` of 45 world units between all items to prevent clutter and ensure readability at high flight speeds
- Food hazards and coffee spawn along the player's flight path (55–120px ring with movement direction bias)

### Infinite Plane
- Camera follows player
- Pseudo-3D perspective ground grid fills the entire 128×64 screen
- Vanishing point placed above the screen (y=-10) for dramatic perspective convergence
- No visible horizon line — objects recede toward the top of the screen and scroll off naturally
- Zero-allocation static object pool (12 entities max) for spawning and despawning

---

## Game States

```
TITLE → (Press A) → PLAYING → (Blackhole catches player) → GAME OVER
                                                             ↓ A → TITLE
                                                             ↓ B → PLAYING (retry)
```

---

## Difficulty Curve (Linear)
- Blackhole speed: increases by 1/256 per frame
- Blackhole charge (gravity radius): increases by 1/256 per frame
- Spawn interval: decreases by 1 frame every 4 seconds, min 60 frames
- Whitehole absorbs money and food, increasing mass and charge (M3)

---

## Technical Constraints
- **RAM**: 2.5 KB total — static allocation only, no `new`/`malloc`
- **Flash**: 32 KB — code + PROGMEM data
- **Math**: Q8.8 fixed-point (no floats)
- **Entities**: Max 12 on-screen (168 bytes)
- **Display**: 128×64 monochrome OLED
- **Frame rate**: 60 FPS target

---

## Art Style
1-bit (black and white) using dedicated PROGMEM bitmap sprites:
- **Player**: 16x16 pixel character (`player_static.png`) with slow-debuff blinking
- **Whitehole**: 32x32 animated swirling celestial hazard (4 frames, `whitehole_32.png`)
- **Collectibles (Money)** (`items_16.png`):
  - **Diamond**: 16x16 faceted gem (Frame 12, +10 pts)
  - **Dollar Bills**: 16x16 bill stack with `$` (Frame 11, +25 pts)
- **Power-Up**: 16x16 Coffee Mug (`items_16.png`, Frame 9, +speed & cleanse)
- **Food Hazards (15 Types Strictly Ordered by Real-Life Calories)** (`items_16.png`):
  1. **Strawberry**: ~6 kcal (Frame 4, Common 10%, -10% speed for 0.33s, 4 stamina drain)
  2. **Carrot**: ~25 kcal (Frame 15, Common 9%, -12% speed for 0.40s, 6 stamina drain)
  3. **Candy**: ~40 kcal (Frame 10, Common 8%, -14% speed for 0.47s, 8 stamina drain)
  4. **Cherries**: ~50 kcal (Frame 5, Common 9%, -16% speed for 0.53s, 10 stamina drain)
  5. **Watermelon**: ~86 kcal (Frame 7, Common 8%, -18% speed for 0.60s, 12 stamina drain)
  6. **Corn**: ~90 kcal (Frame 8, Uncommon 7%, -22% speed for 0.73s, 15 stamina drain)
  7. **Sushi**: ~120 kcal (Frame 16, Uncommon 7%, -25% speed for 0.83s, 18 stamina drain)
  8. **Beer**: ~150 kcal (Frame 13, Rare 4%, -35% speed for 2.00s, 25 stamina drain — drunken buzz)
  9. **Donut**: ~220 kcal (Frame 14, Uncommon 6%, -38% speed for 1.08s, 30 stamina drain)
  10. **Ice Cream**: ~250 kcal (Frame 6, Rare 4%, -55% speed for 1.67s, 42 stamina drain — brain freeze)
  11. **Drumstick**: ~270 kcal (Frame 0, Uncommon 6%, -32% speed for 1.25s, 28 stamina drain)
  12. **Pizza**: ~290 kcal (Frame 1, Uncommon 6%, -30% speed for 1.17s, 26 stamina drain)
  13. **Hotdog**: ~320 kcal (Frame 3, Uncommon 6%, -34% speed for 1.33s, 32 stamina drain)
  14. **Pretzel**: ~390 kcal (Frame 17, Uncommon 6%, -36% speed for 1.42s, 35 stamina drain)
  15. **Burger**: ~540 kcal (Frame 2, Rare 4%, -50% speed for 1.83s, 48 stamina drain — food coma)

---

## Milestones
| Phase | Deliverable | Status |
|-------|-------------|--------|
| M0 | Project scaffold, architecture, HAL interfaces | ✅ Complete |
| M1 | Player movement with hybrid inertia physics, perspective ground grid | ✅ Complete |
| M2 | Entity spawning, object pool, collision detection, power-ups, scoring | ✅ Complete |
| M3 | Blackhole chase, gravity pull, difficulty ramp, absorption growth | ✅ Complete |
| M4 | Polished UI (title, game over, HUD), 2D spacetime grid curvature | ✅ Complete |
| M5 | Real sprites, visual effects, audio HAL, SFX, ambient pulse | ✅ Complete |
| M6 | Playtesting, balance tuning, jam submission | 📋 Planned |
