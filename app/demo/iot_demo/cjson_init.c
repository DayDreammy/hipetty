/*
 * Copyright (c) 2020 HiHope Community.
 * Description: cJSON init 
 * Author: HiSpark Product Team
 * Create: 2020-5-20
 */

#include <stdint.h>
#include <cJSON.h>
#include <hi_mem.h>
/**
	@berf cjson Allocate dynamic memory
	@param size_t sz:Allocated memory size
*/
static void *cJsonMalloc(size_t sz)
{
    return hi_malloc(0,sz);
}
/**
	@berf cjson free,Free memory, pointer to null
*/
static void cJsonFree(void *p)
{
    hi_free(0,p);
}

void cJsonInit( void)
{
    cJSON_Hooks  hooks;
    hooks.malloc_fn = cJsonMalloc;
    hooks.free_fn = cJsonFree;
    cJSON_InitHooks(&hooks);

    return;
}