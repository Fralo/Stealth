# Stealth: RTS game
2D RTS game built with SFML2

[![Università degli studi di Firenze](https://i.imgur.com/1NmBfH0.png)](https://ingegneria.unifi.it)

Made by [Leonardo Fralini](https://github.com/Fralo), [Mattia Marilli](https://github.com/mattiamarilli) and [Edoardo Viviani](https://github.com/vivedo)

### Dependencies
 - cmake v3.1
 - libsfml v2.5

### Build
```sh
$ git clone https://github.com/Fralo/Stealth.git --recursive
$ mkdir Stealth/build && cd Stealth/build
$ cmake ../
$ make
```

### Maps
Maps are built using [Tiled](https://www.mapeditor.org/), an open source tiled map edito and exported in [TMX](https://doc.mapeditor.org/en/stable/reference/tmx-map-format/) (Tiled Map XML) format.
Stealth loads all tiled maps resources from *res/maps* directory.

Tilesets need to be included in the TMX file, and the map has to contains the following objects:
 - A *Layer Group* named _background_
 - An *Object Group* named _objects_

All *Tile Layers* inside _background_ are immutable and will be drawn on the background following their order.

All *Objects* needs to use tiles that have defined 2 collision objects:
 - A *Rectangle* with type _cbox_, which will represent the object collison box
 - A *Point* with type _cx_, which will represent the y plane the object will be drawn
 
Objects can have properties specified in the 'custom property' tab of the TMX editor (tileset properties are ignored):

| property name | default value | accepted values |
| --- | --- | --- |
| destroyable | false | true, false |
| explosive | false | true, false |