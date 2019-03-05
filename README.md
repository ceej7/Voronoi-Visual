# Voronoi-Visual
- A Voronoi diagram is a partitioning of a plane into regions based on distance to points in a specific subset of the plane. 
- A visualization of Voronoi diagram algorithm with C++ and MFC
## Demo
![image](./Voronoi-Visual-Demo.gif)
## Setup
To startup the voronoi system
```C++
Voronoi *vPtr=new Voronoi(with,height,number_of_point);
vPtr->restart();
```
To retrieve the relevant data structure
```C++
std::vector<Vector2 *> set_Sites_Ptrs;
std::vector<Edge *> set_Edge_Ptrs;
std::vector<Cell *> set_Cell_Ptrs;
```
## Reference
[Algorithm](https://courses.cs.washington.edu/courses/cse326/00wi/projects/voronoi.html)