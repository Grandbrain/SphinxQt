#ifndef __SPHINX_CONFIG_H__
#define __SPHINX_CONFIG_H__

#if defined (__ANDROID__)

#define SIZEOF_LONG 8
#define HAVE_LONG_LONG 1
#define SIZEOF_LONG_LONG 8

#elif defined (_WIN32_WCE)

#define SIZEOF_LONG 4
#define EXEEXT ".exe"

#else

#define SIZEOF_LONG 4

#endif

#endif /* __SPHINX_CONFIG_H__ */