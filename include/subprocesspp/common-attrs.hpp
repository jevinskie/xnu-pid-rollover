#pragma once

#ifndef SUBPROCESSPP_HONOR_INLINE
#define SUBPROCESSPP_HONOR_INLINE 1
#endif

#define SUBPROCESSPP_EXPORT [[gnu::visibility("default")]]
#if SUBPROCESSPP_HONOR_INLINE
#define SUBPROCESSPP_INLINE [[gnu::always_inline]]
#else
#define SUBPROCESSPP_INLINE
#endif
#define SUBPROCESSPP_NOINLINE [[gnu::noinline]]
#define SUBPROCESSPP_LIKELY(cond) __builtin_expect((cond), 1)
#define SUBPROCESSPP_UNLIKELY(cond) __builtin_expect((cond), 0)
#define SUBPROCESSPP_BREAK() __builtin_debugtrap()
#define SUBPROCESSPP_ALIGNED(n) [[gnu::aligned(n)]]
#define SUBPROCESSPP_ASSUME_ALIGNED(ptr, n) __builtin_assume_aligned((ptr), n)
#define SUBPROCESSPP_UNREACHABLE() __builtin_unreachable()
