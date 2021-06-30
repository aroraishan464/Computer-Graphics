
  
  
# 3-D Transformation <img src="https://www.opengl.org/img/opengl_logo.png" height=50 align="center">
Transformation means changing some graphics into something else by applying rules. **Transformation** is a process of modifying and re-positioning the existing graphics. Transformations are helpful in changing the position, size, orientation, shape etc. of the object. When a transformation takes place on a 3D plane, it is called 3-D transformation. In this project, every transformation is represented in the form of matrices. No built in functions related to transformations from OpenGL library is used.

There are various types of transformations. In this program following transformations are implemented :-
 
 1. [Translation](#translation)
 2. [Rotation](#rotation)
 3. [Scaling](#scaling)
 4. [Reflection](#reflection)
 5. [Shearing](#shearing)
  
## Usage and Output
- Build and run the code. A glut window will open on the screen.
- Window is divided into eight quadrants with origin at the center.
- By right clicking anywhere inside window, menu can be accessed.
- Every transformation is shown as different mode in which the respective transformation can be performed.
- There is additional mode called drawing mode in which cube, cuboid or octahedron can be drawn.
- In every mode, on the bottom left of the window instruction for the respective mode is displayed.
- Center co-ordinates of the 3-D shape is displayed on top-left corner of the window.
- To visualize the 3-D transformation as well as to see shapes in 3-dimension, everything displayed on the window is looked at from some angle using **gluLookAt** function. 

### Drawing Mode
Cube, Cuboid and Octahedron can be drawn by pressing their respective key mentioned in the instructions. Also by pressing spacebar shapes can be erased, so that any other shape can be drawn.

<img src="https://user-images.githubusercontent.com/46368329/123929547-85f59a80-d9ac-11eb-829b-ed164668d049.gif" height=400>

### Translation
Translation is a movement of objects without deformation. Every position or point is translated by the same amount. For translating polygon, each vertex of the polygon is converted to a new position. 

<img src="https://user-images.githubusercontent.com/46368329/123929544-855d0400-d9ac-11eb-9069-72c1657f8f2b.gif" height=400>

### Rotation
In computer graphics,  if  we want to rotate an object we need to rotate each vertex of the figure individually. In this project rotation is happening around the axis drawn from an arbitrary point which can be moved using the respective keys mentioned in the instructions. Co-ordinates of the arbitrary point around which polygon is rotating is displayed on left side of window above instructions. In this project, rotation is happening in clockwise direction around x, y and z axis drawn from the arbitrary point.

<img src="https://user-images.githubusercontent.com/46368329/123929541-84c46d80-d9ac-11eb-86f0-30343df9c080.gif" height=400>

### Scaling
In computer graphics, scaling is a process of modifying or altering the size of objects. Scaling may be used to increase or reduce the size of object. Scaling subjects the coordinate points of the original object to change. In this project scaling in x and y are done by dragging the mouse in window and for scaling in z, j and l keys are used. Here, scaling is happening about the an arbitrary point for which co-ordinates are displayed on the on left side of window above instructions. This arbitrary point can be moved using the respective keys mentioned in the instructions.

<img src="https://user-images.githubusercontent.com/46368329/123929540-84c46d80-d9ac-11eb-8882-4b18cf6f62e1.gif" height=400>

### Reflection
It is a transformation which produces a mirror image of an object. In this project 3 types of reflection transformations are implemented:-
1.  Reflection about the yz-plane by pressing x key.
2.  Reflection about the xz-plane by pressing y key.
3.  Reflection about the xy-plane by pressing z key.  

<img src="https://user-images.githubusercontent.com/46368329/123929537-842bd700-d9ac-11eb-8d5f-38532c33aeba.gif" height=400>

### Shearing
Shearing in 3-D is the process of slanting an object in 3D space either in x, y, or in the z-direction. Shearing changes(or deformed) the shape of the object.
Below are the types of shearing transformation which are implemented in this project.
-   Shearing in X-direction.
-   Shearing in y-direction
-   Shearing in z-direction.

<img src="https://user-images.githubusercontent.com/46368329/123929528-82621380-d9ac-11eb-9e84-da1727b34604.gif" height=400>

