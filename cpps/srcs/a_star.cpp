#include "cpps/includes/a_star.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <array>
#include <limits>
#include <stack>

namespace {
constexpr int kWidth{20};
constexpr int kHeight{16};
}  // namespace
/*
x x x x x x x x x x x | x x x x x x x x
x x x x x x x x x x x | x x x x x x x x
x x O . x x x x x x x | x x x x x x x x
x x x x . x x x x x x | x x x x x x x x
x x x x x . x x x x x | x x x x x x x x
x x x x x x . x x x x | x x x x x x x x
x x x x x x x . x x x | x x x x x x x x
x x x x x x x x . x x | x x x x x x x x
x x x x x x x x x . . . . x x x x x x x
x x x x x x x x x x x | x . x x x x x x
x x x x x x x x x x x | x . x x x x x x
x x x x x x x x x x x | x . x x x x x x
x x x x x x x x x x x | x x . x x x x x
x x x x x x x x x x x | x x x . x x x x
x x x x x x x x x x x | x x x x . . O x
x x x x x x x x x x x | x x x x x x x x
*/
void Plot(const PointT& start, const PointT& end, const TrajectoryT& traj,
          const ObstaclesT& obs) {
  assert(start.i < kHeight);
  assert(end.i < kHeight);
  assert(start.j < kWidth);
  assert(end.j < kWidth);

  std::array<std::array<char, kWidth>, kHeight> pixels;

  // 1st, mark all the pixels as 'x'
  for (auto& line : pixels) {
    for (auto& pixel : line) {
      pixel = 'x';
    }
  }

  // 2nd, mark all the trajectory points as '.'
  // overwrite all the normal pixels
  for (const auto& traj_point : traj) {
    assert(traj_point.i < kHeight);
    assert(traj_point.j < kWidth);
    pixels[traj_point.i][traj_point.j] = '.';
  }

  // 3rd, mark all the obstacles points as '|'
  // overwrite all the normal pixels and trajectory
  for (const auto& obstacle : obs) {
    assert(obstacle.i < kHeight);
    assert(obstacle.j < kWidth);
    pixels[obstacle.i][obstacle.j] = '|';
  }

  // Finally, mark start and end point as 'O'
  // overwrite all the normal pixels and trajectory
  pixels[start.i][start.j] = 'O';
  pixels[end.i][end.j] = 'O';

  // Rendering
  for (auto& line : pixels) {
    for (auto& pixel : line) {
      printf("%c ", pixel);
    }
    printf("\n");
  }
}

TrajectoryT RouteWithAStar(const PointT& start, const PointT& end,
                           const ObstaclesT& obs) {
  TrajectoryT ret{};
  struct AStarTrajPointT {
    PointT Point;
    std::set<PointT> Successors;
  };
  std::stack<AStarTrajPointT> traj_stack;
  std::set<PointT> operated_points;
  auto cost_func = [](const PointT& a,
                      const PointT& b) -> double {  // eular distance as cost
    return std::hypot(a.i - b.i, a.j - b.j);
  };

  auto GenerateAStarTrajPointT =
      [&operated_points, &obs](const PointT& point) -> AStarTrajPointT {
    AStarTrajPointT a_star_point;
    a_star_point.Point = point;
    for (auto i = point.i - 1; i <= point.i + 1; ++i)
      for (auto j = point.j - 1; j <= point.j + 1; ++j) {
        if (i < 0 || j < 0 || i >= kHeight ||
            j >= kWidth) {  // index out of range
          continue;
        }
        if (obs.find(PointT{i, j}) != obs.end()) {  // Obstacle
          continue;
        }
        if (i == point.i && j == point.j) {
          continue;  // Self not included in successors
        }
        if (operated_points.find(PointT{i, j}) != operated_points.end()) {
          continue;  // Already tried before, skip
        }

        a_star_point.Successors.emplace(PointT{i, j});
      }
    return a_star_point;
  };

  auto GetNextTrajPoint =
      [&end, &cost_func](const AStarTrajPointT& a_star_point) -> PointT {
    double min_cost = std::numeric_limits<double>::max();
    PointT next_point;
    for (const auto& successor : a_star_point.Successors) {
      auto cost = cost_func(successor, end);
      if (cost < min_cost) {
        min_cost = cost;
        next_point = successor;
      }
    }
    return next_point;
  };

  AStarTrajPointT curr_astar_point = GenerateAStarTrajPointT(start);
  traj_stack.push(curr_astar_point);

  while (1) {
    if (curr_astar_point.Successors.empty()) {  // NO successors, trace back
      traj_stack.pop();
      if (traj_stack.empty()) {
        break;
      }
      curr_astar_point = traj_stack.top();

      // printf("Try to moving backward to [%d/%d]\n", curr_astar_point.Point.i,
      //         curr_astar_point.Point.j);
    } else if (curr_astar_point.Successors.find(end) !=
               curr_astar_point.Successors.end()) {
      // Route completed
      traj_stack.push(curr_astar_point);
      traj_stack.push(GenerateAStarTrajPointT(end));
      break;
    } else {  // Moving forward
      auto next_point = GetNextTrajPoint(curr_astar_point);
      traj_stack.top().Successors.erase(traj_stack.top().Successors.find(
          next_point));  // Used, remove from reserved container, directly
                         // operate on the stack because curr_astart_point is
                         // just a copy of that

      auto next_astar_point = GenerateAStarTrajPointT(next_point);
      curr_astar_point = next_astar_point;
      traj_stack.push(
          curr_astar_point);  // has succesors, valid point, store it.
      operated_points.emplace(curr_astar_point.Point);

      // printf("Try to moving forward to [%d/%d]\n", curr_astar_point.Point.i,
      //        curr_astar_point.Point.j);
    }
  }

  while (!traj_stack.empty()) {
    ret.emplace(traj_stack.top().Point);
    traj_stack.pop();
  }
  return std::move(ret);
}
