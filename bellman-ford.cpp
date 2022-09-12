#include "directed-graph.hpp"

int main()
{
  size_t size;
  std::cin >> size;

  DirectedGraph graph(size);

  graph.inputGraph(std::cin);
  graph.BellmanFordShortestPaths();
  graph.outputGraph(std::cout);


  // пример массива для задания 6
  std::vector<double> a;
  a.push_back(0);
  a.push_back(3);
  a.push_back(2.5);
  a.push_back(3.5);
  a.push_back(1);
  a.push_back(std::numeric_limits<double>::infinity());

  std::cout << "\nArray {";
  for(size_t i = 0; i < a.size(); ++i)
  {
    std::cout << a[i];
    if(i != a.size() - 1)
    {
      std::cout << ", ";
    }
    else std::cout << "}";
  }

  if(graph.verifyArray(a, 0))
  {
    std::cout << " is an array with shortest paths";
  }
  else std::cout << " is not an array with shortest paths";

  return 0;
}