## Douglas-Peucker algorithm

The Douglas-Peucker algorithm simplifies a curve composed of line segments to have fewer points, while preserving the shape of the curve.

It's used for zooming out maps, smoothing out input data from telemeters or reducing memory footprint.

![Douglas-Peucker algorithm in action](https://github.com/RaduHaulica/Douglas-Peucker/blob/a3227582f976bc4c672cfde6d91bb71c9f02601e/Douglas%20Peucker/media/douglas%20peucker%20main.gif)

The algorithm divides the line recursively by comparing the distance between the farthest point and the current line boundaries to a given epsilon, then discarding points that are too close (since they offer information about the curve that is similar to the already existing points).

Consequently, the simplified curve consists of a subset of points from the original curve. In the image below, the original curve is blue, while the simplified version is green.

![Douglas-Peucker initial curve vs simplified curve](https://github.com/RaduHaulica/Douglas-Peucker/blob/a3227582f976bc4c672cfde6d91bb71c9f02601e/Douglas%20Peucker/media/douglas%20peucker.png)

I was also curious to see the differences betweeen the algorithm and a bezier curve with a low number of points that uses the original points as a control set.

Additionally, i created another bezier based on the simplified curve point set to see how closely it resembles the original curve. The Bezier line based on the original point set is red, and the one based on the simplified D-P curve is magenta.

![Bezier lines vs Douglas-Peucker simplified line](https://github.com/RaduHaulica/Douglas-Peucker/blob/a3227582f976bc4c672cfde6d91bb71c9f02601e/Douglas%20Peucker/media/douglas%20peucker%20bezier.png)

## How to use

Hold the left mouse button and move the mouse to create a curve.

Right click to start the Douglas-Peucker algorithm.
 
 Hold F1 to display Bezier curves.
