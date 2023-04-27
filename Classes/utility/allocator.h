// アプリ用アロケータ
// TODO

#pragma once


//========================================================================================
// Override
//========================================================================================
// TODO
void* operator new( size_t const size);
// TODO
void* operator new( size_t const size, std::nothrow_t const&) throw();

// TODO
void* operator new[]( size_t const size);
// TODO
void* operator new[]( size_t const size, std::nothrow_t const&) throw();

// TODO
void operator delete( void* ptr);
void operator delete(void* ptr, std::nothrow_t const&) throw();
// TODO
void operator delete[]( void* ptr);
void operator delete[](void* ptr, std::nothrow_t const&) throw();


// TODO
#if 0
//void* malloc(size_t size);
//void free(void* ptr);

_CRTIMP
 _CRTNOALIAS
   void
    __cdecl
     free(_Pre_maybenull_ _Post_invalid_ void * _Memory);

_Check_return_
 _Ret_maybenull_
  _Post_writable_byte_size_(_Size)
   _CRTIMP
    _CRT_JIT_INTRINSIC
     _CRTNOALIAS
      _CRTRESTRICT
        void*
         __cdecl
          malloc(_In_ _CRT_GUARDOVERFLOW size_t _Size);
#endif

//======================================================================================
