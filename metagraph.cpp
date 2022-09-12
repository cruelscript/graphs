#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

typedef std::vector<std::vector<int>> Graph;

Graph findReversed(Graph& graph)
{
  Graph reversedGraph(graph.size());

  for (size_t i = 0; i < graph.size(); ++i)
  {
    for (size_t j = 0; j < graph[i].size(); ++j)
    {
      reversedGraph[graph[i][j]].push_back(i);
    }
  }
  return reversedGraph;
}

void visit(int v,
           Graph& G,
           std::vector<bool>& visited,
           std::vector<int>& pre,
           std::vector<int>& post,
           int& clock,
           std::stack<int>& L)
{
  visited[v] = true;

  pre[v] = clock++; // previsit

  for (size_t i = 0; i < G[v].size(); ++i)
  {
    if (!visited[G[v][i]])
    {
      visit(G[v][i], G, visited, pre, post, clock, L);
    }
  }
  post[v] = clock++; // postvisit

  L.push(v);
}

void dfs(Graph& G,
         std::vector<bool>& visited,
         std::vector<int>& pre,
         std::vector<int>& post,
         int& clock,
         std::stack<int>& L
         )
{
  for (size_t i = 0; i < G.size(); ++i)
  {
    visited[i] = false;
  }

  for (size_t i = 0; i < G.size(); ++i)
  {
    if (!visited[i])
    {
      visit(i, G, visited, pre, post, clock, L);
    }
  }
}

void explore(int v,
             Graph& G,
             std::vector<bool>& visited,
             std::vector<int>& numSCC,
             int& curSCC)
{
  visited[v] = true;

  numSCC[v] = curSCC; // previsit

  for (size_t i = 0; i < G[v].size(); ++i)
  {
    if (!visited[G[v][i]])
    {
      explore(G[v][i], G, visited, numSCC, curSCC);
    }
  }
}

void dfs2(Graph& G,
          std::vector<bool>& visited,
          std::vector<int>& numSCC,
          int& curSCC,
          std::stack<int> L)
{
  for (size_t i = 0; i < G.size(); ++i)
  {
    visited[i] = false;
  }

  while (!L.empty())
  {
    int i = L.top();
    if (!visited[i])
    {
      curSCC++;
      explore(i, G, visited, numSCC, curSCC);
    }
    L.pop();
  }
}

Graph createMetaGraph(Graph& G,
                      size_t nSCC,
                      std::vector<int>& numSCC)
{
  Graph metaGraph(nSCC);
  std::vector<bool> metaVisited(nSCC * nSCC);

  for(auto && i : metaVisited)
  {
    i = false;
  }

  for(size_t i = 0; i < G.size(); ++i)
  {
    for(size_t j = 0; j < G[i].size(); ++j)
    {
      if(numSCC[i] != numSCC[G[i][j]] && !metaVisited[numSCC[i] * nSCC + numSCC[G[i][j]]])
      {
        metaVisited[numSCC[i] * nSCC + numSCC[G[i][j]]] = true;
        metaGraph[numSCC[i]].push_back(numSCC[G[i][j]]);
      }
    }
  }
  return metaGraph;
}

int main()
{
  size_t size;
  std::cin >> size;

  Graph graph(size);

  // input graph
  int vertex;
  for(size_t i = 0; i < size; ++i)
  {
    std::cin >> vertex;

    int u;
    std::cin >> u;

    while(u != -1)
    {
      graph[vertex].push_back(u);
      std::cin >> u;
    }
  }

  Graph reversedG = findReversed(graph);

  std::vector<bool> visited(size);
  std::vector<int> pre(size);
  std::vector<int> post(size);
  std::stack<int> L;
  int clock = 1;

  dfs(reversedG, visited, pre, post, clock, L);

  std::vector<int> numSCC(size);
  int curSCC = -1;

  dfs2(graph, visited, numSCC, curSCC, L);

  // print SCC
  Graph SCCs(curSCC + 1);
  for (size_t i = 0; i < numSCC.size(); ++i)
  {
    SCCs[numSCC[i]].push_back(i);
  }

  for (size_t i = 0; i < SCCs.size(); ++i)
  {
    std::cout << "SCC " << i << ":   ";
    for (auto j : SCCs[i])
    {
      std::cout << j << " ";
    }
    std::cout << "\n";
  }

  Graph metaGraph = createMetaGraph(graph, SCCs.size(), numSCC);

  // print meta-graph
  std::cout << "Meta-graph:\n";
  for(size_t i = 0; i < metaGraph.size(); ++i)
  {
    std::cout << i << "   ";

    for(size_t j = 0; j < metaGraph[i].size(); ++j)
    {
      std::cout << metaGraph[i][j] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}

