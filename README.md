# Kitty Krush

| CERISARA Nathan | JACQUET Ysée |
| :-------------: | :----------: |

## Description

KItty Krush is a game inspired from **konkr.io**.
You play your cat unities to conquer territories and defeat your opponents. Make your army stronger and improve your economy to achieve victory!

## Organization

We followed a standard global organization for C++ projects with a ressource file, a source file, an include file and a makefile.

To run the game, use `./build_and_run.sh`.

### Classes

*TODO: Organisation des classes OwO*

## Rules differences

| KITTY KRUSH | KONKR |
| ----------- | ----- |
| <center>**Treasury**</center> | <center>**Treasury**</center> |
| Income coins are stored into the province, and if necessary the treasury divided by percentage of tiles for each splited province. | Income coins are stored into the nearest town. |
| Units are paid by the province treasury. | Units are paid by the nearest town. |
| <center>**Bandits**</center> | <center>**Bandits**</center> |
| A new bandit camp is created only if there are bandits and no bandit camp. | A new bandit camp is created if there's bandit but no bandit camp in a 5 tile radius and there's a neutral tile available somewhere on the map. |
| Bandits can not go next to an unit. | Bandits can go next to an unit. |
| Bandits coins are fairly distributed between the different bandit camps. | Bandits coins are stored to the nearest bandit camp. |


## Tests

*TODO: Faire des tests pour vérifier que le jeu fonctionne bien, et les décrire ici*

## Conclusion

Well done, it was really fun to play with you ! ⸜(｡˃ ᵕ ˂ )⸝♡
