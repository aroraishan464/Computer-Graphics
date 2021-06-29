
  
# DDA Line Drawing Algorithm <img src="https://www.opengl.org/img/opengl_logo.png" height=50 align="center">
In any 2-Dimensional plane if we connect two points, we get a line segment. But in the case of computer graphics, we can not directly join any two coordinate points, for that we should calculate intermediate points’ coordinates and put a pixel for each intermediate point, of the desired color. 
DDA (Digital Differential Analyzer) is an incremental method of scan conversion of line. In this method calculation is performed at each step but by using results of previous steps. At each step a pixel is created and after all steps are completed these pixels form a line between starting and ending points

## Usage
- Build and run the code. A glut window will open on the screen.
- Create points by left clicking anywhere in the window. 
- When 2 points are created, DDA function will generate a line between starting point and ending point. Multiple lines can be created.
- Slope is calculated for the last drawn line and is displayed on right bottom of the window.
- Last drawn line can be identified with bullet point on each end.   
 
## Output Screenshot
<img src="https://user-images.githubusercontent.com/46368329/123773568-6138ee80-d8ea-11eb-98c3-e11bd5f7b335.png" width="49%">
<img src="https://user-images.githubusercontent.com/46368329/123773574-626a1b80-d8ea-11eb-8e78-c9c0763a76c9.png" width="49%">
