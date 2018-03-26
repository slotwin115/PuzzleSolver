
#include "PuzzleSolver.hpp"
using namespace pz;


// Konstruktor. Inicjalizuje planszê.
pz::PuzzleSolver::PuzzleSolver(Puzzle p)
{
	puzzle = p;
}

// Destruktor.
pz::PuzzleSolver::~PuzzleSolver()
{
	puzzle.clear();
}

// Sprawdza czy wspó³rzêdne s¹ poprawne.
bool pz::PuzzleSolver::checkBounds(const Tuple &pos, int size) const
{
	if (pos.i >= 0 && pos.i < size && pos.j >= 0 && pos.j < size)
		return true;
	return false;
}

/* Zwraca mo¿liwe ruchy.
np:
[Góra, Dó³, Lewo, Prawo]
*/
std::vector<Tuple> pz::PuzzleSolver::getNeighbours(const Tuple &node, int size) const
{
	std::vector<Tuple> coords;
	Tuple neighbour;

	neighbour.i = node.i - 1;
	neighbour.j = node.j;
	if (checkBounds(neighbour, size))
		coords.push_back(neighbour);

	neighbour.i = node.i + 1;
	neighbour.j = node.j;
	if (checkBounds(neighbour, size))
		coords.push_back(neighbour);

	neighbour.i = node.i;
	neighbour.j = node.j - 1;
	if (checkBounds(neighbour, size))
		coords.push_back(neighbour);

	neighbour.i = node.i;
	neighbour.j = node.j + 1;
	if (checkBounds(neighbour, size))
		coords.push_back(neighbour);

	return coords;
}

// Metoda rozwi¹zuj¹ca planszê. Jest rekurencyjna. Sprawdza wszystkie rozwi¹zania, które spe³niaj¹ warunek heurystyki.
Puzzle pz::PuzzleSolver::solveRecursively(Puzzle p, int step)
{
	//wspó³rzêdne pustego kafelka.
	Tuple empty = p.find(9);

	//mo¿liwe ruchy.
	std::vector<Tuple> neighbours = getNeighbours(empty, p.size());

	//najlepsza heurystyka i który ruch.
	Tuple h;
	h.j = p.heuristic();

	//wykonaj ruch -> sprawdŸ heurystykê -> jeœli lepsza od obecjnej -> zapisz -> **rekurencja** -> jeœli u³o¿ona -> koniec -> jeœli nie u³o¿ona -> cofnij ruch -->> zwróæ planszê.
	for (int i = 0; i < neighbours.size(); i++)
	{
		std::swap(p[empty.i][empty.j], p[neighbours[i].i][neighbours[i].j]);
		int tmp = p.heuristic();
		if (tmp <= h.j)
		{
			h.j = tmp;
			h.i = i;
			std::cout << "Step " << step << "\n";
			std::cout << p;
			Puzzle p1 = solveRecursively(p, ++step);
			if (p1.isSolved())
				return p1;
			step--;
		}
		std::swap(p[empty.i][empty.j], p[neighbours[i].i][neighbours[i].j]);
	}

	return p;
}

Puzzle pz::PuzzleSolver::solve()
{
	// którey ruch.
	int step = 1;

	// dopuki plansza nie jest rozwi¹zana
	while (!puzzle.isSolved())
	{
		//wspó³rzêdne pustego kafelka.
		Tuple empty = puzzle.find(9);

		//mo¿liwe ruchy.
		std::vector<Tuple> neighbours = getNeighbours(empty, puzzle.size());

		//najlepsza heurystyka i który ruch.
		Tuple h;
		h.j = puzzle.heuristic();

		//wykonaj ruch -> sprawdŸ heurystykê -->> jeœli lepsza od obecjnej -> zapisz -> cofnij ruch -->> jeœli nie znaleziono lepszej heurystyki od obecnej -> zwróæ planszê. -> wykonaj zapamiêtany ruch -->> zwróæ planszê.
		for (int i = 0; i < neighbours.size(); i++)
		{
			std::swap(puzzle[empty.i][empty.j], puzzle[neighbours[i].i][neighbours[i].j]);
			int tmp = puzzle.heuristic();
			if (tmp <= h.j)
			{
				h.j = tmp;
				h.i = i;
			}
			std::swap(puzzle[empty.i][empty.j], puzzle[neighbours[i].i][neighbours[i].j]);
		}

		if (h.i == -1 || h.j == -1)
			return puzzle;

		std::swap(puzzle[empty.i][empty.j], puzzle[neighbours[h.i].i][neighbours[h.i].j]);
		std::cout << "Step " << step++ << "\n" << puzzle;
	}

	return puzzle;
}

/* Zwraca planszê:
4 1 3
2 8
6 5 7
*/
pz::Puzzle pz::PuzzleSolver::defaultInit()
{
	Puzzle p(3);

	p[0][0] = 4;
	p[0][1] = 1;
	p[0][2] = 3;
	p[1][0] = 2;
	p[1][1] = 8;
	p[1][2] = 9;
	p[2][0] = 6;
	p[2][1] = 5;
	p[2][2] = 7;

	return p;
}

// Zwraca planszê o wartoœciach podanych przez u¿ytkownika.
pz::Puzzle pz::PuzzleSolver::userInit()
{
	Puzzle p(3);
	int size = p.size();
	std::string info = "";
	//std::string info = "Set square plain size(POSITIVE INTEGER): ";
	//int size = getInt(info, s, s);

	std::cout << "Please enter desired numbers from interval [1, 9].\n[1, 8] be values. \'9\' be empty node.\n";
	std::vector<int> chosenValues;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			info = "[" + std::to_string(i) + "][" + std::to_string(j) + "] = ";
			int n = getInt(info, 1, 9);
			while (find(chosenValues.begin(), chosenValues.end(), n) != chosenValues.end())
			{
				std::cout << "Enter nonredundant number.\n";
				n = getInt(info, 1, 9);
			}

			p[i][j] = n;
			chosenValues.push_back(n);
		}
	}

	return p;
}

// Wype³nia wektor plansz, wszystkimi mo¿liwymi permutacjami planszy
void pz::PuzzleSolver::allPermutations(std::vector<Puzzle>& allPuzzles, unsigned int value)
{
	int n = value + 1;
	std::vector<int> v;
	for (int i = 1; i < n; i++)
		v.push_back(i);

	PuzzleSolver::permute(v, 0, v.size() - 1, allPuzzles);
}

// Pobiera liczbê ca³kowit¹ od u¿ytkownika.
int pz::PuzzleSolver::getInt(const std::string & info, int lowBound, int upBound)
{
	int number;
	std::string str = "";
	while (true)
	{
		std::cout << info;
		std::getline(std::cin, str);
		std::stringstream line(str);
		if ((line >> number) && number >= lowBound && number <= upBound)
			return number;
		std::cout << "Invalid input, try again." << std::endl;
	}
}

// Dodaje permutacje wektora a do wektora p. Metoda jest rekurencyjna.
void pz::PuzzleSolver::permute(std::vector<int>& a, int l, int r, std::vector<Puzzle>& p)
{
	if (l == r)
	{
		Puzzle puzzle;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				puzzle[i][j] = a[i * 3 + j];
			}
		}
		p.push_back(puzzle);
	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			std::swap(a[0 + l], a[0 + i]);
			permute(a, l + 1, r, p);
			std::swap(a[0 + l], a[0 + i]);
		}
	}
}

// Inicjalizuje planszê.
void pz::PuzzleSolver::setPuzzle(Puzzle p)
{
	puzzle = p;
}

// Zwraca aktualn¹ planszê.
Puzzle pz::PuzzleSolver::getPuzzle() const
{
	return puzzle;
}
