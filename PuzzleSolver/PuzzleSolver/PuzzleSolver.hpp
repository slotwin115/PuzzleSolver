#ifndef PUZZLESOLVER_HPP
#define PUZZLESOLVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "Puzzle.hpp"

namespace pz
{
	/* Klasa PuzzleSolver: reprezentuje proces rozwi�zania planszy(Puzzle).
	*/
	class PuzzleSolver
	{
	private:
		Puzzle puzzle;

	public:
		// Konstruktor. Inicjalizuje plansz�.
		PuzzleSolver(Puzzle p);

		// Destruktor.
		~PuzzleSolver();

	public:

		// Metoda rozwi�zuj�ca plansz�. Jest rekurencyjna. Sprawdza wszystkie rozwi�zania, kt�re spe�niaj� warunek heurystyki.
		Puzzle solveRecursively(Puzzle p, int step = 1);

		Puzzle solve();

		/* Zwraca plansz�:
		4 1 3
		2 8
		6 5 7
		*/
		static Puzzle defaultInit();

		// Zwraca plansz� o warto�ciach podanych przez u�ytkownika.
		static Puzzle userInit();

		// Wype�nia wektor plansz, wszystkimi mo�liwymi permutacjami planszy
		static void allPermutations(std::vector<Puzzle> &allPuzzles, unsigned int value);

		// Dodaje permutacje wektora a do wektora p. Metoda jest rekurencyjna.
		static void permute(std::vector<int> &a, int l, int r, std::vector<Puzzle> &p);

		// Inicjalizuje plansz�.
		void setPuzzle(Puzzle p);

		// Zwraca aktualn� plansz�.
		Puzzle getPuzzle() const;

		// Pobiera liczb� ca�kowit� od u�ytkownika.
		static int getInt(const std::string &info, int lowBound, int upBound);

	private:
		// Sprawdza czy wsp�rz�dne s� poprawne.
		bool checkBounds(const Tuple &pos, int size) const;

		/* Zwraca mo�liwe ruchy.
		np:
		[G�ra, D�, Lewo, Prawo]
		*/
		std::vector<Tuple> getNeighbours(const Tuple &coord, int size) const;
	};
}

#endif // !PUZZLESOLVER_HPP

