ECS game engine made in c++ with graphics help from sfml.




## TODO
- gather all TODOs here


### Engine
- separate most of Bomberman mechanics into a separate class, such as Game
- Game probably inhertits Engine
- handle input capturing in sInput() instead of in whatever order it happens right now in main.cpp
- improve movement (1 wide corridors require pixel-perfect alignment)
	- allow player to snap into place if overlap is small enough in direction of motion


### Scenes
- implement keybinding modification
- implement help (info) button

### Misc/Rendering
- change the order in which entities are rendered (ie implement some ad hoc Z index for each entity/tag)
- show FPS
- show player inventories
- different drop rates for the various buffs (eg bomb capacity and arm length should be far more common)

### Component
- move all the buffs from BMentity.h to component.h




## Known Bugs
- Currently map has vertical lines of missing pixels; likely due to float->int conversions
- bomb size becomes too large if window is resized
- drops get deleted by flame on the next flame because flames linger for 0.5s after explosion
	- temporary fix: flame-drop collisions are disabled
- scene switching does not always restart the game properly