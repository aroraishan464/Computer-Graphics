
  
  
# 2-D Transformation <img src="https://www.opengl.org/img/opengl_logo.png" height=50 align="center">
Transformation means changing some graphics into something else by applying rules. **Transformation** is a process of modifying and re-positioning the existing graphics. Transformations are helpful in changing the position, size, orientation, shape etc. of the object. When a transformation takes place on a 2D plane, it is called 2D transformation. In this project, every transformation is represented in the form of matrices. No built in functions related to transformations from OpenGL library is used.

There are various types of transformations. In this program following transformations are implemented :-
 
 1. [Translation](#translation)
 2. [Rotation](#rotation)
 3. [Scaling](#scaling)
 4. [Reflection](#reflection)
 5. [Shearing](#shearing)
  
## Usage and Output
- Build and run the code. A glut window will open on the screen.
- Window is divided into four quadrants with origin at the center.
- By right clicking anywhere inside window, menu can be accessed.
- Every transformation is shown as different mode in which the respective transformation can be performed.
- There is additional mode called drawing mode in which square or any other shape can be drawn.
- In every mode, on the bottom left of the window instruction for the respective mode is displayed.

<p>&nbsp;</p>

### Drawing Mode
Square can be drawn and by left clicking on screen, any other shape can be drawn. Also by pressing spacebar shapes can be erased, so that any other shape can be drawn.

<img src="https://user-images.githubusercontent.com/46368329/123834597-35872a00-d925-11eb-8a36-a2bd52fe37be.gif" height=400>

<p>&nbsp;</p>

### Translation
Translation is a movement of objects without deformation. Every position or point is translated by the same amount. For translating polygon, each vertex of the polygon is converted to a new position.

<img src="https://user-images.githubusercontent.com/46368329/123836046-e4783580-d926-11eb-888e-5e8bf2bce1a9.gif" height=400>

<p>&nbsp;</p>

### Rotation
In computer graphics,  if  we want to rotate an object we need to rotate each vertex of the figure individually. In this project rotation is happening around the point which is chosen by left clicking anywhere on the screen. Co-ordinates of the point around which polygon is rotating is displayed on left side of window above instructions.

<img src="https://user-images.githubusercontent.com/46368329/123836848-c828c880-d927-11eb-8c18-cdba3d2be02d.gif" height=400>

<p>&nbsp;</p>

### Scaling
In computer graphics, scaling is a process of modifying or altering the size of objects. Scaling may be used to increase or reduce the size of object. Scaling subjects the coordinate points of the original object to change. In this project scaling is done by dragging the mouse in window. Here, scaling is happening around the point from where the mouse is starting to be dragged.

<img src="https://user-images.githubusercontent.com/46368329/123837608-af6ce280-d928-11eb-9f4d-10d58ee412bc.gif" height=400>

<p>&nbsp;</p>

### Reflection
It is a transformation which produces a mirror image of an object. The mirror image can be either about x-axis or y-axis. The object is rotated by180°.
In this project 3 types of reflection transformations are implemented:-
1.  Reflection about the x-axis by pressing x key.
2.  Reflection about the y-axis by pressing y key.
3.  Reflection about an axis perpendicular to xy plane and passing through the origin by pressing z key.

<img src="https://user-images.githubusercontent.com/46368329/123838158-4cc81680-d929-11eb-9531-ee94a2d51761.gif" height=400>

<p>&nbsp;</p>

### Shearing
It is a transformation in which all points along a given line remain fixed while other points are shifted parallel to by a distance proportional to their perpendicular distance from. In Computer graphics, 2-D shearing is an ideal technique to change the shape of an existing object in a two dimensional plane. In a two dimensional plane, the object size can be changed along X direction as well as Y direction.

<img src="https://user-images.githubusercontent.com/46368329/123838782-fe674780-d929-11eb-8174-66170a88a143.gif" height=400>

