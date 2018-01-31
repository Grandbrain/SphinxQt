#ifndef __ASSERT_H__
#define __ASSERT_H__

#if defined (_WIN32_WCE)
#define assert(x) if (!(x)) (*(int *)0=0);
#else

#include <assert.h>

#endif


#endif /* __ASSERT_H__ */