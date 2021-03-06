

#include "logging.h"
#include "wedgebase.h"
#include <ginac/power.h>

namespace Wedge {

/** @brief The normal form of a linear combination of vectors (either of type Vector or LambdaVector)
*
* This class allows iterating through nonzero coefficients. The order is determined by ex_is_less, evaluated on vectors.
* Dereferencing the iterator gives a pair<ex,ex> where the first element is a VectorBase wrapped in an ex, and the second element a scalar expression
*
* test:is_a<VectorBase>(*i);
*/

class VectorNormalForm {
	friend class LambdaVectorNormalForm;
	exmap coefficients;
public:
	VectorNormalForm() {};
	VectorNormalForm(ex linear_combination);

	using const_iterator = exmap::const_iterator;
	const_iterator begin() const {return coefficients.begin();}
	const_iterator end() const {return coefficients.end();}
/** @brief Return a normal form in which coefficients are collected
*
* e.g. a*e(1)-a*e(2)+a*e(3) -> a*(e(1)-e(2)+e(3))
*/
	ex CollectCoefficients() const;
};


struct LambdaVectorNormalForm {
	ex scalar_part;
	VectorNormalForm vector_part, lambda_vector_part;
	LambdaVectorNormalForm(ex linear_combination);
	using const_iterator = exmap::const_iterator;
};

inline ostream& operator<<(ostream& os, const VectorNormalForm& linear_combination)
{
	return os<<linear_combination.CollectCoefficients();
}

}
