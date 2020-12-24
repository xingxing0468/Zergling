#ifndef A_STAR_H_
#define A_STAR_H_

#include <vector>

struct PointT {
  int i;
  int j;
};

using TrajectoryT = std::vector<PointT>;
using ObstaclesT = std::vector<PointT>;

void Plot(const PointT& start, const PointT& end, const TrajectoryT& traj,
          const ObstaclesT& obs);

#endif