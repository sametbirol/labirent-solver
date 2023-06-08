# labirent_recursive
This repository includes codes for a project that aims to generate random(with specific constraints) labyrinths and solve them in the best optimized way possible.

SPECIFICATIONS
• The labyrinth is a rectangular.
• The labyrinth will contain at most 100000 cells. All row/column counts ≥3 that satisfy
this restriction are possible.
• Walls are persistent. It is not possible to move to a wall cell.
• The start point is a passage cell.
• A valid path is made up of adjacent moves marked by ‘+’ and made in one of the west,
north, east or south directions. Diagonal moves are not accepted.
• Any valid path leading to any exit will be accepted. No need to search for shortest path.
• If no path exists then mark the interior of the vicinity (that you are stucked in) with ‘*’
characters.
