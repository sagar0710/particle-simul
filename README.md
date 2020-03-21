# Simulator

### A simple, not-so-accurate basic physics simulator.

<hr>

## About

<p> This started as an attempt of making an accurate physics simulator which can simulate Univeral Gravitation and Electromagnetic forces on particles, and display of motion of them using OpenGL.<br>
However soon that idea fizzled out, as difficulties were found in making a global time-step and accurate collision detection.<br>
Some of these problems were resolved, and some could not be.<br>
This is a not-so-accurate physics simulator, which can simulate Universal gravitation, Electromagnetic force, and Earth's Gravitation 'g'.</p>
<p> This can simulate motion of spheres, points and add static oblique rectangles and can show their paths. It can do collision detection for all of those bodies, but can give wrong results sometimes.</p>

<p>This started as an attempt to use OpenGL while learning Computer Graphics in SE. Also really wanted to do this as a project related to physics for a long time. Even though it didn't turn out to be exactly what I had in ming, I had lot of fun doing this.<br>

Even though this is not an accurate (ir for that matter, decently correct) simulator, I got to learn how to use Basic OpenGL, how game physics simulation and collision detection is done, and other things during this.</p>

## Compiling Information

<p>The default makefile is generated using <a href="https://github.com/YJDoc2/Makefile-Generator">Makefile Generator</a> and is usable for g++ compiler which can support c++17 standard. Also OpenGL and GLUT libraries need to be available in compiler include path as well as runtime libreries.<br>
Otherwise files can be compiled one by one as per the makefile.</p>

## Usage

<p> The binary created by makefile, named as 'simulator' takes a file as an argument in format 'simulator <filename>'. The File needs to be a text file, and should specify the simulation objects as per the specified format (Which is given in examples folder README). Some examples are given in the examples folder, as well as the template.sim file which shows the syntax. As the tokenizer splits tokens by white space, the arguments needs to be separated by space, and their line position does not matter. The simulation will be opend in a window.The file need not have the extention '.sim' but is used for consistency in examples.</p>

## Notes

<ul>
<li>
The Collision with static bodies can be incorrect sometimes,if not most of times.
</li>
<li>The Universal Gravitation (and probably the electromagnetic as well) is highly reactive to the tslice parameter, with different values of which completely different paths of objects  can be observed for same starting conditions.</li>
<li>The Objects in Universal Gravitation usually precess even though there are no other objects influening their paths.</li>
<li><b>There is a very good chance of finding bugs as one tries various combinations</b></li>
</ul>
## Warnings 
#### Please do not use this in any projects as this is quite inaccurate and buggy.
