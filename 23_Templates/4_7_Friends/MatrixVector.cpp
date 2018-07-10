// 23.4.7 Friends
// a template class can designate functions as friends

#include <initializer_list>
#include <stdexcept>

template<typename T>
class Matrix;

template<typename T>
class Vector
{
	T v[4] = {};
public:
	Vector() = default;
	Vector(std::initializer_list<T> values)
	{
		if (values.size() != 4)
			throw std::out_of_range("size must be 4");
		std::copy(values.begin(), values.end(), v);
	}
	// Following declaration is not supported and leads to syntax error on MSVC, GCC, Clang
	//friend Vector operator*<>(const Matrix<T>& mat, const Vector& vec);
	template<typename U>
	friend Vector<U> operator*(const Matrix<U>& mat, const Vector<U>& vec);
};

template<typename T>
class Matrix
{
	Vector<T> v[4];
public:
	Matrix() = default;
	Matrix(std::initializer_list<Vector<T>> values)
	{
		if (values.size() != 4)
			throw std::out_of_range("size must be 4");
		std::copy(values.begin(), values.end(), v);
	}
	template<typename U>
	friend Vector<U> operator*(const Matrix<U>& mat, const Vector<U>& vec);
};


template<typename T>
Vector<T> operator*(const Matrix<T>& mat, const Vector<T>& vec)
{
	Vector<T> r;
	for (int i = 0; i != 4; ++i)
	{
		for (int j = 0; j != 4; ++j)
			r.v[i] += mat.v[i].v[j] * vec.v[j];
	}
	return r;
}

int main()
{
	Vector<int> v1 = { 1, 2, 3, 4 };
	Matrix<int> m1 = {
		{ 1, 1, 1, 1 },
		{ 2, 2, 2, 2 },
		{ 3, 3, 3, 3 },
		{ 4, 4, 4, 4 } };
	auto r = m1 * v1; // { 10, 20, 30, 40 }
	return 0;
}