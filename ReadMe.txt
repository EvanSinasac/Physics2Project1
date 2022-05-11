Evan Sinasac - 1081418
INFO6022 Physics & Simulation 2
Project 1

Built and compiled using Visual Studios 2019 in Debug in 64 bit.
gdpPhysics and PhysicsInterface do not compile in Release.

CONTROLS
WASD		- Apply a force on the selected sphere in the direction of the camera orthogonal to the horizontal plane
Arrow Keys	- Camera is facing the origin and the arrow keys rotate the camera around the origin and zoom in/out towards the origin
1/2/3/4/5	- Switch the selected sphere that the user can apply forces to


PHYSICS
The gdpPhysics and PhysicsInterface projects are the ones we made in class, with their implementations into the main project my own.  It's a little funky, but I made a new kind of Entity that posseses a rigid body.  I have a single global physics factory and a single global physics world.  When the entity is made, it creates it's own mesh and rigid body, the rigid body being made by the physics factory and then added to the physics world.  Then when the WASD keys are pressed, we apply a force in the direction the camera is facing on the currently selected sphere.


Video: https://youtu.be/cFtpgxqvO7k