#pragma once

#ifndef XNU_NOLIBC_HONOR_INLINE
#define XNU_NOLIBC_HONOR_INLINE 1
#endif

#define XNU_NOLIBC_EXPORT [[gnu::visibility("default")]]
#if XNU_NOLIBC_HONOR_INLINE
#define XNU_NOLIBC_INLINE [[gnu::always_inline]]
#else
#define XNU_NOLIBC_INLINE
#endif
#define XNU_NOLIBC_NOINLINE [[gnu::noinline]]
#define XNU_NOLIBC_LIKELY(cond) __builtin_expect((cond), 1)
#define XNU_NOLIBC_UNLIKELY(cond) __builtin_expect((cond), 0)
#define XNU_NOLIBC_BREAK() __builtin_debugtrap()
#define XNU_NOLIBC_ALIGNED(n) [[gnu::aligned(n)]]
#define XNU_NOLIBC_ASSUME_ALIGNED(ptr, n) __builtin_assume_aligned((ptr), n)
#define XNU_NOLIBC_UNREACHABLE() __builtin_unreachable()
