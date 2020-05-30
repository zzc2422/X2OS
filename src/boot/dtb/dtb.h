#ifndef DTB_H
#define DTB_H

#include <defs.h>

typedef struct {
} dtb_t;

static u32 get_whole_mem_end_n(const dtb_t* dtb_p) {
	return 128 * 1024 * 1024 + 0x80000000;
}

#endif // DTB_H