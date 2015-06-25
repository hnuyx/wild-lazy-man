/* a.cpp
 * build a simple program using boost
 */
#include <iostream>
#include <iterator>
#include <algorithm>

#include <boost/lambda/lambda.hpp>

int main()
{
	//using namespace boost::lambda;

	typedef std::istream_iterator<int> in;
	std::for_each(
		in(std::cin), in(), std::cout<< (boost::lambda::_1 * 3) << " ");
	return 0;
}
