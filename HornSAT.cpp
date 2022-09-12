#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>

class HornSat
{
public:
  struct Implication
  {
    std::vector<int> implicants;
    int consequent;
  };

  explicit HornSat(size_t);
  void inputFormula(std::istream&);
  void solveHornSAT();
  void printSolution(std::ostream&);

private:
  std::vector<Implication> clauses_;
  std::vector<std::vector<int>> adjClauses_;
  std::vector<bool> solution_;

  bool isSAT_ = true;
};


HornSat::HornSat(size_t size) :
  adjClauses_(size),
  solution_(size)
{}


void HornSat::inputFormula(std::istream& in)
{
  size_t index = 0;

  while (!in.eof())
  {
    std::string input;
    std::getline(in >> std::ws, input);
    std::stringstream sin(input);

    if(in.eof())
    {
      break;
    }

    bool firstPart = true;
    clauses_.push_back({});

    while (!sin.eof())
    {
      std::string temp;

      sin >> temp;
      if (temp != "&" && firstPart && temp != "->")
      {
        int num = std::stoi(temp);
        clauses_[index].implicants.push_back(num);
      }
      else if (temp == "->")
      {
        firstPart = false;
      }
      else if (temp != "&" && !firstPart)
      {
        int num = std::stoi(temp);
        clauses_[index].consequent = num;
      }
    }
    index++;
  }
}


void HornSat::solveHornSAT()
{
  size_t numClauses = clauses_.size();
  std::queue<int> toVisit;
  std::vector<size_t> negVarNum(numClauses);

  for (size_t c = 0; c < numClauses; ++c)
  {
    auto clause = clauses_[c];
    auto implicants = clauses_[c].implicants;

    negVarNum[c] = implicants.size();

    if (implicants.empty()) // 1 -> consequent
    {
      toVisit.push(clauses_[c].consequent);
    }

    for (int implicant : implicants) // Для каждой отрицательной переменной будем хранить
      // все номера дизъюнктов, где она встречается
    {
      adjClauses_[implicant].push_back(c);
    }
  }

  while (!toVisit.empty())
  {
    int posVar = toVisit.front();
    toVisit.pop();

    if (posVar < 0) // (posVar = False) => (1 -> 0)
    {
      isSAT_ = false;
      return;
    }

    if (solution_[posVar]) // Если переменная уже True, идем дальше
    {
      continue;
    }
    solution_[posVar] = true;

    auto clauseSet = adjClauses_[posVar];

    for (int c : clauseSet) // Перебираем все дизъюнкты, в которых встречается posVar
    {
      if (--negVarNum[c] == 0)
      {
        toVisit.push(clauses_[c].consequent);
      }
    }
  }
}


void HornSat::printSolution(std::ostream& out)
{
  if (isSAT_)
  {
    out << "Satisfiable: \n";
    for (auto&& i : solution_)
    {
      out << (i ? "True " : "False ");
    }
  }
  else out << "Unsatisfiable";
}


int main()
{
  int size = 0;
  std::cin >> size;

  HornSat hornsat(size);

  hornsat.inputFormula(std::cin);
  hornsat.solveHornSAT();
  hornsat.printSolution(std::cout);

  return 0;
}
