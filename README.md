# so_long

A small 2D tile game in C with MiniLibX: collect every item on the map, then reach the exit. A 42 Common Core project about windows, sprites and event loops.

## Build

Needs X11 development headers (`libx11-dev`, `libxext-dev`) on Linux.

```bash
make
```

## Run

```bash
./so_long maps/valid/map.ber
```

`maps/valid/` holds playable maps, `maps/invalid/` holds broken ones to check that the parser rejects them.

### Controls

`W` `A` `S` `D` to move, `ESC` to quit. The window's close button works too.

## The map format

A `.ber` file is a rectangular grid of characters:

| Char | Meaning |
|---|---|
| `1` | wall |
| `0` | floor |
| `P` | player start |
| `C` | collectible |
| `E` | exit |

```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## Validation

A map is only loaded if it is rectangular, fully enclosed by walls, and contains exactly one player and one exit with at least one collectible. On top of that, a **flood fill** from the player's position checks that every collectible and the exit are actually reachable — a map that parses but cannot be finished is rejected.

The move counter is printed to the terminal on every step.

## Layout

```
src/parsing/   map reading and validation, flood fill
src/init/      window and image setup
src/utils/     helpers
src/lib/libft/ my own C library
xpm/           sprites
maps/          valid and invalid maps
```

Sprites are Pikmin-themed: the collectibles are red, yellow and blue Pikmin.
