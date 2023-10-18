#include <iostream>
#include "complex.h"

int main()
{
	std::vector<Complex> complex_vec;
	complex_vec.push_back((Complex(12, 7)));
	complex_vec.push_back(Complex(12, 6));
	complex_vec.push_back(Complex(25));
	complex_vec.push_back(Complex(3, 4));
	complex_vec.push_back((Complex(12, 7) - Complex(4, 7) ));
	complex_vec.push_back((Complex(12, 7) + Complex(4, 7) ));
	complex_vec.push_back(Complex());
	sort_complex(complex_vec);
	for(Complex i:complex_vec)
	{
		std::cout<<i<<" ";
	} 
	std::cout<<std::endl;      
	return 0;
}
