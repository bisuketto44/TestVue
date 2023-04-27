// アプリ用アロケータ
/**
 * @brief		TODO
 */

#include <cocos2d.h>
#include "utility/macro.h"
#include "utility/allocator.h"


//========================================================================================
// Override
//========================================================================================
void* operator new(size_t const size);
void* operator new(size_t const size, std::nothrow_t const&) throw();
void* operator new[](size_t const size);
void* operator new[](size_t const size, std::nothrow_t const&) throw();
void operator delete(void* ptr);
void operator delete(void* ptr, std::nothrow_t const&) throw();
void operator delete[](void* ptr);
void operator delete[](void* ptr, std::nothrow_t const&) throw();


/**
 * @brief		TODO
 */
void* allocateStatic(size_t const size)
{
	void* ptr = Allocator::getInstance()->allocate(size);
	return ptr;
}

/**
 * @brief		TODO
 */
void freeStatic(void* ptr)
{
	Allocator::getInstance()->free(ptr);
}

/**
 * @brief		TODO
 */
void* operator new(size_t const size)									{ return allocateStatic(size); }
void* operator new(size_t const size, std::nothrow_t const&) noexcept	{ return allocateStatic(size); }

/**
 * @brief		TODO
 */
void* operator new[](size_t const size)									{ return allocateStatic(size); }
void* operator new[](size_t const size, std::nothrow_t const&) noexcept	{ return allocateStatic(size); }

/**
 * @brief		TODO
 */
void operator delete(void* ptr) noexcept							{ freeStatic(ptr); }
void operator delete(void* ptr, std::nothrow_t const&) noexcept		{ freeStatic(ptr); }
void operator delete[](void* ptr) noexcept							{ freeStatic(ptr); }
void operator delete[](void* ptr, std::nothrow_t const&) noexcept	{ freeStatic(ptr); }


//======================================================================================
