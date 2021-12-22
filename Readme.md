#README

#There are 4 versions included, 

##Modulo Versions
1. gmlife_serial_modulo_O3: serial version, use of modulo to emulate the infinite grid 
2. gmlife_parallel_modulo: same as (1) & parallelized with OpenMp


##Extra Row/Col Versions
3. gmlife_serial_+rc_O3: serial version, use of extra rows/cols to emulate the infinite grid 
4. gmlife_parallel_+rc_bestVersion: same as (3) & parallelized with OpenMp


#Compile and run
* Type make to compile all the versions
* Run with  ./version number_of_rows number_of_columns generations
* Type make clean when you are done

#Graphics
* To view the simulation, modify the preprocessor statement DISPLAY_STATE, set it to 1 
to enable graphics
* To view the simulation's final state, modify the preprocessor statement DISPLAY_FINAL_STATE, set it to 1

#Example
* $ ./gmlife_parallel_+rc_bestVersion 2000 2000 120 
* Run the Game of life on a 2000x2000 grid for 120 generations
* Output: Time:0.534357
