#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int64_t malloc_fail_at = -1;
static int64_t calloc_fail_at = -1;
static int64_t realloc_fail_at = -1;
static int64_t reallocarray_fail_at = -1;

void *malloc(size_t size)
{
    static void *(*real_malloc)(size_t);
    static int64_t malloc_counter = 0;
    char *env_malloc_fail_at = NULL;

    // TODO: replace atol() with something more secure
    env_malloc_fail_at = secure_getenv("MALLOC_FAIL_AT");
    if (env_malloc_fail_at)
        malloc_fail_at = atol(env_malloc_fail_at);

    if(!real_malloc)
        real_malloc = (typeof(real_malloc)) dlsym(RTLD_NEXT, "malloc");

    if(malloc_fail_at >= 0 && malloc_counter++ >= malloc_fail_at)
        return real_malloc(-1);

    return real_malloc(size);
}

void *calloc(size_t nmemb, size_t size)
{
    static void *(*real_calloc)(size_t,size_t);
    static int64_t calloc_counter = 0;
    char *env_calloc_fail_at = NULL;

    // TODO: replace atol() with something more secure
    env_calloc_fail_at = secure_getenv("CALLOC_FAIL_AT");
    if (env_calloc_fail_at)
        calloc_fail_at = atol(env_calloc_fail_at);

    if(!real_calloc)
        real_calloc = (typeof(real_calloc)) dlsym(RTLD_NEXT, "calloc");

    if(calloc_fail_at >= 0 && calloc_counter++ >= calloc_fail_at)
        return real_calloc(nmemb, -1);

    return real_calloc(nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    static void *(*real_realloc)(void*,size_t);
    static int64_t realloc_counter = 0;
    char *env_realloc_fail_at = NULL;

    // TODO: replace atol() with something more secure
    env_realloc_fail_at = secure_getenv("REALLOC_FAIL_AT");
    if (env_realloc_fail_at)
        realloc_fail_at = atol(env_realloc_fail_at);

    if(!real_realloc)
        real_realloc = (typeof(real_realloc)) dlsym(RTLD_NEXT, "realloc");

    if(realloc_fail_at >= 0 && realloc_counter++ >= realloc_fail_at)
        return real_realloc(ptr, -1);

    return real_realloc(ptr, size);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    static void *(*real_reallocarray)(void*,size_t,size_t);
    static int64_t reallocarray_counter = 0;
    char *env_reallocarray_fail_at = NULL;

    // TODO: replace atol() with something more secure
    env_reallocarray_fail_at = secure_getenv("REALLOCARRAY_FAIL_AT");
    if (env_reallocarray_fail_at)
        reallocarray_fail_at = atol(env_reallocarray_fail_at);

    if(!real_reallocarray)
        real_reallocarray = (typeof(real_reallocarray)) dlsym(RTLD_NEXT, "reallocarray");

    if(reallocarray_fail_at >= 0 && reallocarray_counter++ >= reallocarray_fail_at)
        return real_reallocarray(ptr, nmemb, -1);

    return real_reallocarray(ptr, nmemb, size);
}
