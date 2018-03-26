
#include "Tuple.hpp"
using namespace pz;

// Przeciążony operator pisania do strumienia.
std::ostream & pz::operator<<(std::ostream & out, const Tuple & t)
{
	return out << "(" << t.i << "," << t.j << ")";
}
