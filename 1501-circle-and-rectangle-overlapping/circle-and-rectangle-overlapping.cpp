class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int closestX = max(x1, min(x2, xCenter));
        int closestY = max(y1, min(y2, yCenter));
        int distanceX = closestX - xCenter;
        int distanceY = closestY - yCenter;
        return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
    }
};
