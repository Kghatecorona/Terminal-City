# Terminal-City
A C++ city simulation built entirely for the terminal, implementing inheritance, polymorphism, and data management to model realistic urban growth.
<br>
TerminalCity/
├── include/                # Header files (12)<br>
│   ├── building.h<br>
│   ├── residential.h<br>
│   ├── industrial.h<br>
│   ├── farm.h<br>
│   ├── road.h<br>
│   ├── city.h<br>
│   ├── city_impl.h<br>
│   ├── statsmanager.h<br>
│   ├── eventmanager.h<br>
│   ├── logger.h<br>
│   ├── filehandler.h<br>
│   └── exceptions.h<br>
│<br>
├── src/                    # Source files (10)<br>
│   ├── main.cpp<br>
│   ├── building.cpp<br>
│   ├── residential.cpp<br>
│   ├── industrial.cpp<br>
│   ├── farm.cpp<br>
│   ├── road.cpp<br>
│   ├── statsmanager.cpp<br>
│   ├── eventmanager.cpp<br>
│   ├── logger.cpp<br>
│   └── filehandler.cpp<br>
|
├── Makefile<br>
└──README.md<br>
<br>

<H3>Major Features</H3>

Abstract Building base class with 4 derived types<br>

City<T> template class for grid-based city management<br>

4 custom exception classes<br>

Dedicated logging system (game.log)<br>

Comprehensive statistics manager (Population, Gold, Happiness, Environment)<br>

Random event generator (disasters, bonuses)<br>

Save/Load system using binary file handling<br>

Input validation and a clean, menu-driven interface<br>
<br>

Compilation Commands<br>
make           # Build
make run       # Build & run
make clean <br>


<br>
Members : 
<br>
Kavyansh Gupta (241030392)
<br>
Aryan (241030433)
<br>
Wani Priya (241030394)
<br>
Shristi Jain (241030388)
