#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <iomanip>

struct Circle {
    double x;
    double y;
    double r;
};

bool insideCircle(double px, double py, const Circle& circle) {
    return (px - circle.x) * (px - circle.x) + (py - circle.y) * (py - circle.y) <= circle.r * circle.r;
}

bool insideIntersection(double px, double py, const Circle& c1, const Circle& c2, const Circle& c3) {
    return insideCircle(px, py, c1) && insideCircle(px, py, c2) && insideCircle(px, py, c3);
}

double monteCarlo(const Circle& c1, const Circle& c2, const Circle& c3, int n) {


    double minX = std::min(std::min(c1.x - c1.r, c2.x - c2.r), c3.x - c3.r);
    double maxX = std::max(std::max(c1.x + c1.r, c2.x + c2.r), c3.x + c3.r);
    double minY = std::min(std::min(c1.y - c1.r, c2.y - c2.r), c3.y - c3.r);
    double maxY = std::max(std::max(c1.y + c1.r, c2.y + c2.r), c3.y + c3.r);

    double rectangle = (maxX - minX) * (maxY - minY);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distX(minX, maxX);
    std::uniform_real_distribution<double> distY(minY, maxY);

    int count = 0;
    for (int i = 0; i < n; ++i) {
        double px = distX(rng);
        double py = distY(rng);

        if (insideIntersection(px, py, c1, c2, c3)) {
            ++count;
        }
    }

    double estimated_res = static_cast<double>(count) / n * rectangle;
    return estimated_res;
}

int main() {
    Circle c1;
    Circle c2;
    Circle c3;

    std::cin >> c1.x >> c1.y >> c1.r;
    std::cin >> c2.x >> c2.y >> c2.r;
    std::cin >> c3.x >> c3.y >> c3.r;

    std::ofstream outFile("results.csv");
    outFile << "N,EstimatedArea,RelativeError\n";
    int big_n = 1000000;
    double true_res = monteCarlo(c1, c2, c3, big_n);

    int start = 100;
    int end = 100000;
    int step = 500;

     for (int n = start; n <= end; n += step) {
         double estimated_res = monteCarlo(c1, c2, c3, n);

         double error = std::abs(estimated_res - true_res) / true_res * 100.0;

         outFile << n << "," << std::setprecision(10) << estimated_res << "," << error << "\n";

         std::cout << "n = " << n << ",\t Estimated area = " << estimated_res << ",\t Error = " << error << "%\n";
     }

    outFile.close();
    std::cout << "Результаты сохранены в results.csv\n";

    return 0;
}