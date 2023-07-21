COMPILER = gcc
CSTD = --std=c18


makeResultfiles: sim
	> Power_alive.txt
	> Power_dead.txt
	> Level_alive.txt
	> Level_dead.txt
	> Charm_alive.txt
	> Charm_dead.txt
	> Agility_alive.txt
	> Agility_dead.txt
	> Intelligence_alive.txt
	> Intelligence_dead.txt

sim:
	gcc --std=c18 -o sim simulation.c -lpthread

clean: 
	rm -f *.txt sim *.o
