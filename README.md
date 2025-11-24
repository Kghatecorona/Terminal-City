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



<H3>Gameplay Guide</H3>H3><br><br>
Building Types<br>
Code	Type	Cost	Effect<br>
R	Residential	200	+500 population<br>
I	Industrial	300	+100 gold/turn<br>
F	Farm	150	+50 gold/turn<br>
=	Road	100	Infrastructure<br><br>
Main Menu<br><br>

Build Infrastructure<br>

Demolish Building<br>

Next Turn<br>

Save Game<br>

Load Game<br>

Show Building Costs<br>

Exit<br>
<br>
Gameplay Highlights<br><br>

8×10 interactable city grid<br>

Gold / population / happiness management<br>

Random seasonal events<br>

Saves stored in city.dat<br>

Automatic logging in game.log<br>


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
