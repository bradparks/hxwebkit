#ifndef HXWEBKIT_JAVASCRIPT_H_
#define HXWEBKIT_JAVASCRIPT_H_

#include <hxwebkit.h>

/*
JSValueRef hxwebkit_js_test_cb(JSContextRef js_context, JSObjectRef js_function,
		JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception);
*/

/**
 * Application->System haXe remoting
 */
JSValueRef hxr_js2neko(JSContextRef js_context,
		JSObjectRef js_function, JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception);

#endif /* HXWEBKIT_JAVASCRIPT_H_ */
