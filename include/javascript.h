#ifndef JAVASCRIPT_H_
#define JAVASCRIPT_H_

#include <JavaScriptCore/JavaScript.h>

JSValueRef webkit_js_test_cb(JSContextRef js_context, JSObjectRef js_function,
		JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception);

JSValueRef remoting_js_2_neko(JSContextRef js_context, JSObjectRef js_function,
		JSObjectRef js_this, size_t argument_count,
		const JSValueRef js_arguments[], JSValueRef* js_exception);


#endif /* JAVASCRIPT_H_ */
