#include <stdio.h>
#include <glib-2.0/glib.h>
#include <glib-2.0/glib/gtypes.h>
#include <glib-2.0/glib/ghash.h>
#include <hxwebkit.h>
#include <hxwebkit_webview.h>
#include <hxwebkit_util.h>
#include <hxwebkit_javascript.h>
#include <hxwebkit_plugin.h>

DEFINE_KIND(k_webview);
DEFINE_KIND(k_websettings);

#define is_notification(n) ( val_is_abstract(n) && val_is_kind(n,k_notification) )

WebKitWebSettings *_websettings;

static void destroy(GtkWidget *widget, gpointer data) {
	//gtk_main_quit();
	printf("DESTROY\n");
}

value hxwebkit_webview_init(value window) {

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
//	JSStringRef js_function_name;
	JSObjectRef js_set_can_register;
//	GtkWidget* button_box;

	vbox = gtk_vbox_new(false, 4);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vbox), scrolled, true, true, 0);

	webview = webkit_web_view_new();
	gtk_container_add(GTK_CONTAINER(scrolled), webview);
	//webkit_web_view_load_string(WEBKIT_WEB_VIEW(webview), "hello", "text/html","UTF-8", "");

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

	g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(destroy), NULL);

	//testplugin_init();
	webframe = webkit_web_view_get_main_frame(WEBKIT_WEB_VIEW (webview));
	js_context = webkit_web_frame_get_global_context(webframe);
	js_global = JSContextGetGlobalObject(js_context);

	/*
	 js_function_name = JSStringCreateWithUTF8CString("js_Webkit_test");
	 js_set_can_register = JSObjectMakeFunctionWithCallback(js_context,
	 js_function_name, hxwebkit_js_test_cb);
	 JSObjectSetProperty(js_context, js_global, js_function_name,
	 js_set_can_register, 0, NULL);
	 JSStringRelease(js_function_name);
	 */

	JSStringRef function_js_2_neko;
	function_js_2_neko = JSStringCreateWithUTF8CString("remoting_js2neko");
	js_set_can_register = JSObjectMakeFunctionWithCallback(js_context,
			function_js_2_neko, hxr_js2neko);
	JSObjectSetProperty(js_context, js_global, function_js_2_neko,
			js_set_can_register, 0, NULL);
	JSStringRelease(function_js_2_neko);

	gtk_widget_show_all(win);

	return alloc_abstract(k_webview, webview);
}

value hxwebkit_webview_can_copy_clipboard(value v) {
	return alloc_bool( webkit_web_view_can_copy_clipboard( val_data(v) ) );
}
value hxwebkit_webview_can_cut_clipboard(value v) {
	return alloc_bool( webkit_web_view_can_cut_clipboard( val_data(v) ) );
}
value hxwebkit_webview_can_go_back(value v) {
	return alloc_bool( webkit_web_view_can_go_back( val_data(v) ) );
}
value hxwebkit_webview_can_go_back_or_foward(value v, value steps) {
	return alloc_bool( webkit_web_view_can_go_back_or_forward( val_data(v), val_int(steps) ) );
}
value hxwebkit_webview_can_go_foward(value v) {
	return alloc_bool( webkit_web_view_can_go_forward( val_data(v) ) );
}
value hxwebkit_webview_can_paste_clipboard(value v) {
	return alloc_bool( webkit_web_view_can_paste_clipboard( val_data(v) ) );
}
value hxwebkit_webview_can_go_redo(value v) {
	return alloc_bool( webkit_web_view_can_redo( val_data(v) ) );
}
value hxwebkit_webview_can_show_mimetype(value v, value mimetype) {
	return alloc_bool( webkit_web_view_can_show_mime_type( val_data(v), val_string( mimetype ) ) );
}
value hxwebkit_webview_can_go_undo(value v) {
	return alloc_bool( webkit_web_view_can_undo( val_data(v) ) );
}

value hxwebkit_webview_copy_clipboard(value v) {
	webkit_web_view_copy_clipboard(val_data(v));
	return val_null;
}
value hxwebkit_webview_cut_clipboard(value v) {
	webkit_web_view_copy_clipboard(val_data(v));
	return val_null;
}
value hxwebkit_webview_delete_selection(value v) {
	webkit_web_view_delete_selection(val_data(v));
	return val_null;
}
value hxwebkit_webview_execute_script(value v, value script) {
	webkit_web_view_execute_script(val_data(v), val_string(script));
	return val_null;
}

value hxwebkit_webview_get_back_forward_list(value v) {
	//TODO
	//webkit_web_view_get_back_forward_list(val_data(v));
	return val_null;
}
value hxwebkit_webview_get_copy_target_list(value v) {
	//TODO
	/*
	int t0 = WEBKIT_WEB_VIEW_TARGET_INFO_HTML;
	int t1 = WEBKIT_WEB_VIEW_TARGET_INFO_TEXT;
	printf("IIIIIIIIII %i\n",t0);
	printf("IIIIIIIIII %i\n",t1);
*/
	GtkTargetList *list = webkit_web_view_get_copy_target_list(val_data(v));
	GList *tmp;
	GList *l = list->list;
	tmp = l;
	WebKitWebViewTargetInfo *element;
	while (tmp) {
		element = tmp->data;
		//printf ("%d\n", *element);
		int i = *element;
		printf ("%i\n", i);
		tmp = g_list_next (tmp);
	}
	/*
	int i = 0;
	GList *l;
	for (l=list->list; l; l=l->next, i++) {
		value v = alloc_string( l->data );
		val_print(v);
		//char *s = (char *)l->data;
		//printf("###################################%s\n", s );
	}
	*/
	return val_null;
}
value hxwebkit_webview_get_custom_encoding(value v) {
	return alloc_string(webkit_web_view_get_custom_encoding(val_data(v)));
}
value hxwebkit_webview_get_dom_document(value v) {
	//TODO
	//WebKitDOMDocument *doc = webkit_web_view_get_dom_document(val_data(v));
	//gchar* title = webkit_dom_document_get_title(doc);
	//webkit_dom_document_get_type();
	//return o;
	return val_null;
}
value hxwebkit_webview_get_editable(value v) {
	return alloc_bool( webkit_web_view_get_editable(val_data(v)) );
}
value hxwebkit_webview_get_encoding(value v) {
	return alloc_string(webkit_web_view_get_encoding(val_data(v)));
}
value hxwebkit_webview_get_focused_frame(value v) {
	//TODO
	return val_null;
	//return alloc_bool( webkit_web_view_get_focused_frame(val_data(v)) );
}
value hxwebkit_webview_get_full_content_zoom(value v) {
	return alloc_bool( webkit_web_view_get_full_content_zoom(val_data(v)) );
}
value hxwebkit_webview_get_hit_test_result(value v) {
	//TODO
	return val_null;
	//return alloc_bool( webkit_web_view_get_full_content_zoom(val_data(v)) );
}
value hxwebkit_webview_get_icon_uri(value v) {
	return alloc_string(webkit_web_view_get_icon_uri(val_data(v)));
}
value hxwebkit_webview_get_inspector(value v) {
	//TODO
	return val_null;
}
value hxwebkit_webview_get_load_status(value v) {
	int i = webkit_web_view_get_load_status(val_data(v));
	return alloc_int(i);
}
value hxwebkit_webview_get_main_frame(value v) {
	//TODO
	return val_null;
}
value hxwebkit_webview_get_paste_target_list(value v) {
	//TODO
	return val_null;
}
value hxwebkit_webview_get_progress(value v) {
	return alloc_float(webkit_web_view_get_progress(val_data(v)));
}
static void alloc_field_bool(value o, WebKitWebSettings *s, char *key) {
	gboolean* v = NULL;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_bool(v));
}
static void alloc_field_string(value o, WebKitWebSettings *s, char *key) {
	gchar *v = NULL;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_string(v));
}
static void alloc_field_int(value o, WebKitWebSettings *s, char *key) {
	gint v;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_int(v));
}
static void alloc_field_float(value o, WebKitWebSettings *s, char *key) {
	gfloat v;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_float(v));
}
value hxwebkit_webview_get_settings(value v) {
	WebKitWebSettings * s = webkit_web_view_get_settings(val_data(v));
	value o = alloc_object(NULL);
	alloc_field_bool(o, s, "auto-resize-window");
	alloc_field_bool(o, s, "auto-shrink-images");
	alloc_field_string(o, s, "cursive-font-family");
	alloc_field_string(o, s, "default-encoding");
	alloc_field_string(o, s, "default-font-family");
	alloc_field_int(o, s, "default-font-size");
	alloc_field_int(o, s, "default-monospace-font-size");
	alloc_field_bool(o, s, "enable-caret_browsing");
	alloc_field_bool(o, s, "enable-default-context-menu");
	alloc_field_bool(o, s, "enable-developer-extras");
	alloc_field_bool(o, s, "enable-dns-prefetching");
	alloc_field_bool(o, s, "enable-dom-paste");
	alloc_field_bool(o, s, "enable-file-access-from-file-uris");
	alloc_field_bool(o, s, "enable-frame-flattening");
	alloc_field_bool(o, s, "enable-fullscreen");
	alloc_field_bool(o, s, "enable-html5-database");
	alloc_field_bool(o, s, "enable-html5-local-storage");
	alloc_field_bool(o, s, "enable-hyperlink-auditing");
	alloc_field_bool(o, s, "enable-java-applet");
	alloc_field_bool(o, s, "enable-offline-web-application-cache");
	alloc_field_bool(o, s, "enable-page_cache");
	alloc_field_bool(o, s, "enable-plugins");
	alloc_field_bool(o, s, "enable-private-browsing");
	alloc_field_bool(o, s, "enable-scripts");
	alloc_field_bool(o, s, "enable-site-specific-quirks");
	alloc_field_bool(o, s, "enable-spatial-navigation");
	alloc_field_bool(o, s, "enable-spell-checking");
	alloc_field_bool(o, s, "enable-universal-access-from-file-uris");
	//	alloc_field_bool(o, s, "enable-webgl");
	alloc_field_bool(o, s, "enable-xss-auditor");
	alloc_field_bool(o, s, "enforce-96-dpi");
	alloc_field_string(o, s, "fantasy-font-family");
	//	alloc_field_string(o, s, "html5-local-storage-database-path");
	alloc_field_bool(o, s, "javascript-can-access-clipboard");
	alloc_field_bool(o, s, "javascript-can-open-windows-automatically");
	alloc_field_int(o, s, "minimum-font-size");
	alloc_field_int(o, s, "minimum-logical-font-size");
	alloc_field_string(o, s, "monospace-font-family");
	alloc_field_bool(o, s, "print-backgrounds");
	alloc_field_bool(o, s, "resizable-text-areas");
	alloc_field_string(o, s, "sans-serif-font-family");
	alloc_field_string(o, s, "serif-font-family");
	alloc_field_string(o, s, "spell-checking-languages");
	alloc_field_bool(o, s, "tab-key-cycles-through-elements");
	alloc_field_string(o, s, "user-agent");
	alloc_field_string(o, s, "user-stylesheet-uri");
	alloc_field_float(o, s, "zoom-step");
	return o;
}
value hxwebkit_webview_get_title(value v) {
	return alloc_string(webkit_web_view_get_title(val_data(v)));
}
value hxwebkit_webview_get_transparent(value v) {
	return alloc_bool(webkit_web_view_get_transparent(val_data(v)));
}
value hxwebkit_webview_get_uri(value v) {
	const gchar * uri = webkit_web_view_get_uri(val_data(v));
	if( uri == NULL )
		return val_null;
	return alloc_string(uri);
}
value hxwebkit_webview_get_view_mode(value v) {
	int i = webkit_web_view_get_view_mode(val_data(v));
	return alloc_int(i);
}
value hxwebkit_webview_get_view_source_mode(value v) {
	return alloc_bool(webkit_web_view_get_view_source_mode(val_data(v)));
}

//TODO not again! (see get_settings)
static void alloc_field_viewport_bool(value o, WebKitViewportAttributes *s, char *key) {
	gboolean* v = NULL;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_bool(v));
}
static void alloc_field_viewport_string(value o, WebKitViewportAttributes *s, char *key) {
	gchar *v = NULL;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_string(v));
}
static void alloc_field_viewport_int(value o, WebKitViewportAttributes *s, char *key) {
	gint v;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_int(v));
}
static void alloc_field_viewport_float(value o, WebKitViewportAttributes *s, char *key) {
	gfloat v;
	g_object_get(s, key, &v, NULL);
	alloc_field(o, val_id(str_replace(key, "-", "_")), alloc_float(v));
}
value hxwebkit_webview_get_viewport_attributes(value v) {
	//TODO
	WebKitViewportAttributes * s = webkit_web_view_get_viewport_attributes(val_data(v));
	value o = alloc_object(NULL);
	alloc_field_viewport_int(o, s, "available-height");
	alloc_field_viewport_int(o, s, "available-width");
	alloc_field_viewport_int(o, s, "desktop-width");
	alloc_field_viewport_int(o, s, "device-dpi");
	alloc_field_viewport_int(o, s, "device-height");
	alloc_field_viewport_float(o, s, "device-pixel-ratio");
	alloc_field_viewport_int(o, s, "device-width");
	alloc_field_viewport_int(o, s, "height");
	alloc_field_viewport_float(o, s, "initial-scale-factor");
	alloc_field_viewport_float(o, s, "maximum-scale-factor");
	alloc_field_viewport_float(o, s, "minimum-scale-factor");
	alloc_field_viewport_bool(o, s, "user-scalable");
	alloc_field_viewport_bool(o, s, "valid");
	alloc_field_viewport_int(o, s, "width");
	return o;
}
value hxwebkit_webview_get_zoom_level(value v) {
	return alloc_float(webkit_web_view_get_zoom_level(val_data(v)));
}


value hxwebkit_webview_go_back(value v) {
	webkit_web_view_go_back(val_data(v));
	return val_null;
}
value hxwebkit_webview_go_back_or_forward(value v, value steps) {
	webkit_web_view_go_back_or_forward(val_data(v), val_int(steps));
	return val_null;
}
value hxwebkit_webview_go_forward(value v) {
	webkit_web_view_go_forward(val_data(v));
	return val_null;
}
value hxwebkit_webview_go_to_back_forward_item(value v, value item) {
	//TODO
	return val_null;
}
value hxwebkit_webview_has_selection(value v) {
	return alloc_bool(webkit_web_view_has_selection(val_data(v)));
}
value hxwebkit_webview_load_html_string(value v, value content, value base_uri) {
	webkit_web_view_load_html_string(val_data(v), val_string(content),
			val_string(base_uri));
	return val_null;
}
value hxwebkit_webview_load_request(value v, value request) {
	//TODO
	return val_null;
}
value hxwebkit_webview_load_string(value v, value content, value mime_type,
		value encoding, value base_uri) {
	gchar *_mime_type, *_encoding, *_base_uri;
	if (val_is_null( mime_type ))
		_mime_type = NULL;
	else
		_mime_type = val_string(mime_type);
	if (val_is_null( encoding ))
		_encoding = NULL;
	else
		_encoding = val_string(encoding);
	if (val_is_null( base_uri ))
		_base_uri = NULL;
	else
		_base_uri = val_string(base_uri);
	webkit_web_view_load_string(val_data(v), val_string(content), _mime_type,
			_encoding, _base_uri);
	return val_null;
}
value hxwebkit_webview_load_uri(value v, value s) {
	webkit_web_view_load_uri(val_data(v), val_string(s));
	return val_null;
}
value hxwebkit_webview_mark_text_matches(value v, value string,
		value case_sensitive, value limit) {
	return alloc_int( webkit_web_view_mark_text_matches(val_data(v), val_string(string), val_bool(case_sensitive), val_int(limit) ) );
}
value hxwebkit_webview_move_cursor(value v, value step, value count) {
	//TODO
	//webkit_web_view_move_cursor(val_data(v), val_string(step), val_bool(count) );
	return val_null;
}
value hxwebkit_webview_paste_clipboard(value v, value step, value count) {
	webkit_web_view_paste_clipboard(val_data(v));
	return val_null;
}
value hxwebkit_webview_redo(value v) {
	webkit_web_view_redo(val_data(v));
	return val_null;
}
value hxwebkit_webview_reload(value v) {
	webkit_web_view_reload(val_data(v));
	return val_null;
}
value hxwebkit_webview_reload_bypass_cache(value v) {
	webkit_web_view_reload_bypass_cache(val_data(v));
	return val_null;
}
value hxwebkit_webview_search_text(value v, value s, value c, value f, value w) {
	return alloc_bool( webkit_web_view_search_text(val_data(v),val_string(s),val_bool(c),val_int(f),val_int(w)) );
}
value hxwebkit_webview_select_all(value v) {
	webkit_web_view_select_all(val_data(v));
	return val_null;
}

value hxwebkit_webview_set_custom_encoding(value v, value value) {
	webkit_web_view_set_custom_encoding(val_data(v), val_string(value));
	return val_null;
}
value hxwebkit_webview_set_editable(value v, value value) {
	webkit_web_view_set_editable(val_data(v), val_bool(value));
	return value;
}
value hxwebkit_webview_set_full_content_zoom(value v, value value) {
	webkit_web_view_set_full_content_zoom(val_data(v), val_float(value));
	return val_null;
}
value hxwebkit_webview_set_highlight_text_matches(value v, value value) {
	webkit_web_view_set_highlight_text_matches(val_data(v), val_bool(value));
	return val_null;
}
value hxwebkit_webview_set_maintains_back_forward_list(value v, value value) {
	webkit_web_view_set_maintains_back_forward_list(val_data(v),
			val_bool(value));
	return val_null;
}
void set_websettings_field(value v, field f, void * p) {
	char * key = str_replace(val_string( val_field_name( f ) ), "_", "-");
	switch(val_type(v)) {
		case VAL_NULL :
		g_object_set (G_OBJECT(_websettings), key, val_null, NULL );
		break;
		case VAL_INT :
		g_object_set (G_OBJECT(_websettings), key, val_int(v), NULL );
		break;
		case VAL_BOOL :
		g_object_set (G_OBJECT(_websettings), key, val_bool(v), NULL );
		break;
		case VAL_STRING :
		g_object_set (G_OBJECT(_websettings), key, val_string(v), NULL );
		break;
		case VAL_FLOAT :
		g_object_set (G_OBJECT(_websettings), key, val_float(v), NULL );
		break;
	}
}
value hxwebkit_webview_set_settings(value v, value settings) {
	_websettings = webkit_web_settings_new();
	val_iter_fields(settings, set_websettings_field, NULL);
	webkit_web_view_set_settings(WEBKIT_WEB_VIEW(val_data(v)), _websettings);
	_websettings = NULL;
	return val_null;
}
value hxwebkit_webview_set_setting(value v, value id, value _value) {
	//TODO
	WebKitWebView * view = WEBKIT_WEB_VIEW(val_data(v));
	_websettings = webkit_web_view_get_settings(view);
	set_websettings_field(_value, val_id(str_replace(val_string(id), "_", "-")),
			NULL);
	webkit_web_view_set_settings(view, _websettings);
	//_websettings = NULL;
	//WebKitWebSettings * _websettings = webkit_web_view_get_settings(val_data(v));
	//set_websettings_field(_value, val_id(val_string(id)), NULL);
	//webkit_web_view_set_settings(WEBKIT_WEB_VIEW(val_data(v)), _websettings);
	//_websettings = NULL;
	return val_null;
}
value hxwebkit_webview_set_transparent(value v, value value) {
	webkit_web_view_set_transparent(val_data(v), val_bool(value));
	return val_null;
}
value hxwebkit_webview_set_view_mode(value v, value value) {
	//TODO
	//webkit_web_view_set_view_mode(val_data(v),val_bool(value));
	return val_null;
}
value hxwebkit_webview_set_view_source_mode(value v, value value) {
	webkit_web_view_set_view_source_mode(val_data(v), val_bool(value));
	return val_null;
}
value hxwebkit_webview_set_zoom_level(value v, value value) {
	webkit_web_view_set_zoom_level(val_data(v), val_float(value));
	return value;
}
value hxwebkit_webview_stop_loading(value v) {
	webkit_web_view_stop_loading(val_data(v));
	return val_null;
}
value hxwebkit_webview_undo(value v) {
	webkit_web_view_undo(val_data(v));
	return val_null;
}
value hxwebkit_webview_unmark_text_matches(value v) {
	webkit_web_view_unmark_text_matches(val_data(v));
	return val_null;
}
value hxwebkit_webview_zoom_in(value v) {
	webkit_web_view_zoom_in(val_data(v));
	return val_null;
}
value hxwebkit_webview_zoom_out(value v) {
	webkit_web_view_zoom_out(val_data(v));
	return val_null;
}
value hxwebkit_webview_get_window_features(value _v) {
	//TODO
	WebKitWebWindowFeatures * s = webkit_web_view_get_window_features(val_data(_v));
	value o = alloc_object(NULL);
	gint x;
	g_object_get(s,"x",&x,NULL);
	alloc_field( o, val_id("x"), alloc_int(x));
	gint y;
	g_object_get(s,"y",&y,NULL);
	alloc_field( o, val_id("y"), alloc_int(y));
	gboolean fullscreen;
	g_object_get(s,"fullscreen",&fullscreen,NULL);
	alloc_field( o, val_id("fullscreen"), alloc_bool(fullscreen));
	gint width;
	g_object_get(s,"width",&width,NULL);
	alloc_field( o, val_id("width"), alloc_int(width));
	gint height;
	g_object_get(s,"height",&height,NULL);
	alloc_field( o, val_id("height"), alloc_int(height));
	gboolean locationbar_visible;
	g_object_get(s,"locationbar-visible",&locationbar_visible,NULL);
	alloc_field( o, val_id("locationbar_visible"), alloc_bool(locationbar_visible));
	gboolean menubar_visible;
	g_object_get(s,"menubar-visible",&menubar_visible,NULL);
	alloc_field( o, val_id("menubar_visible"), alloc_bool(menubar_visible));
	gboolean scrollbar_visible;
	g_object_get(s,"scrollbar-visible",&scrollbar_visible,NULL);
	alloc_field( o, val_id("scrollbar_visible"), alloc_bool(scrollbar_visible));
	gboolean statusbar_visible;
	g_object_get(s,"statusbar-visible",&statusbar_visible,NULL);
	alloc_field( o, val_id("statusbar_visible"), alloc_bool(statusbar_visible));
	gboolean toolbar_visible;
	g_object_get(s,"toolbar-visible",&toolbar_visible,NULL);
	alloc_field( o, val_id("toolbar_visible"), alloc_bool(toolbar_visible));
	return o;
}

DEFINE_PRIM( hxwebkit_webview_init, 1);

DEFINE_PRIM( hxwebkit_webview_can_copy_clipboard, 1);
DEFINE_PRIM( hxwebkit_webview_can_cut_clipboard, 1);
DEFINE_PRIM( hxwebkit_webview_can_go_back, 1);
DEFINE_PRIM( hxwebkit_webview_can_go_back_or_foward, 2);
DEFINE_PRIM( hxwebkit_webview_can_go_foward, 1);
DEFINE_PRIM( hxwebkit_webview_can_paste_clipboard, 1);
DEFINE_PRIM( hxwebkit_webview_can_go_redo, 1);
DEFINE_PRIM( hxwebkit_webview_can_show_mimetype, 2);
DEFINE_PRIM( hxwebkit_webview_can_go_undo, 1);

DEFINE_PRIM( hxwebkit_webview_copy_clipboard, 1);
DEFINE_PRIM( hxwebkit_webview_cut_clipboard, 1);
DEFINE_PRIM( hxwebkit_webview_delete_selection, 1);
DEFINE_PRIM( hxwebkit_webview_execute_script, 2);

DEFINE_PRIM( hxwebkit_webview_get_back_forward_list, 1);
DEFINE_PRIM( hxwebkit_webview_get_copy_target_list, 1);
DEFINE_PRIM( hxwebkit_webview_get_custom_encoding, 1);
DEFINE_PRIM( hxwebkit_webview_get_dom_document, 1);
DEFINE_PRIM( hxwebkit_webview_get_editable, 1);
DEFINE_PRIM( hxwebkit_webview_get_encoding, 1);
DEFINE_PRIM( hxwebkit_webview_get_focused_frame, 1);
DEFINE_PRIM( hxwebkit_webview_get_full_content_zoom, 1);
DEFINE_PRIM( hxwebkit_webview_get_hit_test_result, 1);
DEFINE_PRIM( hxwebkit_webview_get_icon_uri, 1);
DEFINE_PRIM( hxwebkit_webview_get_inspector, 1);
DEFINE_PRIM( hxwebkit_webview_get_load_status, 1);
DEFINE_PRIM( hxwebkit_webview_get_main_frame, 1);
DEFINE_PRIM( hxwebkit_webview_get_paste_target_list, 1);
DEFINE_PRIM( hxwebkit_webview_get_progress, 1);
DEFINE_PRIM( hxwebkit_webview_get_settings, 1);
DEFINE_PRIM( hxwebkit_webview_get_title, 1);
DEFINE_PRIM( hxwebkit_webview_get_transparent, 1);
DEFINE_PRIM( hxwebkit_webview_get_uri, 1);
DEFINE_PRIM( hxwebkit_webview_get_view_mode, 1);
DEFINE_PRIM( hxwebkit_webview_get_view_source_mode, 1);
DEFINE_PRIM( hxwebkit_webview_get_viewport_attributes, 1);
DEFINE_PRIM( hxwebkit_webview_get_zoom_level, 1);

DEFINE_PRIM( hxwebkit_webview_go_back, 1);
DEFINE_PRIM( hxwebkit_webview_go_back_or_forward, 2);
DEFINE_PRIM( hxwebkit_webview_go_forward, 1);
DEFINE_PRIM( hxwebkit_webview_go_to_back_forward_item, 2);
DEFINE_PRIM( hxwebkit_webview_has_selection, 1);
DEFINE_PRIM( hxwebkit_webview_load_html_string, 3);
DEFINE_PRIM( hxwebkit_webview_load_request, 1);
DEFINE_PRIM( hxwebkit_webview_load_string, 5);
DEFINE_PRIM( hxwebkit_webview_load_uri, 1);
DEFINE_PRIM( hxwebkit_webview_mark_text_matches, 4);
DEFINE_PRIM( hxwebkit_webview_move_cursor, 3);
//DEFINE_PRIM( hxwebkit_webview_new, 1);
//DEFINE_PRIM( hxwebkit_webview_open, 2);
DEFINE_PRIM( hxwebkit_webview_paste_clipboard, 1);
DEFINE_PRIM( hxwebkit_webview_redo, 1);
DEFINE_PRIM( hxwebkit_webview_reload, 1);
DEFINE_PRIM( hxwebkit_webview_reload_bypass_cache, 1);
DEFINE_PRIM( hxwebkit_webview_search_text, 5);
DEFINE_PRIM( hxwebkit_webview_select_all, 1);

DEFINE_PRIM( hxwebkit_webview_set_custom_encoding, 2);
DEFINE_PRIM( hxwebkit_webview_set_editable, 2);
DEFINE_PRIM( hxwebkit_webview_set_full_content_zoom, 2);
DEFINE_PRIM( hxwebkit_webview_set_highlight_text_matches, 2);
DEFINE_PRIM( hxwebkit_webview_set_maintains_back_forward_list, 2);
DEFINE_PRIM( hxwebkit_webview_set_settings, 2);
DEFINE_PRIM( hxwebkit_webview_set_transparent, 2);
DEFINE_PRIM( hxwebkit_webview_set_view_mode, 2);
DEFINE_PRIM( hxwebkit_webview_set_view_source_mode, 2);
DEFINE_PRIM( hxwebkit_webview_set_zoom_level, 2);

DEFINE_PRIM( hxwebkit_webview_stop_loading, 1);
DEFINE_PRIM( hxwebkit_webview_undo, 1);
DEFINE_PRIM( hxwebkit_webview_unmark_text_matches, 1);
DEFINE_PRIM( hxwebkit_webview_zoom_in, 1);
DEFINE_PRIM( hxwebkit_webview_zoom_out, 1);

DEFINE_PRIM( hxwebkit_webview_get_window_features, 1);
