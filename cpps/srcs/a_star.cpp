#include "cpps/includes/a_star.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include <array>
#include <limits>
#include <list>
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
    std::set<PointT> SuccessorCandidates;
  };

  // TODO, consolidate these containers
  std::stack<AStarTrajPointT> traj_stack;
  std::list<AStarTrajPointT> traj_list;
  std::set<PointT> operated_points;
  auto cost_func = [](const PointT& a,
                      const PointT& b) -> double {  // eular distance as cost
    return std::hypot(a.i - b.i, a.j - b.j);
  };

  auto GenerateAStarTrajPointT = [&traj_list, &operated_points, &obs](
                                     const PointT& point) -> AStarTrajPointT {
    AStarTrajPointT a_star_point;
    a_star_point.Point = point;
    std::set<PointT> four_direction_movement_points{{point.i - 1, point.j},
                                                    {point.i, point.j - 1},
                                                    {point.i, point.j + 1},
                                                    {point.i + 1, point.j}};

    std::set<PointT> eight_direction_movement_points{
        {point.i - 1, point.j},     {point.i, point.j - 1},
        {point.i, point.j + 1},     {point.i + 1, point.j},
        {point.i - 1, point.j - 1}, {point.i - 1, point.j + 1},
        {point.i + 1, point.j - 1}, {point.i + 1, point.j + 1}};
    // for (const auto& next_point : four_direction_movement_points) {
    for (const auto& next_point : eight_direction_movement_points) {
      if (next_point.i < 0 || next_point.j < 0 || next_point.i >= kHeight ||
          next_point.j >= kWidth) {  // index out of range
        continue;
      }
      if (obs.find(next_point) != obs.end()) {  // Obstacle
        continue;
      }
      if (operated_points.find(next_point) != operated_points.end()) {
        continue;  // Already tried before, skip
      }
      bool bIsDuplicatedSuccessor{false};
      for (const auto& existing_traj_point : traj_list) {
        if (existing_traj_point.SuccessorCandidates.find(next_point) !=
            existing_traj_point.SuccessorCandidates.end()) {
          bIsDuplicatedSuccessor = true;
          break;
        }
      }
      if (bIsDuplicatedSuccessor) {
        continue;
      }  // Already existing in previous one's successors, has a relative
         // smaller cost(1 + 1 > sqrt(2), 1 + sqrt(2) > 1)
      a_star_point.SuccessorCandidates.emplace(next_point);
    }
    return a_star_point;
  };

  auto GetNextTrajPoint =
      [&end, &cost_func](const AStarTrajPointT& a_star_point) -> PointT {
    double min_cost = std::numeric_limits<double>::max();
    PointT next_point;
    for (const auto& successor : a_star_point.SuccessorCandidates) {
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
  operated_points.emplace(curr_astar_point.Point);
  traj_list.push_back(curr_astar_point);

  while (1) {
    if (curr_astar_point.SuccessorCandidates
            .empty()) {  // NO successors, trace back
      traj_stack.pop();
      traj_list.pop_back();
      if (traj_stack.empty()) {
        break;
      }
      curr_astar_point = traj_stack.top();

      // printf("Try to moving backward to [%d/%d]\n",
      // curr_astar_point.Point.i,
      //         curr_astar_point.Point.j);
    } else if (curr_astar_point.SuccessorCandidates.find(end) !=
               curr_astar_point.SuccessorCandidates.end()) {
      // Route completed
      traj_stack.push(curr_astar_point);
      traj_stack.push(GenerateAStarTrajPointT(end));
      break;
    } else {  // Moving forward
      auto next_point = GetNextTrajPoint(curr_astar_point);
      traj_stack.top().SuccessorCandidates.erase(
          traj_stack.top().SuccessorCandidates.find(
              next_point));  // Used, remove from reserved container, directly
                             // operate on the stack because curr_astart_point
                             // is just a copy of that

      curr_astar_point = GenerateAStarTrajPointT(next_point);
      traj_stack.push(
          curr_astar_point);  // has succesors, valid point, store it.
      traj_list.push_back(curr_astar_point);
      operated_points.emplace(curr_astar_point.Point);

      // printf("Try to moving forward to [%d/%d]\n",
      // curr_astar_point.Point.i,
      //        curr_astar_point.Point.j);
    }
  }

  // TO BE IMPROVED
  while (!traj_stack.empty()) {
    ret.emplace(traj_stack.top().Point);
    traj_stack.pop();
  }
  return std::move(ret);
}
