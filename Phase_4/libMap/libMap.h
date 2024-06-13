#ifndef LIBMAP_H
#define LIBMAP_H

#ifdef LIBMAP_EXPORTS
#define LIBMAP_API __declspec(dllexport)
#else
#define LIBMAP_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	// Function declarations
	LIBMAP_API void __cdecl map_func(const char* fileName, const char* data, const char* temp, int numReducers);

#ifdef __cplusplus
}
#endif

#endif // LIBMAP_H
