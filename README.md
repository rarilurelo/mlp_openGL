# mlp_openGL
## using
input.c is a file to generate supervised data.
Draw characters 'r', 'g', 'b', 'y', 'w' and typing the corresponding key, it will output output?.dat.  
If you feel bothering at creating supervised data, I've already made at rgbyw.

learning*.cpp is a training program, it will output Matrix and bias Vector data.

output*.cpp can demonstrate MLP classifier with OpenGL.
You can draw 'r', 'g', 'b', 'y', 'w', and type '9' the color of ball will change to red, green, blue, yellow, white.

## compile
You have to check option 'GLUT' and 'OpenGL' Library when you compile.
These files depend on Eigen, so you have to install Eigen Library.

