Realtivistic Ray Tracing
========================
This is done as part of my final project for the CS 175 Comuter Graphics class in school. For a full description of the project please refer to the writeup.pdf file.

== DISCLAIMER ==
	The entire code was written in C++ on the MAC OSX 10.8.2 operating system with 2GHz processor Intel Core i7. There is a Makefile included in the submission that can be used to compile the code in the folder.

== INTRODUCTION ==

	This project implements a simple ray tracer using the approach illustrated in the book, ”An Intro- duction to Ray Tracing” by Andrew S. Glassner. The ray tracer implments the basic geometrical shapes such as sphere, plane, box, cylinder. It also extends the implementation in class to include refraction and super sampling.

== THEORY ==
	
	The writeup.pdf file covers in depth of the theoretical background of refraction that is used in ray-tracing of the program.

== SUPERSAMPLING ==

	The ray tracing algorithm that I implemented was only sending rays into a scene in a grid pattern that matches the image pattern. This produces images with jagged edges which can be most easily seen along the boundaries of the shadows. To smooth out the edge, I implemented an antialiasing technique using a grid supersampling tech- nical. In supersampling, more rays are sent into the scene. Each of these additional rays are slghly offset to the rays that were used initially. The color of the pixel is then the sum of the color of each ray averaged over the total number of rays sent. The supersampling technique is easy to implement but more computationally intesnsive.

== CONCLUSIONS ==

	This project implements the various primatives for the raytracing program. Several problems were encountered when coding up the ray tracing algorithm. First, there are ghost dots appearing when the rebounced ray is not set far away enough from the surface of intersection. Second, due to supersampling, the time taken to render the image increased by a significant amount and therefore we have to figure out a compromise solution.
	
	For the future, it will be good to implement the ray tracing on a GPU as this will increase the run time by a significant amount. Also, for the special relativity section, due to the time constraint, only lorentz transformation was simulated. It will visually more realistic to also include other special relativity effects such as doppler effect.
