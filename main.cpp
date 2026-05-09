#include <iostream>
#include "min_circle.h"

int main() {
	LineSegment a{{1,0},{5,6}};
	LineSegment b{{2,4},{-10,3}};
	LineSegment c{{-5,-5},{0,10}};
	std::vector<LineSegment> tmp{a,b,c};
	Circle cir = MinimumEnclosingCircleForSegments(tmp);
	std::cout << "Центр: (" << cir.center.x << "," << cir.center.y << ") Радиус: " << cir.radius << std::endl;
	return 0;
}
