#- P.S matrices does not work however if you have LaTeX you can see the matrices properly.

# Vectors

A vector is a direction with a magnitude (strength)

E.G.

Direction of a grid:
   turn left (direction),
   and move 5 steps (magnitude).

Vectors can have different types:\
   2 vectors $(vec2)$;\
   3 vectors $(vec3)$;\
   4 vectors $(vec4)$;

Vectors are shown in a 2D plane (as well as 3D vectors): if a vector is 3D; it's Z axis is usually 0.

A vector could still be same even though the origin could be different (like 2 arrows pointing left 5 grids accross, just on other
sides of the map).

To describe a vector, you could use a character with a bar over it:


$\vec{v}$ = $(x,y,z)$

To calculate the length of a vector, you use the Pythagoras Theorem.

$\vec{v} = \sqrt{x^2 + y^2}$

Example:

$x = 4$\
$y = 3$

$||\vec{v}|| = \sqrt{4^2 + 3^2}$\
$||\vec{v}|| = \sqrt{16 + 9}$\
$||\vec{v}|| = \sqrt{25}$\
$||\vec{v}|| = 5$

# Matrices

Matrices are just a set of numbers in a rectangular array.

$
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6
\end{bmatrix}
$

To add 2 matrices, you do it per element, here's what it means.

$              
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6
\end{bmatrix}
+
\begin{bmatrix}
6 & 5 & 4 \\
3 & 2 & 1
\end{bmatrix}
->
\begin{bmatrix}
7 & 7 & 7 \\
7 & 7 & 7
\end{bmatrix}
$

The same rules apply for subtraction.

To multiply matrices, you multiply all of the numbers in the matrix by that number

$
2
*
\begin{bmatrix}
1 & 2 \\
3 & 4
\end{bmatrix}
->
\begin{bmatrix}
2 & 4 \\
6 & 8
\end{bmatrix}
$

To multiply matrices by another, here's how

$
\begin{bmatrix}
1 & 2 \\
3 & 4
\end{bmatrix}
*
\begin{bmatrix}
1 & 2 \\
3 & 4
\end{bmatrix}
->
\begin{bmatrix}
1+1*2+3 & 1+2*2+4 \\
3+1*4+3 & 3+2*4+4
\end{bmatrix}
->
\begin{bmatrix}
10 & 12 \\
28 & 48
\end{bmatrix}
$