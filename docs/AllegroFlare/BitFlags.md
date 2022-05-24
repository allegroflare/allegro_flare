```cpp
   AllegroFlare::BitFlags<int32_t> bit_flags;
```

Defines a set of boolean flags.  Note the type `int32_t` is used
for the example above and provides 32 boolean flags.  For the template type, you should use one of the [fixed width integer
types](https://en.cppreference.com/w/cpp/types/integer): `int8_t`, `int16_t`,
`int32_t`, or `int64_t`.

Avoid using `int`, `float`, or other types which do not have a reliably defined fixed width. On typical systems, an `int` might be 32 flags, but on older systems it'll be 16, and on newer could be 64.

### How To Use

You might define a set of predefined flags for objects in your game.

```cpp
enum tile_flag_t
{
  // this is 8 flags, and a dullard (0x00) which isn't a flag
  TILE_FLAG_UNDEF = 0x00,
  TILE_FLAG_BOUNDRY_TOP = 0x01,
  TILE_FLAG_BOUNDRY_BOTTOM = 0x02,
  TILE_FLAG_BOUNDRY_LEFT = 0x04,
  TILE_FLAG_BOUNDRY_RIGHT = 0x08,
  TILE_FLAG_IS_LADDER = 0x10,
  TILE_FLAG_IS_INSTADEATH = 0x20,
  TILE_FLAG_IS_DESTRUCTABLE = 0x40,
  TILE_FLAG_IS_GOAL = 0x80
};
```

Then use a set of `BitFlags` to store when the booleans are switched on or off
for your game object.

```cpp
class Tile
{
public:
   BitFlags<int_16> properties;
};
```

```cpp
Tile tile;
```

```cpp
tile.properties.set(TILE_FLAG_BOUNDARY_TOP); // defines a tile as having a top boundary
```

You can then query the flags to see if the property is set:

```cpp
tile.properties.has(TILE_FLAG_BOUNDARY_TOP); // returns true
tile.properties.has(TILE_FLAG_IS_LADDER);    // returns false
```


