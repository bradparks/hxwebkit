#include <stdlib.h>
#include <string.h>

/**
 * Usage: replace_str("Hello, world!", "world", "Miami");
 */
char * str_replace(char const * const original, char const * const pattern,
		char const * const replacement) {

	size_t const replen = strlen(replacement);
	size_t const patlen = strlen(pattern);
	size_t const orilen = strlen(original);

	size_t patcnt = 0;
	const char * oriptr;
	const char * patloc;

	// find how many times the pattern occurs in the original string
	for (oriptr = original; (patloc = strstr(oriptr, pattern));
			oriptr = patloc + patlen) {
		patcnt++;
	}

	{
		// allocate memory for the new string
		size_t const retlen = orilen + patcnt * (replen - patlen);
		char * const returned = (char *) malloc(sizeof(char) * (retlen + 1));
		if (returned != NULL) {
			// copy the original string, replacing all the instances of the pattern
			char * retptr = returned;
			for (oriptr = original; (patloc = strstr(oriptr, pattern));
					oriptr = patloc + patlen) {
				size_t const skplen = patloc - oriptr;
				strncpy(retptr, oriptr, skplen); // copy the section until the occurence of the pattern
				retptr += skplen;
				strncpy(retptr, replacement, replen); // copy the replacement
				retptr += replen;
			}
			strcpy(retptr, oriptr); // copy the rest of the string
		}
		return returned;
	}
}
