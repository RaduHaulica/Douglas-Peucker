 Implementation of Douglas-Peucker algorithm that simplifies a curve composed of line segments to have fewer points, while preserving the shape of the curve.
 
 The algorithm divides the line recursively by comparing the distance between the farthest point and the current line boundaries to a given epsilon and discarding points that are too close.
 
 Consequently, the simplified curve consists of a subset of points from the original curve.
 
 Useful for zooming out maps or reducing memory footprint.
 
 I was also curious to see the differences betweeen the algorithm and a bezier curve with a low number of points that uses the original points as a control set.
 Additionally, i created another bezier based on the simplified curve point set to see how closely it resembles the original curve.
 
 ##How to use
 
 Hold the left mouse button and move the mouse to create a curve.
 
 Right click to start the Douglas-Peucker algorithm.
