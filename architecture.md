# Global Project Architecture and Class Description

We will be inspired by a Model-View-Controller architecture (Separating the display process from the controller, which means creating a separate game model, upon which we will independently depend the display and the controller).

We will also try to do as much Polymorphism as possible and create small libraries for vectors / mathematical, game logic, and classic computer operations...

## MVC - Model

Class Player:
    - player_name (str): unique identifier and display name of the player
    TODO: the rest will depend on the type of game

GameModel:
    - players (dict[str, Player]): players are stored here, indexed by there player_name


## MVC - Controller

Class PlayerControler:
    - player_name (str): identifier linking to player model
    TODO: the rest will depend on the type of game


## MVC - View

Class MainView:
    - game_model_ptr (GameModel*): Pointer toward the game model


## Other

TODO: add the other stuff here or in other sub-categories.


