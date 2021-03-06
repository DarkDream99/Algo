#include "stdafx.h"

#include "Point2D.h"
#include "Polygon.h"

#include <iostream>

Vertex* leastVertex(Polygon& polygon, int(*cmp)(Point2D*, Point2D*)) {
	Vertex* bestVertex = polygon.targetVertex();
	polygon.advance(Vertex::CLOCKWISE);

	for (int i = 1; i < polygon.size(); polygon.advance(Vertex::CLOCKWISE), ++i) {
		if ((*cmp)(polygon.targetVertex(), bestVertex) < 0) {
			bestVertex = polygon.targetVertex();
		}
	}

	polygon.setTargetVertex(bestVertex);
	return bestVertex;
}

int LeftToRightCmp(Point2D* pointA, Point2D* pointB) {
	if (*pointA < *pointB) return -1;
	if (*pointA > *pointB) return 1;
	return 0;
}

int RightToLeftCmp(Point2D* pointA, Point2D* pointB) {
	return LeftToRightCmp(pointB, pointA);
}

int main() {
	Point2D pointStart(-1, 3);
	Vertex* vertexStart = new Vertex(pointStart);
	vertexStart->insert(new Vertex(4, 3));
	vertexStart->insert(new Vertex(4, -3));
	vertexStart->insert(new Vertex(-1, -3));
	
	Polygon polygon(vertexStart);
	Point2D point(6, 7);

	Vertex* minVertex = leastVertex(polygon, LeftToRightCmp);
	Vertex* maxVertex = leastVertex(polygon, RightToLeftCmp);
	std::cout << *minVertex << std::endl;
	std::cout << *maxVertex << std::endl;

	return 0;
}