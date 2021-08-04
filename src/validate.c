/*
 *  Very simple example program
 */

#include "duktape.h"
#include "duk_v1_compat.h"
#include "validate.h"
#include <stdio.h>
#include <stdlib.h>

void fatal_error_to_console(void *udata, const char *msg)
{
    (void)udata; /* ignored in this case, silence warning */

    /* Note that 'msg' may be NULL. */
    fprintf(stderr, "*** FATAL ERROR: %s\n", (msg ? msg : "no message"));
    fflush(stderr);
    abort();
    return;
}

// duk_context *create_heap_default()
// {
//     duk_context *ctx = duk_create_heap(NULL, NULL, NULL, NULL, fatal_error_to_console);
//     return ctx;
// }

static duk_ret_t native_print(duk_context *ctx)
{
    duk_push_string(ctx, " ");
    duk_dump_context_stdout(ctx);
    duk_insert(ctx, 0);
    duk_dump_context_stdout(ctx);
    duk_join(ctx, duk_get_top(ctx) - 1);
    duk_dump_context_stdout(ctx);
    printf("%s\n", duk_safe_to_string(ctx, -1));
    return 0;
}

static void print_register(duk_context *ctx)
{
    duk_push_c_function(ctx, native_print, DUK_VARARGS);
    duk_put_global_string(ctx, "print");
}

duk_ret_t init_duktape_context(duk_context *ctx, void *udata)
{
    (void)udata;

    print_register(ctx);

    return 0;
}

static duk_ret_t read_file(char **content, char *filename, int* length)
{
    FILE *f = NULL;
    f = fopen(filename, "rb");
    if (!f)
    {
        fprintf(stderr, "failed to open file: %s\n", filename);
        fflush(stderr);
        return -1;
    }

    //read the content
    int len;
    int got;
    if (fseek(f, 0, SEEK_END) < 0)
    {
        return -1;
    }
    len = (int)ftell(f);
    if (fseek(f, 0, SEEK_SET) < 0)
    {
        return -1;
    }
    *content = (char *)malloc(len);
    if (!(*content))
    {
        return -1;
    }
    got = fread((void *)*content, (size_t)1, (size_t)len, f);
    *length = got;

    fclose(f);

    return 0;
}

duk_ret_t read_json_file(duk_context *ctx, char *filename)
{
    char *jsonData = NULL;
    int length = 0;
    //read the file
    int retValue = read_file(&jsonData,filename, &length);
    if (retValue == 0)
    {
        //put the data to the value stack
        duk_push_lstring(ctx, jsonData,length);
        duk_json_decode(ctx, -1);
    }
    //free the data
    free(jsonData);
    jsonData = NULL;

    return retValue;
}

duk_ret_t evaluate_js_file(duk_context *ctx, char *filename)
{
    char *jsCode = NULL;
     int length = 0;
    //read the file
    int retValue = read_file(&jsCode, filename,&length);
    if (retValue == 0)
    {
        int comp_flags = 0;
        //put the data to the value stack
        duk_push_lstring(ctx, jsCode,length);
        duk_push_string(ctx, filename);
         //free the data
        free(jsCode);
        jsCode = NULL;
        //compile the code
        duk_compile(ctx, comp_flags);
        duk_push_global_object(ctx);

        duk_insert(ctx, -2); /* [ ... global func ] */
        duk_put_prop_string(ctx, -2, "_USERCODE");
        duk_pop(ctx);
        duk_eval_string(ctx,"_USERCODE();");
    }
   

    return retValue;
}


static void print_error(duk_context *ctx, FILE *f) {
	if (duk_is_object(ctx, -1) && duk_has_prop_string(ctx, -1, "stack")) {
		/* XXX: print error objects specially */
		/* XXX: pcall the string coercion */
		duk_get_prop_string(ctx, -1, "stack");
		if (duk_is_string(ctx, -1)) {
			fprintf(f, "%s\n", duk_get_string(ctx, -1));
			fflush(f);
			duk_pop_2(ctx);
			return;
		} else {
			duk_pop(ctx);
		}
	}
	duk_to_string(ctx, -1);
	fprintf(f, "%s\n", duk_get_string(ctx, -1));
	fflush(f);
	duk_pop(ctx);
}
