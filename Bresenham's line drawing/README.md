
  
  
# Bresenham's Line Drawing Algorithm <img src="https://www.opengl.org/img/opengl_logo.png" height=50 align="center">
Bresenham's algorithm is used for scan converting a line. Just like DDA, it is another incremental scan conversion algorithm. It was developed by Bresenham. The big advantage of this algorithm is that, it uses only integer calculations. It is an efficient method because it involves only integer addition, subtractions, and multiplication operations. These operations can be performed very rapidly so lines can be generated quickly. In this method, next pixel selected is that one who has the least distance from true line.

## Usage
- Build and run the code. A glut window will open on the screen.
- Create points by left clicking anywhere in the window. 
- When 2 points are created, "bresenham" function will generate a line between starting point and ending point. Multiple lines can be created.
- Slope is calculated for the last drawn line and is displayed on right bottom of the window.
- Last drawn line can be identified with bullet point on each end.   
 
## Output Screenshot
<img src="https://user-images.githubusercontent.com/46368329/123784771-67809800-d8f5-11eb-8fb7-904d855538f2.png" width="49%"> <img src="https://user-images.githubusercontent.com/46368329/123784776-68b1c500-d8f5-11eb-9667-c95e7e472881.png" width="49%">