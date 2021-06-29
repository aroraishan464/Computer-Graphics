
  
  
# Filling Algorithm <img src="https://www.opengl.org/img/opengl_logo.png" height=50 align="center">
Region filling is the process of filling image or region. In this program, two algorithms are implemented, flood fill and boundary fill. Boundary Fill algorithm is used to fill the boundary and flood-fill algorithm is used to fill the interior.
 
- **Boundary Filled Algorithm:** This algorithm uses the recursive method. First of all, a starting pixel called as the seed is considered. The algorithm checks boundary pixel or adjacent pixels are colored or not. If the adjacent pixel is already filled or colored then leave it, otherwise fill it. The filling is done using four connected or eight connected approaches. 
- **Flood Fill Algorithm:** In this method, a point or seed which is inside region is selected. This point is called a seed point. Then four connected approaches or eight connected approaches is used to fill with specified color. The flood fill algorithm has many characters similar to boundary fill. But this method is more suitable for filling multiple colors boundary. When boundary is of many colors and interior is to be filled with one color we use this algorithm.

In this program, four connected approach is used for both boundary fill and flood fill algorithm. 
## Usage
- Build and run the code. A glut window will open on the screen.
- Left click anywhere in the sub-windows for boundary fill and flood fill to create points. These points connect with each other automatically to make polygon. 
- Right click inside the polygon to fill them with random color using their algorithm respective to their sub-window. 
- Color will vanish after the polygon gets completely filled, so that it can be filled again with another random color.
- By pressing spacebar in any sub-window, polygons of their respective sub-windows can be erased. After that new polygons can be made, or by pressing escape key, exit the program.    
 
## Output Screenshot
<img src="https://user-images.githubusercontent.com/46368329/123795214-66556800-d901-11eb-8e83-65e327c08a89.gif"> 