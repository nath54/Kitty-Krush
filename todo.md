# ToDo

## Architecture

- [x] Passer les layers de tuiles en dictionnaire
- [x] Modifier les (x,y) en Coord

## Règles de jeu

- [ ] Implémenter les bandits
- [ ] Implémenter le calcul des palissade/défense des unités
- [ ] Implémenter le repoussement des troupes si elles étaient derrière une palissade

## Fonctions à coder dans Map

- [ ] `void_reset_color_layer()` : Vider le dictionnaire
- [ ] `void reset_entity_layer()` : Vider le dictionnaire
- [ ] `void set_tile_color(usint x, usint y, short tile_color)` (tile->convert_type)
- [ ] `void set_tile_entity(usint x, usint y, usint level, bool type)` : ajouter l'entité au dictionnaire
=> bool type : TRUE = unit, FALSE = building
- [ ] `short get_tile_color(usint x, usint y)` (tile->_color)
- [ ] `Element* get_tile_entity(usint x, usint y)` : renvoyer le pointeur sur l'élémenent (find du dictionnaire)
- [ ] `Province* get_tile_province(usint x, usint y)` : retourne la province à laquelle appartient la tuile
- [ ] `usint get_player_toplay()` : retourne le numéro du joueur dont c'est le tour
- [ ] `bool action_move_entity(usint x1, usint y1, usint x2, usint y2)`: retourne TRUE si une entité présente sur x1y1 peut aller sur x2y2
- [ ] `bool action_new_entity(usint x, usint y, usint level, bool type)` : retourne TRUE si le joueur peut poser l'entité demandé à cet endroit
- [ ] `bool action_end_turn()` : renvoyer TRUE
- [ ] `list<Coord> possible_movements_of_entity(int x, int y)` : Renvoie la liste des cases où l'entité à la position (x, y) peuvent se déplacer
