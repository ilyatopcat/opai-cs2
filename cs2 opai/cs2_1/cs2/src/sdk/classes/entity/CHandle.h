#pragma once

class CHandle {
private:
	void* GetBaseEntity();
public:
	int index;

	template <typename T = void>
	T* Get() {
		return reinterpret_cast<T*>(GetBaseEntity());
	};
};

template <typename T>
class C_NetworkUtlVectorBase
{
public:
	unsigned int m_nSize;
	T* m_pElements;
};
static_assert(sizeof(C_NetworkUtlVectorBase<void*>) == 0x10);