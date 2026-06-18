class Solution {
public:
    double angleClock(int hour, int minutes) {
        double deg1 = minutes * 6;
        if (hour == 12) hour = 0;
        double deg2 = hour * 30 + minutes * 1.00 / 60 * 30;
        double dif = abs(deg1 - deg2);
        return min(dif, 360 - dif);
    }
};