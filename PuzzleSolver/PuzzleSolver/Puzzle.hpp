#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <vector>
#include <ostream>
#include "Tuple.hpp"

namespace pz
{
	/* Klasa Puzzle: reprezentuje plansz�.
	np:
	1 4 7
	2 5 8
	3 6
	*/
	class Puzzle
	{
	private:
		std::vector<std::vector<int>> puzzle;

	public:
		// Konstruktor. Inicjalizuje zerami plansz� kwadratow� o zadanym rozmiarze. Domy�lnie 3.
		Puzzle(int size = 3);

		// Destruktor.
		~Puzzle();

	public:
		std::vector<int>& operator[] (int index);
		const std::vector<int>& operator[] (int index) const;

		// Szuka podanego elementu w planszy i zwraca jego wsp�rz�dne.
		Tuple find(int x);

		// Zwraca prawid�owe wsp�rz�dne dla danej warto�ci.
		static Tuple correctPosition(int number);

		// Sprawdza czy plansza jest rozwi�zaniem.
		bool isSolved() const;

		// Oblicza heurystyk� planszy.
		int heuristic();

		/* Zwraca rozmiar planszy.
		np: n je�li plansza jest n x n
		*/
		unsigned int size() const;

		// Zwalnia pami��.
		void clear();

		// Przeci��ony operator piasania do strumienia.
		friend std::ostream& operator<< (std::ostream &out, const Puzzle &p);
	};
}

#endif // !PUZZLE_HPP

