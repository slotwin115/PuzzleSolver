
#include "Tuple.hpp"
using namespace pz;

// Przeci��ony operator pisania do strumienia.
std::ostream & pz::operator<<(std::ostream & out, const Tuple & t)
{
	return out << "(" << t.i << "," << t.j << ")";
}
