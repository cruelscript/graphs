#ifndef DIRECTED_GRAPH_HPP
#define DIRECTED_GRAPH_HPP

#include <vector>
#include <limits>
#include <iostream>

class DirectedGraph
{
public:

  typedef struct
  {
    int node;
    double weight;
  } Entry;

  explicit DirectedGraph(size_t);
  void inputGraph(std::istream&);
  void BellmanFordShortestPaths();
  void outputGraph(std::ostream&);
  bool verifyArray(std::vector<double> a, int s);

private:

  const double INF = std::numeric_limits<double>::infinity();
  const int NAV = -1; // Not a vertex
  bool isNegCycle = false; // Для проверки, на наличие циклов отрицательного веса
  int startVertex_;

  std::vector<std::vector<Entry>> graph_;
  std::vector<std::vector<int>> tree_;
  std::vector<double> dist_;
  std::vector<double> prev_;
  std::vector<bool> isVisited_;

  void visit(int v, std::ostream& out, int gap = 2);
};

#endif //DIRECTED_GRAPH_HPP
