#include "intrusive_ptr.h"
#include <iostream>

class TDoc: public TRefCounter<TDoc> {};

int main() {
	TIntrusivePtr<TDoc> ptr = nullptr;
	ptr = MakeIntrusive<TDoc>();
	std::cout << (ptr.RefCount() == 1) << std::endl;
	TIntrusivePtr<TDoc> ptr2 = ptr;
	std::cout << (ptr.RefCount() == 2) << std::endl;
	std::cout << (ptr == ptr2) << std::endl;
	TIntrusivePtr<TDoc> ptr3 = MakeIntrusive<TDoc>();
	std::cout << (ptr != ptr3) << std::endl;
	ptr3.Reset(ptr2);
	std::cout << ((ptr.RefCount() == ptr3.RefCount()) && (ptr3.RefCount() == 3)) << std::endl;
	ptr3.Reset();
	std::cout << ((ptr.RefCount() == ptr2.RefCount()) &&  (ptr2.RefCount() == 2)) << std::endl;
	ptr3.Reset(std::move(ptr2));
	std::cout << ((ptr.RefCount() == ptr3.RefCount()) && (ptr3.RefCount() == 2)) << std::endl;
	static_assert(sizeof(TDoc*) == sizeof(ptr));
}