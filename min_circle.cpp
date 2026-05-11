#include "min_circle.h"
#include <vector>
#include <cmath>

Circle MinimumEnclosingCircleForSegments(const std::vector<LineSegment>& segments) {
	std::vector<Point2D> tmp = extractPointsFromSegments(segments);
	return minCircle(tmp); 	
}

double distanceSquared(const Point2D& p1,const Point2D& p2) {
	return pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2);
}

double distance(const Point2D& p1,const Point2D& p2) {
	return pow(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2),0.5);
}

Circle circleFromDiameter(const Point2D& p1,const Point2D& p2) {
	return Circle{findMidPoint({p1,p2}),distance(p1,p2)/2};
}

Circle circleFrom3Points(const Point2D& p1,const Point2D& p2,const Point2D& p3) {
	if ((p2.x-p1.x)*(p3.y-p1.y)-(p2.y-p1.y)*(p3.x-p1.x)==0) return Circle{{0,0},0};
	double d1 = (p1.x*p1.x + p1.y*p1.y) - (p2.x*p2.x + p2.y*p2.y);
	double d2 = (p1.x*p1.x + p1.y*p1.y) - (p3.x*p3.x + p3.y*p3.y);
	double a1 = 2*(p1.x - p2.x);
	double b1 = 2*(p1.y-p2.y);
	double a2 = 2*(p1.x-p3.x);
	double b2 = 2*(p1.y-p3.y);
	double det = a1*b2 - b1*a2;
	double x0 = (d1 * b2 - b1 * d2) / det;
	double y0 = (a1 * d2 - d1 * a2) / det;
	Point2D tmp{x0,y0};
	return Circle{tmp,distance(tmp,p1)};
}

Circle minCircleHelper(std::vector<Point2D>& points,std::vector<Point2D> boundary,size_t n) {
	if (boundary.size()==3) return circleFrom3Points(boundary[0],boundary[1],boundary[2]);
	if (n==0)
	{
		if (boundary.size()==2) return circleFromDiameter(boundary[0],boundary[1]);
		else if (boundary.size()==1) return Circle{boundary[0],0};
		else return Circle{{0,0},-1};
	}
	Point2D p = points[n-1];
	Circle d = minCircleHelper(points,boundary,n-1);
	if (d.contains(p)) return d;
	boundary.push_back(p);
	return minCircleHelper(points,boundary,n-1);
}

Circle minCircle(std::vector<Point2D> points) {
	return minCircleHelper(points,{},points.size());
}

std::vector<Point2D> extractPointsFromSegments(const std::vector<LineSegment>& segments) {
	std::vector<Point2D> tmp;
	for (auto i:segments)
	{
		tmp.push_back(i.start);
		tmp.push_back(i.end);
		tmp.push_back(findMidPoint(i));
	}
	return tmp;
}

Point2D findMidPoint(const LineSegment& segment) {
	return Point2D{(segment.start.x+segment.end.x)/2,(segment.start.y+segment.end.y)/2};
}
				
