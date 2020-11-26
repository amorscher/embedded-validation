/*
 *  Very simple example program
 */

#include "duktape.h"
#include "duk_v1_compat.h"
#include "validate.h"

int main(int argc, char *argv[])
{
    int retval = 1;
    duk_context *ctx = create_heap_default();

    if (duk_safe_call(ctx, init_duktape_context, NULL, 0 /*nargs*/, 1 /*nrets*/) != 0)
    {
        fprintf(stderr, "Failed to initialize: %s\n", duk_safe_to_string(ctx, -1));
        goto cleanup;
    }
    duk_dump_context_stdout(ctx);
    duk_pop(ctx);
    duk_dump_context_stdout(ctx);
    duk_eval_string(ctx, "print('askdhakhdkjsahdksad','dasdadsad','ambrosa'   );print('Ambros');print('Alex');");
    duk_dump_context_stdout(ctx);
    duk_pop(ctx);
    duk_dump_context_stdout(ctx);

    retval = 0;
cleanup:

    if (ctx)
    {
        duk_destroy_heap(ctx);
    }

    return retval;
}