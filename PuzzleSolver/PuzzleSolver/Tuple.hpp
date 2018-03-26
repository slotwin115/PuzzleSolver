#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <ostream>

namespace pz
{
	// Struktura Tuple: reprezentuje parê liczb ca³kowitych.
	struct Tuple
	{
		int i = -1;
		int j = -1;

		// Przeci¹¿ony operator pisania do strumienia.
		friend std::ostream& operator<< (std::ostream &out, const Tuple &t);
	};
}

#endif // !TUPLE_HPP

