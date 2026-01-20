# Solar System

## geocentrism rocks!

Final project for the "Computing Techniques for Physics" course in the Bachelor's Degree in Physics at the University of Turin.
The goal is to simulate the solar system in C++, implementing a graphical engine with openGL to visualize the orbits of the planets in 3 dimensions. Coincidentally we also verify the validity of the second and third Kepler's laws.

### Luca Tempesta, Paolo Rocchietti March, Alessandro Romanini

## Structure

The project is subdivided in directories:

* src: containing source files (.cpp)
* include: containig header files (.h, .cc)
* bin: containing compiled executables
* root: containing ROOT files
* csv: containing the .csv files that store the simulations' output

Moreover Make will be used to guarantee the automation of the compiling process.
If the project becomes too complex to use Make, CMake will be used
in order to automatize the Make file generation used to build the executables (.out).
## How to use
Firstly, you need to clone this repository with the command

<code>git clone https://www.github.com/0universe0/solar_system</code>. 

### n(=2) body simulator
To access the main simulator, you need to compile the code and libraries by running <code>make</code>
in the main directory, you can then execute the binary <code>./bin/main</code> to access the simulator:
Note that, for now, only the 2 body simulations are implemented.

To visualize the simulated orbits you can execute the specific root macro with

<code>root ./root/twoBodiesGraphic.cpp</code>

### Second Kepler law of planetary motion
To verify the second law, you can execute the specific root macro with
<code>root ./root/secondKepler.cpp</code>
that will show that the areal velocity of closed orbits is constant over time (simulating the Earth-Sun and Moon-Earth systems).

### Third Kepler law of planetary motion
To verify the third law, you can execute the specific root macro with
<code>root ./root/thirdKepler.cpp</code>
that will show that, for closed orbits, T^2 is proportional to a^3 (where a is the major semiaxis and the T is the period of the orbit) by a constant k dependent on the mass of the bigger body of the binary system (even though this is inaccurate for the orbits of the gas giants, like Jupiter).

[To be continued...]
