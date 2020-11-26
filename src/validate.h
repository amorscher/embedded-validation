

#if !defined(VALIDATE)
#define VALIDATE

duk_ret_t read_json_file(duk_context *ctx, char *filename);

duk_ret_t init_duktape_context(duk_context *ctx,void *udata);

void fatal_error_to_console(void *udata, const char *msg);

#define create_heap_default() \
    duk_create_heap(NULL, NULL, NULL, NULL, fatal_error_to_console)

#endif
