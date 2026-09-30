cmake_minimum_required(VERSION 3.28)
project(RepProj C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(RepProj
        main.c
        code/commandes.h
        code/commandes.c
        code/graphe.c
        code/graphe.h
        code/programme.c
        code/programme.h
        code/algos.c
        code/algos.h
        code/dot.c
        code/dot.h
        code/especes.c
        code/especes.h
        code/connexite.c
        code/connexite.h
        code/maillons.c
        code/maillons.h
        code/symbiose.c
        code/symbiose.h
        code/especes_speciales.c
        code/especes_speciales.h
        code/complexite.c
        code/complexite.h
        code/simulation.c
        code/simulation.h
        code/Importance_trophique.c
        code/Importance_trophique.h
        )
