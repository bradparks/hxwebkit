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

/*
 static GtkWidget* register_button = NULL;

 static void cb_setButtonColor(GtkWidget* button, gpointer userdata) {
 GtkWidget* webview = GTK_WIDGET (userdata);
 GdkColor color;
 gchar* script;
 gtk_color_button_get_color(GTK_COLOR_BUTTON (button), &color);
 script = g_strdup_printf("document.body.style.backgroundColor = \"#%x%x%x\";", color.red / 256, color.green / 256, color.blue / 256);
 script = g_strdup_printf("document.body.style.backgroundColor=\"#ff0000\";");
 webkit_web_view_execute_script(WEBKIT_WEB_VIEW (webview), script);
 }

 static GtkWidget* web_view_create_plugin_widget_cb(GtkWidget* webview,
 const gchar* mime_type, const gchar* uri, GHashTable* param,
 gpointer userdata) {
 if (g_str_equal(mime_type, "application/x-gtk-color-button")) {
 GtkWidget* btn = gtk_color_button_new();
 GdkColor color;
 gdk_color_parse("#3A47EF", &color);
 gtk_color_button_set_color(GTK_COLOR_BUTTON (btn), &color);
 g_signal_connect(btn, "color-set", G_CALLBACK(cb_setButtonColor), webview);
 return btn;
 }
 return NULL;
 }

 static JSValueRef set_can_register_cb(JSContextRef js_context,
 JSObjectRef js_function, JSObjectRef js_this, size_t argument_count,
 const JSValueRef js_arguments[], JSValueRef* js_exception) {
 JSValueRef js_value = JSValueMakeNull(js_context);
 if (argument_count == 1
 && JSValueGetType(js_context, js_arguments[0]) == kJSTypeBoolean) {
 bool sensitive = JSValueToBoolean(js_context, js_arguments[0]);
 gtk_widget_set_sensitive(register_button, sensitive == true);
 }
 return js_value;
 }
 */

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

	gtk_widget_show_all(win);

	return alloc_abstract(k_webview, webview);
}

/*
 value webiew_close() {
 }
 */



static void alloc_websettings_bool(value o, WebKitWebSettings *s, char *key) {
	gboolean* b = NULL;
	g_object_get(s, key, &b, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_bool(b));
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

value webview_getwebsettings(value v) {
	WebKitWebSettings * s = webkit_web_view_get_settings(val_data(v));
	//TODO........
	value o;
	o = alloc_object(NULL);
	alloc_websettings_bool(o, s, "auto-resize-window");
	alloc_websettings_bool(o, s, "auto-shrink-images");
	alloc_websettings_string(o, s, "cursive-font-family");
	alloc_websettings_string(o, s, "default-encoding");
	alloc_websettings_string(o, s, "default-font-family");
	alloc_websettings_int(o, s, "default-font-size");
	alloc_websettings_int(o, s, "default-monospace-font-size");

	alloc_websettings_bool(o, s, "enable-scripts");


	return o;
}
value webview_setwebsettings(value v, value s) {

	//WebKitWebSettings * s = webkit_web_view_get_settings(val_data(s));
	//webkit_web_view_set_settings (WEBKIT_WEB_VIEW(my_webview), s);
	WebKitWebSettings *settings = webkit_web_settings_new();
	//g_object_set (G_OBJECT(s), "enable-scripts", FALSE, NULL);

	webkit_web_view_set_settings (WEBKIT_WEB_VIEW(val_data(v)), settings);

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

value webview_loadstring(value v, value str) {
	webkit_web_view_load_string(val_data(v), val_string(str), "text/html",
			"UTF-8", "");
	return val_null;
}

value webview_loaduri(value v, value s) {
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
DEFINE_PRIM( webview_loadstring, 2);
DEFINE_PRIM( webview_loaduri, 2);
DEFINE_PRIM( webview_reload, 1);
DEFINE_PRIM( webview_reloadbypasscache, 1);
DEFINE_PRIM( webview_undo, 1);
DEFINE_PRIM( webview_redo, 1);
