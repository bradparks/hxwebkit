
#include <hxwebkit_javascript.h>
#include <neko.h>

/*
JSValueRef hxwebkit_js_test_cb(JSContextRef js_context, JSObjectRef js_function,
		JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception) {
	JSValueRef js_value = JSValueMakeNull(js_context);
	//printf("CAaaaLLBACK SUCCESSFUL webkit_js_test_c\n");
	return js_value;
}
*/

//////////////////////////

value *callback_storage = NULL;

static value hxwebkit_set_hxr_handler(value f) {
	val_check_function(f, 1);
	if (callback_storage == NULL)
		callback_storage = alloc_root(1);
	*callback_storage = f;
	return val_null;
}
DEFINE_PRIM(hxwebkit_set_hxr_handler, 1);

JSValueRef hxr_js2neko(JSContextRef js_context,
		JSObjectRef js_function, JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception) {
	JSValueRef js_value = JSValueMakeNull(js_context);
	if (argument_count == 1 && JSValueIsString(js_context, js_arguments[0])) {
		size_t len;
		char *cstr;
		JSStringRef jsstr = JSValueToStringCopy(js_context, js_arguments[0], NULL);
		len = JSStringGetMaximumUTF8CStringSize(jsstr);
		cstr = g_new( char, len );
		JSStringGetUTF8CString(jsstr, cstr, len);
		/////value ret = val_call1(*callback_storage, alloc_string(cstr));
	}
	/*
	int i;
	for(i = 0; i < sizeof(js_arguments) / sizeof( JSValueRef); i++){
	}
	*/
	return js_value;
}


static value hxwebkit_javascript_hxr(value t) {
	printf("Recieved from neko: %s\n",val_string(t));
	return val_null;
}
DEFINE_PRIM(hxwebkit_javascript_hxr, 1);
