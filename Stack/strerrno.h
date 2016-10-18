#include "stdio.h"

int errno = 0;

enum err_num

{
#define ERR_NO(CODE, NUM, DESCR) CODE = NUM,
#include "Errno.h"

	LAST_ERR

#undef ERR_NO
};

char* strerror(int i)
{
#define ERR_NO(CODE, NUM, DESCR) if (i == NUM) return DESCR;

#include "Errno.h"

#undef ERR_NO
}

int perror(int local_errno = errno)
{
	printf("%s", strerror(local_errno));
	return 1;
}