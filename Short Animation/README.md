
  
  
# Short Animation <img src="https://www.opengl.org/img/opengl_logo.png" height=50 align="center">
In this project, a short robot animation is made with the help of OpenGL in-built functions for transformation and **glutTimerFunc** callback function. Animation is divided into small parts and for every  part has its own timer function, which handles the animation for that part. Another timer function (which I like to call master timer function) is also there, which handles when to call all the other timer functions of mentioned small parts. This master timer function handles the timing and sequence for every small animation, just like the conductor in an orchestra show.
This short animation is inspired from the before credit scene of a famous animated show on Netflix called "Love Death+Robots".
  
## Usage
- Build and run the code. A glut window will open on the screen.
- By left clicking once anywhere on the window, animation can be started. 
Then just sit back and enjoy the show **although it is a very short show :sweat_smile:**
- Also, you can increase the speed by clicking again inside the window. I won't recommend it though, as it is already very short.
## Output

![animation gif](https://user-images.githubusercontent.com/46368329/123936740-1c2cbf00-d9b3-11eb-9b7c-0f562f835361.gif) 
