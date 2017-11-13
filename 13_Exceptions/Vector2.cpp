#include <memory> // allocator

// memory structure for vector
// deals with memory and leaves concerns about objects to vector
template<typename T, typename A = std::allocator<T>>
struct vector_base
{
	A alloc;  // allocator
	T* elem;  // start of allocation
	T* space; // end of element sequence, start of space allocated for possible expansion
	T* last;  // end of allocated space

	vector_base(const A& a, typename A::size_type n)
		:	alloc{ a }, elem{ alloc.allocate(n) }, space{ elem + n },
			last{ elem + n }
	{}

	~vector_base()
	{
		alloc.deallocate(elem, last - elem);
	}

	// no copy operations
	vector_base(const vector_base&) = delete;
	vector_base& operator=(const vector_base&) = delete;

	vector_base(vector_base&& other)
		:	alloc { other.alloc}, elem{ other.elem }, space{ other.space },
			last{ other.last }
	{
		other.elem = other.space = other.last = nullptr; // no longer owns memory
	}

	vector_base& operator=(vector_base&& other)
	{
		std::swap(*this, other);
		return *this;
	}
};

template<typename T, typename A = std::allocator<T>>
class vector
{
	vector_base<T, A> vb;
	void destroy_elements()
	{
		for (iterator p = vb.elem; p != vb.space; ++p)
			vb.alloc.destroy(p); // p->~T();
		vb.space = vb.elem;
	}
public:
	using size_type = typename A::size_type;
	using iterator = T*;
	using const_iterator = const T*;

	vector(size_type n, const T& val = T(), const A& a = A())
		: vb{ a, n }
	{
		std::uninitialized_fill(vb.elem, vb.elem + n, val); // copy elements
	}

	vector(const vector& a)
		: vb{ a.vb.alloc, a.size() }
	{
		std::uninitialized_copy(a.begin(), a.end(), vb.elem);
	}

	vector(vector&& a)
		: vb{ std::move(a.vb) } // transfer ownership
	{}

	//// straightforward implementation
	//vector& operator=(const vector& a)
	//{
	//	vector_base<T, A> b{ a.vb.alloc, a.size() }; // get the memory
	//	std::uninitialized_copy(a.begin(), a.end(), vb.elem); // copy elements
	//	destroy_elements(); // destroy elements
	//	std::swap(vb, b); // transfer ownership
	//	return *this; // implicitly destroy the old value
	//}

	//// avoid repetition
	//vector& operator=(const vector& a)
	//{
	//	// possible optimizations:
	//	// 1) capacity of destination vector is large enough so don't need to allocate new memory
	//	// 2) element assignment may be more efficient than destruction followed by construction
	//	vector temp{ a }; // copy allocator
	//	std::swap(*this, temp); // swap representations
	//	return *this;
	//}

	// optimized version
	vector& operator=(const vector& a)
	{
		if (capacity() < a.size())
		{
			vector temp{ a }; // copy allocator
			std::swap(*this, temp); // swap representations
			return *this;
		}

		if (this == a) // self assignment
			return *this;

		auto sz = size();
		auto asz = a.size();
		vb.alloc = a.vb.alloc;
		if (asz <= sz)
		{
			std::copy(a.begin(), a.begin() + asz, vb.elem);
			for (auto p = vb.elem + asz; p != vb.space; ++p)
				p->~T(); //vb.alloc.deallocate(p);  // destroy surpulus elements
		}
		else
		{
			std::copy(a.begin(), a.begin() + sz, vb.elem);
			// construct extra elements
			std::uninitialized_copy(a.begin() + sz, a.begin() + asz, vb.space);
		}
		vb.space = vb.elem + asz;
		return *this;
	}

	vector& operator=(vector&& a)
	{
		clear();
		std::swap(*this, a);
		return *this;
	}

	~vector()
	{
		destroy_elements();
	}

	size_type size() const
	{
		return vb.space - vb.elem;
	}

	size_type capacity() const
	{
		return vb.last - vb.elem;
	}

	const_iterator begin() const
	{
		return vb.elem;
	}

	const_iterator end() const
	{
		return vb.space;
	}

	// increase capacity to n
	void reserve(size_type n)
	{

	}

	// increase size to n
	void resize(size_type n)
	{

	}

	void clear()
	{

	}

	// add an element to end
	void push_back(const T& e)
	{

	}
};

int main()
{
	vector<int> v(4, 1);
	return 0;
}