#ifndef A_STAR_H_
#define A_STAR_H_

#include <set>

struct PointT {
  int i;
  int j;
};

bool operator<(const PointT& lhs, const PointT& rhs) {
  if (lhs.i == rhs.i) {
    return lhs.j < rhs.j;
  }
  return lhs.i < rhs.i;
};

bool operator==(const PointT& lhs, const PointT& rhs) {
  return lhs.i == rhs.i && lhs.j == rhs.j;
}

using TrajectoryT = std::set<PointT>;
using ObstaclesT = std::set<PointT>;

void Plot(const PointT& start, const PointT& end, const TrajectoryT& traj,
          const ObstaclesT& obs);

TrajectoryT RouteWithAStar(const PointT& start, const PointT& end,
                           const ObstaclesT& obs);
#endif