#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <vector>
#include <ostream>
#include "Tuple.hpp"

namespace pz
{
	/* Klasa Puzzle: reprezentuje planszê.
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
		// Konstruktor. Inicjalizuje zerami planszê kwadratow¹ o zadanym rozmiarze. Domyœlnie 3.
		Puzzle(int size = 3);

		// Destruktor.
		~Puzzle();

	public:
		std::vector<int>& operator[] (int index);
		const std::vector<int>& operator[] (int index) const;

		// Szuka podanego elementu w planszy i zwraca jego wspó³rzêdne.
		Tuple find(int x);

		// Zwraca prawid³owe wspó³rzêdne dla danej wartoœci.
		static Tuple correctPosition(int number);

		// Sprawdza czy plansza jest rozwi¹zaniem.
		bool isSolved() const;

		// Oblicza heurystykê planszy.
		int heuristic();

		/* Zwraca rozmiar planszy.
		np: n jeœli plansza jest n x n
		*/
		unsigned int size() const;

		// Zwalnia pamiêæ.
		void clear();

		// Przeci¹¿ony operator piasania do strumienia.
		friend std::ostream& operator<< (std::ostream &out, const Puzzle &p);
	};
}

#endif // !PUZZLE_HPP

