#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <glib-2.0/glib.h>
#include <glib-2.0/glib/gtypes.h>
#include <glib-2.0/glib/ghash.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <JavaScriptCore/JavaScript.h>
#include <neko.h>
#include "javascript.h"
#include "plugin.h"

DEFINE_KIND(k_webview);
DEFINE_KIND(k_websettings);

value webview_init(value window) {

	//if (!val_is_abstract(window) || !val_is_kind(window, k_window))
	if (!val_is_abstract(window))
		neko_error();

	GtkWidget *win;
	win = val_data(window);
	GtkWidget *scrolled;
	GtkWidget *vbox;
	GtkWidget *webview;

	WebKitWebFrame* webframe;
	JSGlobalContextRef js_context;
	JSObjectRef js_global;
	JSStringRef js_function_name;
	JSObjectRef js_set_can_register;
	GtkWidget* button_box;

	vbox = gtk_vbox_new(false, 4);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vbox), scrolled, true, true, 0);

	webview = webkit_web_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled), webview);
	webkit_web_view_load_string(WEBKIT_WEB_VIEW(webview), "hello", "text/html",
			"UTF-8", "");

	/*
	g_signal_connect(webview, "create-plugin-widget",
			G_CALLBACK(web_view_create_plugin_widget_cb), NULL);

	button_box = gtk_hbutton_box_new();
	gtk_box_pack_start(GTK_BOX (vbox), button_box, false, false, 0);
	register_button = gtk_button_new_with_mnemonic("Send _Registration");
	gtk_widget_set_sensitive(register_button, false);
	gtk_box_pack_start(GTK_BOX (button_box), register_button, false, false, 0);

	webframe = webkit_web_view_get_main_frame(WEBKIT_WEB_VIEW (webview));
	js_context = webkit_web_frame_get_global_context(webframe);
	js_global = JSContextGetGlobalObject(js_context);
	js_function_name = JSStringCreateWithUTF8CString("setCanRegister");
	js_set_can_register = JSObjectMakeFunctionWithCallback(js_context,
			js_function_name, set_can_register_cb);
	JSObjectSetProperty(js_context, js_global, js_function_name,
			js_set_can_register, 0, NULL);
	JSStringRelease(js_function_name);
	*/


	//testplugin_init();

	webframe = webkit_web_view_get_main_frame(WEBKIT_WEB_VIEW (webview));
	js_context = webkit_web_frame_get_global_context(webframe);
	js_global = JSContextGetGlobalObject(js_context);

	js_function_name = JSStringCreateWithUTF8CString("js_Webkit_test");
	js_set_can_register = JSObjectMakeFunctionWithCallback(js_context,js_function_name, webkit_js_test_cb);
	JSObjectSetProperty(js_context, js_global, js_function_name, js_set_can_register, 0, NULL);
	JSStringRelease(js_function_name);

	JSStringRef function_js_2_neko;
	function_js_2_neko = JSStringCreateWithUTF8CString("remoting_js_2_neko");
	js_set_can_register = JSObjectMakeFunctionWithCallback(js_context,function_js_2_neko, remoting_js_2_neko);
	JSObjectSetProperty(js_context, js_global, function_js_2_neko, js_set_can_register, 0, NULL);
	JSStringRelease(function_js_2_neko);



	gtk_widget_show_all(win);

	return alloc_abstract(k_webview, webview);
}

/*
 value webiew_close() {
 }
 */

//TODO websettings get/set
// use array ???
static void alloc_websettings_bool(value o, WebKitWebSettings *s, char *key) {
	gboolean* v = NULL;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_bool(v));
}
static void alloc_websettings_string(value o, WebKitWebSettings *s, char *key) {
	gchar *v = NULL;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_string(v));
}
static void alloc_websettings_int(value o, WebKitWebSettings *s, char *key) {
	gint v;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_int(v));
}
static void alloc_websettings_float(value o, WebKitWebSettings *s, char *key) {
	gfloat v;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_float(v));
}
value webview_getwebsettings(value v) {

	WebKitWebSettings * s = webkit_web_view_get_settings(val_data(v));
	value o;
	o = alloc_object(NULL);

	alloc_websettings_bool(o, s, "auto-resize-window");
	alloc_websettings_bool(o, s, "auto-shrink-images");
	alloc_websettings_string(o, s, "cursive-font-family");
	alloc_websettings_string(o, s, "default-encoding");
	alloc_websettings_string(o, s, "default-font-family");
	alloc_websettings_int(o, s, "default-font-size");
	alloc_websettings_int(o, s, "default-monospace-font-size");

	alloc_websettings_bool(o, s, "enable-caret_browsing");
	alloc_websettings_bool(o, s, "enable-default-context-menu");
	alloc_websettings_bool(o, s, "enable-developer-extras");
	alloc_websettings_bool(o, s, "enable-dns-prefetching");
	alloc_websettings_bool(o, s, "enable-dom-paste");
	alloc_websettings_bool(o, s, "enable-file-access-from-file-uris");
	alloc_websettings_bool(o, s, "enable-frame-flattening");
	alloc_websettings_bool(o, s, "enable-fullscreen");
	alloc_websettings_bool(o, s, "enable-html5-database");
	alloc_websettings_bool(o, s, "enable-html5-local-storage");
	alloc_websettings_bool(o, s, "enable-hyperlink-auditing");
	alloc_websettings_bool(o, s, "enable-java-applet");
	alloc_websettings_bool(o, s, "enable-offline-web-application-cache");
	alloc_websettings_bool(o, s, "enable-page_cache");
	alloc_websettings_bool(o, s, "enable-plugins");
	alloc_websettings_bool(o, s, "enable-private-browsing");
	alloc_websettings_bool(o, s, "enable-scripts");
	alloc_websettings_bool(o, s, "enable-site-specific-quirks");
	alloc_websettings_bool(o, s, "enable-spatial-navigation");
	alloc_websettings_bool(o, s, "enable-spell-checking");
	alloc_websettings_bool(o, s, "enable-universal-access-from-file-uris");
	alloc_websettings_bool(o, s, "enable-webgl");
	alloc_websettings_bool(o, s, "enable-xss-auditor");

	alloc_websettings_bool(o, s, "enforce-96-dpi");
	alloc_websettings_string(o, s, "fantasy-font-family");
	alloc_websettings_string(o, s, "html5-local-storage-database-path");
	alloc_websettings_bool(o, s, "javascript-can-access-clipboard");
	alloc_websettings_bool(o, s, "javascript-can-open-windows-automatically");
	alloc_websettings_int(o, s, "minimum-font-size");
	alloc_websettings_int(o, s, "minimum-logical-font-size");
	alloc_websettings_string(o, s, "monospace-font-family");
	alloc_websettings_bool(o, s, "print-backgrounds");
	alloc_websettings_bool(o, s, "resizable-text-areas");
	alloc_websettings_string(o, s, "sans-serif-font-family");
	alloc_websettings_string(o, s, "serif-font-family");
	alloc_websettings_string(o, s, "spell-checking-languages");
	alloc_websettings_bool(o, s, "tab-key-cycles-through-elements");
	alloc_websettings_string(o, s, "user-agent");
	alloc_websettings_string(o, s, "user-stylesheet-uri");
	alloc_websettings_float(o, s, "zoom-step");

	return o;
}
value webview_setwebsettings(value v, value s) {
	//TODO
	//WebKitWebSettings * s = webkit_web_view_get_settings(val_data(s));
	//webkit_web_view_set_settings (WEBKIT_WEB_VIEW(my_webview), s);
	WebKitWebSettings *settings = webkit_web_settings_new();
	//g_object_set (G_OBJECT(s), "enable-scripts", FALSE, NULL);
	webkit_web_view_set_settings(WEBKIT_WEB_VIEW(val_data(v)), settings);
	//value o;
	//o = alloc_object(NULL);
	return val_null;
}

value webview_gettransparent(value v) {
	return alloc_bool(webkit_web_view_get_transparent(val_data(v)));
}
value webview_settransparent(value v, value t) {
	webkit_web_view_set_transparent(val_data(v), val_bool(t));
	return t;
}

value webview_uri(value v) {
	return alloc_string(webkit_web_view_get_uri(val_data(v)));
}

value webview_loadstring(value v, value str) {
	webkit_web_view_load_string(val_data(v), val_string(str), "text/html",
			"UTF-8", "");
	return val_null;
}

value webview_loaduri(value v, value s) {
	printf("URRRRRRRRI:\n");
	webkit_web_view_load_uri(val_data(v), val_string(s));
	return val_null;
}

value webview_reload(value v) {
	webkit_web_view_reload(val_data(v));
	return val_null;
}

value webview_reloadbypasscache(value v) {
	webkit_web_view_reload_bypass_cache(val_data(v));
	return val_null;
}

value webview_undo(value v) {
	webkit_web_view_undo(val_data(v));
	return val_null;
}

value webview_redo(value v) {
	webkit_web_view_redo(val_data(v));
	return val_null;
}

DEFINE_PRIM( webview_init, 1);
DEFINE_PRIM( webview_getwebsettings, 1);
DEFINE_PRIM( webview_setwebsettings, 2);
DEFINE_PRIM( webview_gettransparent, 1);
DEFINE_PRIM( webview_settransparent, 2);
DEFINE_PRIM( webview_uri, 1);

DEFINE_PRIM( webview_loadstring, 2);
DEFINE_PRIM( webview_loaduri, 2);
DEFINE_PRIM( webview_reload, 1);
DEFINE_PRIM( webview_reloadbypasscache, 1);
DEFINE_PRIM( webview_undo, 1);
DEFINE_PRIM( webview_redo, 1);
