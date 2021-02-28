#  <img src="https://github.com/SvetlanaGolub/MimiDove/blob/master/dove.png" width="80" height="80">MimiDove

Tool to dump passwords from **gnome-keyring-daemon** process memory.

## Features :
- Dump passwords from process (based on @huntergregal's [MimiPenguin](https://github.com/huntergregal/mimipenguin)) :
- Overwriting passwords found in memory (this idea was implemented in Python2 by @n1nj4sec's [MimiPy](https://github.com/n1nj4sec/mimipy))
- Smart search for passwords based on memory location 
- Supports Unicode characters  

## Building
* Run `make` in the root directory of the project
* To build a debug binary with debug prints run `make debug`
* To build a static linked binaries run `make static`


## Usage
```bash
./mimidove [--clean]

optional argument:
  --clean                clean found passwords from memory
```

## Contact
by mail: glb.svtln@gmail.ru  

## Special thanks
* gentilkiwi for Mimikatz
* huntergregal for MimiPenguin
* n1nj4sec for MimiPy
