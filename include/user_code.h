/*
 * user_code.h
 *
 */

#ifndef INC_USER_CODE_H_
#define INC_USER_CODE_H_
#define BUFFER_SIZE 256 // Must Be incremented by a factor of 2. eg.(4,8,16,32,64,..,256)
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


void xStartup_Function(void);
void x2000hz_Function(void);
void x1000hz_Function(void);
void x500hz_Function(void);
void x200hz_Function(void);
void x100hz_Function(void);
void x50hz_Function(void);
void x20hz_Function(void);
void x10hz_Function(void);
void x5hz_Function(void);
void x2hz_Function(void);
void x1hz_Function(void);



#endif /* INC_USER_CODE_H_ */
