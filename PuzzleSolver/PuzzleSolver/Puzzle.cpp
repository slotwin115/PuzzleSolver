
#include "Puzzle.hpp"
using namespace pz;


// Konstruktor. Inicjalizuje zerami plansz� kwadratow� o zadanym rozmiarze. Domy�lnie 3.
Puzzle::Puzzle(int size)
{
	puzzle.resize(size);
	for (int i = 0; i < size; i++)
	{
		puzzle[i].resize(size);
		for (int j = 0; j < size; j++)
		{
			puzzle[i][j] = 0;
		}
	}
}

// Destruktor.
Puzzle::~Puzzle()
{
	puzzle.clear();
}


std::vector<int>& Puzzle::operator[] (int index)
{
	return puzzle[index];
}


const std::vector<int>& Puzzle::operator[] (int index) const
{
	return puzzle[index];
}

// Szuka podanego elementu w planszy i zwraca jego wsp�rz�dne.
Tuple Puzzle::find(int x)
{
	Tuple f;
	int n = puzzle.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (puzzle[i][j] == x)
			{
				f.i = i;
				f.j = j;
			}
		}
	}

	return f;
}

// Zwraca prawid�owe wsp�rz�dne dla danej warto�ci.
Tuple pz::Puzzle::correctPosition(int number)
{
	Tuple pos;
	pos.i = ((number - 1) % 3);
	pos.j = (number > 6 ? 2 : (number > 3 ? 1 : 0));
	return pos;
}

// Sprawdza czy plansza jest rozwi�zaniem.
bool Puzzle::isSolved() const
{
	int n = puzzle.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (puzzle[i][j] != (j * 3 + i + 1))
				return false;
		}
	}

	return true;
}

// Oblicza heurystyk� planszy.
int Puzzle::heuristic()
{
	int h = 0;
	const int n = puzzle.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (puzzle[i][j] != 9)
			{
				Tuple tmp = correctPosition(puzzle[i][j]);
				h += abs(tmp.i - i) + abs(tmp.j - j);
			}
		}
	}

	return h;
}

/* Zwraca rozmiar planszy.
np: n je�li plansza jest n x n
*/
unsigned int Puzzle::size() const
{
	return puzzle.size();
}

// Zwalnia pami��.
void pz::Puzzle::clear()
{
	puzzle.clear();
}

// Przeci��ony operator piasania do strumienia.
std::ostream & pz::operator<<(std::ostream & out, const Puzzle & p)
{
	int n = p.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (p[i][j] == 9)
				out << " " << " ";
			else
				out << p[i][j] << " ";
		}
		out << "\n";
	}
	out << "\n\n";

	return out;
}
