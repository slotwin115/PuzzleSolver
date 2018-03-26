#include "PuzzleSolver.hpp"
#include <fstream>
using namespace std;

void main()
{
	int init = pz::PuzzleSolver::getInt("Init options:\n1. User\n2. Default\n>", 1, 2);
	pz::PuzzleSolver solver(pz::PuzzleSolver::defaultInit());
	if (init == 1)
		solver.setPuzzle(pz::PuzzleSolver::userInit());
	else
		solver.setPuzzle(pz::PuzzleSolver::defaultInit());

	cout << "\nYour puzzle:\n" << solver.getPuzzle();




	int solve = pz::PuzzleSolver::getInt("Solving options:\n1. Recursive\n2. Regular\n>", 1, 2);
	cout << endl;
	pz::Puzzle solution;
	if (solve == 1)
		solution = solver.solveRecursively(solver.getPuzzle());
	else
		solution = solver.solve();

	if (solution.isSolved())
		cout << "Solution reached.\n\n";
	else
		cout << "Failed to reach solution.\nSolver stuck in local extreme.\n\n";




	system("pause");
}