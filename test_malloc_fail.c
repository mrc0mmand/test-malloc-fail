#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static uint64_t malloc_fail_at = 0;

void *malloc(size_t size)
{
    static void *(*real_malloc)(size_t);
    static uint64_t malloc_counter = 0;
    char *env_malloc_fail_at = NULL;

    // TODO: replace atol() with something more secure
    env_malloc_fail_at = secure_getenv("MALLOC_FAIL_AT");
    if (env_malloc_fail_at)
        malloc_fail_at = atol(env_malloc_fail_at);

    if(!real_malloc)
        real_malloc = (typeof(real_malloc)) dlsym(RTLD_NEXT, "malloc");

    if(malloc_counter++ >= malloc_fail_at)
        return real_malloc(-1);

    return real_malloc(size);
}
