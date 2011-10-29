#include <javascript.h>

JSValueRef hxwebkit_js_test_cb(JSContextRef js_context, JSObjectRef js_function,
		JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception) {
	JSValueRef js_value = JSValueMakeNull(js_context);
	//printf("CAaaaLLBACK SUCCESSFUL webkit_js_test_c\n");
	return js_value;
}


JSValueRef hxwebkit_remoting_js_2_neko(JSContextRef js_context, JSObjectRef js_function,
		JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception) {
	JSValueRef js_value = JSValueMakeNull(js_context);
	//printf("remoting_js_2_neko CAaagggggggggggggggggggggggggaLLBACK SUCCESSFUL webkit_js_test_c\n",0);
	return js_value;
}


//////////

	/*
value *function_storage_remoting_js_2_neko = NULL;

static value set_handler_remoting_js_2_neko( value f ) {
	val_check_function(f,1); // checks that f has 1 argument
	   if( function_storage == NULL )
	       function_storage = alloc_root(1);
	   *function_storage = f;
	   return val_null;
}
	   */




//DEFINE_PRIM( js_createJSONString, 2);

