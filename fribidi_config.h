
#define FRIBIDI_PACKAGE "fribidi"

#define FRIBIDI_VERSION "0.10.5"
#define FRIBIDI_MAJOR_VERSION 0
#define FRIBIDI_MINOR_VERSION 10
#define FRIBIDI_MICRO_VERSION 5
#define FRIBIDI_INTERFACE_VERSION 2

#if 0 /* FRIBIDI_NO_CHARSETS */
#define FRIBIDI_NO_CHARSETS 1
#else /* NOT FRIBIDI_NO_CHARSETS */
#undef FRIBIDI_NO_CHARSETS
#endif /* FRIBIDI_NO_CHARSETS */

#define TOSTR(x) #x

#ifdef WIN32

#ifdef FRIBIDI_EXPORTS
#define FRIBIDI_API __declspec(dllexport)
#else
#define FRIBIDI_API __declspec(dllimport)
#endif

#define snprintf _snprintf

#else /* NOT WIN32 */

#define FRIBIDI_API

#endif /* WIN32 */

/* __BEGIN_DECLS should be used at the beginning of your declarations,
 * so that C++ compilers don't mangle their names.  Use __END_DECLS at
 * the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else /* NOT __cplusplus */
#define __BEGIN_DECLS		/* empty */
#define __END_DECLS		/* empty */
#endif /* __cplusplus */

#define FRIBIDI_TRUE    1
#define FRIBIDI_FALSE   0

#ifndef TRUE
#define TRUE FRIBIDI_TRUE
#endif /* TRUE */
#ifndef FALSE
#define FALSE FRIBIDI_FALSE
#endif /* FALSE */
