#ifndef PUZZLESOLVER_HPP
#define PUZZLESOLVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "Puzzle.hpp"

namespace pz
{
	/* Klasa PuzzleSolver: reprezentuje proces rozwi¹zania planszy(Puzzle).
	*/
	class PuzzleSolver
	{
	private:
		Puzzle puzzle;

	public:
		// Konstruktor. Inicjalizuje planszê.
		PuzzleSolver(Puzzle p);

		// Destruktor.
		~PuzzleSolver();

	public:

		// Metoda rozwi¹zuj¹ca planszê. Jest rekurencyjna. Sprawdza wszystkie rozwi¹zania, które spe³niaj¹ warunek heurystyki.
		Puzzle solveRecursively(Puzzle p, int step = 1);

		Puzzle solve();

		/* Zwraca planszê:
		4 1 3
		2 8
		6 5 7
		*/
		static Puzzle defaultInit();

		// Zwraca planszê o wartoœciach podanych przez u¿ytkownika.
		static Puzzle userInit();

		// Wype³nia wektor plansz, wszystkimi mo¿liwymi permutacjami planszy
		static void allPermutations(std::vector<Puzzle> &allPuzzles, unsigned int value);

		// Dodaje permutacje wektora a do wektora p. Metoda jest rekurencyjna.
		static void permute(std::vector<int> &a, int l, int r, std::vector<Puzzle> &p);

		// Inicjalizuje planszê.
		void setPuzzle(Puzzle p);

		// Zwraca aktualn¹ planszê.
		Puzzle getPuzzle() const;

		// Pobiera liczbê ca³kowit¹ od u¿ytkownika.
		static int getInt(const std::string &info, int lowBound, int upBound);

	private:
		// Sprawdza czy wspó³rzêdne s¹ poprawne.
		bool checkBounds(const Tuple &pos, int size) const;

		/* Zwraca mo¿liwe ruchy.
		np:
		[Góra, Dó³, Lewo, Prawo]
		*/
		std::vector<Tuple> getNeighbours(const Tuple &coord, int size) const;
	};
}

#endif // !PUZZLESOLVER_HPP

