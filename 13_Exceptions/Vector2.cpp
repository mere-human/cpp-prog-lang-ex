#include <memory> // allocator

// memory structure for vector
// deals with memory and leaves concerns about objects to vector
template<typename T, typename A = std::allocator<T>>
struct vector_base
{
	A alloc;  // allocator
	T* elem;  // start of allocation
	T* space; // end of element sequence,
                  // start of space allocated for possible expansion
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
		:	alloc { std::move(other.alloc) }, elem{ other.elem },
                        space{ other.space }, last{ other.last }
	{
		other.elem = other.space = other.last = nullptr; // no longer owns memory
	}

	vector_base& operator=(vector_base&& other)
	{
		alloc.deallocate(elem, last - elem);
		elem = space = last = nullptr;
		std::swap(alloc, other.alloc);
		std::swap(elem, other.elem);
		std::swap(space, other.space);
		std::swap(last, other.last);
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

	template<typename In, typename Out>
	void uninitialized_move(In b, In e, Out oo)
	{
		for (; b != e; ++b, ++oo)
		{
			// move construct
			new(static_cast<void*>(&*oo)) T{ std::move(*b) };
			b->~T(); // destroy
		}
	}

	template<typename In>
	void destroy(In b, In e)
	{
		for (; b != e; ++b)
			b->~T();
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
		std::swap(vb, a.vb);
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

	//// increase capacity to n
	//// this is flawed because not all types have default constructor
	//void reserve(size_type n)
	//{
	//	if (n <= capacity()) // never decrease capacity
	//		return;
	//	vector<T, A> v(capacity()); // make a vector with the new capacity
	//	std::copy(elem, elem + size(), v.begin()); // copy elements
	//	std::swap(*this, v); // install new value
	//	// implicitly release old value
	//}

	// increase capacity to n
	void reserve(size_type n)
	{
		if (n <= capacity()) // never decrease capacity
			return;
		vector_base<T, A> b(vb.alloc, n); // get new space
		uninitialized_move(vb.elem, vb.elem + size(), b.elem); // move elements
		b.space = b.elem + size(); // set size
		std::swap(vb, b); // install new base
		// implicitly release old value
	}

	// increase size to n
	void resize(size_type n, const T& val = T{})
	{
		reserve(n);
		if (size() < n)
		{
			// construct new elements
			std::uninitialized_fill(vb.elem + size(), vb.elem + n, val);
		}
		else
		{
			// destroy surplus elements
			destroy(vb.elem + size(), vb.elem + n);
		}
		vb.space = vb.last = vb.elem + n;
	}

	void clear()
	{
		destroy_elements();
	}

	// add an element to end
	// vector remains unchanged if add failed
	void push_back(const T& val)
	{
		const auto sz = size();
		if (capacity() == sz) // no more free space; reallocate
		{
			// grow or start with 8
			// however, mathematically optimal factor is 1.618
			reserve(sz ? sz * 2 : 8);
		}
		vb.alloc.construct(&vb.elem[sz], val); // add val at end
		++vb.space; // increment size
	}
};

int main()
{
	vector<int> v(4, 1);
	v.resize(5);
	v.push_back(2);
	vector<int> v2(2);
	v2 = std::move(v);
	v2.push_back(3);
	return 0;
}
