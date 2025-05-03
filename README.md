# Kitty Krush

| CERISARA Nathan | JACQUET Ysée |
| :-------------: | :----------: |

## Description

KItty Krush is a game inspired from **[konkr.io](https://www.konkr.io/)** (scholar project).
You play your cat unities to conquer territories and defeat your opponents. Make your army stronger and improve your economy to achieve victory!

**To run the game, use** `./build_and_run.sh`.
If you want to only build it, use `./build.sh`.

> ⚠️ The working directory must be the root of the project.

## Organization

We followed a standard global organization for C++ projects with a ressource file, a source file, an include file and a makefile.

###  Main Classes

|   Class       | Description |
| :--------:    | ----------- |
| `Coord`       | The skeleton of this project: a simple 2d vector (x, y) that represents a `Tile` (or `Element`) coordinates. |
| `Element`     | Entities you can find on the map. There are two types (implemented in two subclasses), `Unit` and `Building`. |
| `Tile`        | To describe each tile on the map. Can be linked to an `Element`. |
| `Province`    | Block of `Tile`s belonging to a player. Must have one town at least to exist. |
| `Map`         | Stores all `Tile`s, `Province`s and the list of bandit `Element`s. |
| `GameModel`   | Has the overview of the game (precisely its `Map`) and its players. |
| `MainGame`    | Do the different links between game (`GameModel`) and display (`MainView`) to execute tasks simultaneously. |
| `MainView`    | Manages the SDL environment & SDL Window. |
| `WindowElt`   | Represents an element that will be drawn, ex: `WindowEltText` for text, `WindowEltSprite` for sprites, `WindowEltButton` for buttons... |
| `Event`       | Represents an low level SDL event, ex: `EventMouseMotion`, `EventMouseClick`, `EventMouseDragging`, `EventKeyUp`... |


## Menu

- `Continue game` : allows player to continue his last game, when quitted with _back_ button.
- `Create a new map` : use the map creator to imagine your own map, or use the random generator (_generate_ button) to create one automatically and randomly.
- `2p_green_island`, `3p_stranded_on_beach` : predefined test maps (2 or 3 players).
- `map_created` : the last created map (saved from the map generator when use _back_ button).

## Rules differences

| KITTY KRUSH | KONKR |
| ----------- | ----- |
| <center>**Treasury**</center> | <center>**Treasury**</center> |
| Income coins are stored into the province, and if necessary the treasury divided by percentage of tiles for each splited province. | Income coins are stored into the nearest town. |
| Units are paid by the province treasury. | Units are paid by the nearest town. |
| <center>**Bandits**</center> | <center>**Bandits**</center> |
| A new bandit camp is created only if there are bandits and no bandit camp (on a random neutral tile on the map). | A new bandit camp is created if there's bandit but no bandit camp in a 5 tile radius and there's a neutral tile available somewhere on the map. |
| Bandits can not go next to an unit. | Bandits can go next to an unit. |
| Bandits coins are fairly distributed between the different bandit camps. | Bandits coins are stored to the nearest bandit camp. |

## Conclusion

We hope you have fun on Kitty Krush! ⸜(｡˃ ᵕ ˂ )⸝♡
