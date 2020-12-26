#include "cpps/includes/a_star.h"

#include <assert.h>
#include <stdio.h>

#include <array>

constexpr int kWidth{20};
constexpr int kHeight{16};

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
  return std::move(ret);
}
