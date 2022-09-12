#include "directed-graph.hpp"

DirectedGraph::DirectedGraph(size_t size):
  graph_(size),
  tree_(size),
  dist_(size, INF),
  prev_(size, NAV),
  isVisited_(size, false),
  startVertex_(0)
{}

void DirectedGraph::inputGraph(std::istream& in)
{
  for(size_t i = 0; i < graph_.size(); ++i)
  {
    int vertex;
    in >> vertex;

    int u;
    double w;
    in >> u;

    while(u != -1)
    {
      in >> w;
      graph_[vertex].push_back({u, w});
      in >> u;
    }
  }
  in >> startVertex_;
}

void DirectedGraph::BellmanFordShortestPaths()
{
  bool stop = false; // Для оптимизации алгоритма, будем выходить из цикла,
                     // когда все ребра уже срелаксированы

  dist_[startVertex_] = 0;

  for(size_t k = 1; k <= graph_.size() && !stop; ++k)
  {
    stop = true;
    for(size_t i = 0; i < graph_.size(); ++i)
    {
      for(size_t j = 0; j < graph_[i].size(); ++j)
      {
        int vertex = i;
        int adjVertex = graph_[i][j].node;
        double weight = graph_[i][j].weight;

        // релаксация ребра (vertex, adjVertex)
        if(dist_[vertex] + weight < dist_[adjVertex])
        {
          dist_[adjVertex] = dist_[vertex] + weight;
          prev_[adjVertex] = vertex;

          stop = false;

          if(k == graph_.size())
          {
            isNegCycle = true;
            break;
          }
        }
      }
    }
  }
  // создание дерева кратчайших путей
  for(size_t i = 0; i < graph_.size(); ++i)
  {
    if(prev_[i] != NAV)
    {
      tree_[prev_[i]].push_back(i);
    }
  }
}

void DirectedGraph::outputGraph(std::ostream& out)
{
  if(isNegCycle)
  {
    out << "\nA negative-weight cycle is reachable from the source vertex.";
  }
  else
  {
    out << "\nThe weight of a shortest path from vertex " <<
      startVertex_ << " to vertex\n";

    for(size_t i = 0; i < graph_.size(); ++i)
    {
      out << i << "  is  " << dist_[i] << "\n";
    }

    out << "\nThe shortest-path tree: \n";
    out << startVertex_ << "\n";

    visit(startVertex_, out);

    for(size_t i = 0; i < graph_.size(); ++i)
    {
      visit(i, out);
    }
  }
}

void DirectedGraph::visit(int v, std::ostream& out, int gap)
{
  isVisited_[v] = true;

  for(size_t u: tree_[v])
  {
    if(!isVisited_[u])
    {
      for(size_t j = 0; j < gap; ++j)
      {
        out << " ";
      }
      out << u << "\n";

      visit(u, out, gap + 2);
    }
  }
}

bool DirectedGraph::verifyArray(std::vector<double> a, int s)
{
  if(a[s] != 0)
  {
    return false;
  }

  for(size_t i = 0; i < graph_.size(); ++i)
  {
    for(size_t j = 0; j < graph_[i].size(); ++j)
    {
      int vertex = i;
      int adjVertex = graph_[i][j].node;
      double weight = graph_[i][j].weight;

      // релаксация ребра (vertex, adjVertex)
      if(a[vertex] + weight < a[adjVertex])
      {
        return false;
      }
    }
  }
  return true;
}
