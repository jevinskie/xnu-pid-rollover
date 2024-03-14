#pragma once

#ifndef FILEPERM_HONOR_INLINE
#define FILEPERM_HONOR_INLINE 1
#endif

#define FILEPERM_EXPORT [[gnu::visibility("default")]]
#if FILEPERM_HONOR_INLINE
#define FILEPERM_INLINE [[gnu::always_inline]]
#else
#define FILEPERM_INLINE
#endif
#define FILEPERM_NOINLINE [[gnu::noinline]]
#define FILEPERM_LIKELY(cond) __builtin_expect((cond), 1)
#define FILEPERM_UNLIKELY(cond) __builtin_expect((cond), 0)
#define FILEPERM_BREAK() __builtin_debugtrap()
#define FILEPERM_ALIGNED(n) [[gnu::aligned(n)]]
#define FILEPERM_ASSUME_ALIGNED(ptr, n) __builtin_assume_aligned((ptr), n)
#define FILEPERM_UNREACHABLE() __builtin_unreachable()
