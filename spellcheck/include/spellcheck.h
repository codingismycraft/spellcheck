/* 
 * File:   wdist.h
 * Author: john
 *
 * Created on June 30, 2022, 8:35 PM
 */

#ifndef WDIST_H
#define WDIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_WORD_LENGTH 25
#define TOLERANCE 2
#define MAX_MATCHES 10

typedef const char* CONST_STR_PTR;

int word_distance(CONST_STR_PTR psz1, CONST_STR_PTR psz2);

int find_matches(CONST_STR_PTR psz, char matches[MAX_MATCHES][MAX_WORD_LENGTH]);

int set_dict(CONST_STR_PTR psz);

#ifdef __cplusplus
}
#endif


#endif /* WDIST_H */

