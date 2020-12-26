#include "cpps/includes/a_star.h"
#include "gtest/gtest.h"

namespace {
const ObstaclesT kCol11Obstacles{{0, 11},  {1, 11},  {2, 11},  {3, 11},
                                 {4, 11},  {5, 11},  {6, 11},  {7, 11},
                                 {8, 11},  {9, 11},  {10, 11}, {11, 11},
                                 {12, 11}, {13, 11}, {14, 11}, {15, 11}};
const PointT kStart{2, 2};
const PointT kEnd{14, 18};
}  // namespace

TEST(AStar, DISABLED_Plot) {
  const TrajectoryT& traj{{2, 2},   {2, 3},   {3, 4},   {4, 5},   {5, 6},
                          {6, 7},   {7, 8},   {8, 9},   {8, 10},  {8, 11},
                          {8, 12},  {9, 13},  {10, 13}, {11, 13}, {12, 14},
                          {13, 15}, {14, 16}, {14, 17}, {14, 18}};

  ObstaclesT obs{kCol11Obstacles};
  obs.erase(obs.find({8, 11}));

  Plot(kStart, kEnd, traj, obs);
}

TEST(AStar, Typical) {
  ObstaclesT obs{kCol11Obstacles};
  obs.erase(obs.find({3, 11}));

  TrajectoryT traj = RouteWithAStar(kStart, kEnd, obs);
  Plot(kStart, kEnd, traj, obs);
}

TEST(AStar, NoObstacles) {
  TrajectoryT traj = RouteWithAStar(kStart, kEnd, {});
  Plot(kStart, kEnd, traj, {});
}

TEST(AStar, NoTrajectory) {
  TrajectoryT traj = RouteWithAStar(kStart, kEnd, kCol11Obstacles);
  Plot(kStart, kEnd, traj, kCol11Obstacles);
  EXPECT_EQ(TrajectoryT{}, traj);
}