
#include <hxwebkit_plugin.h>

//static GtkWidget* register_button = NULL;

/*
static void cb_setButtonColor(GtkWidget* button, gpointer userdata) {
	GtkWidget* webview = GTK_WIDGET(userdata);
	GdkColor color;
	gchar* script;
	gtk_color_button_get_color(GTK_COLOR_BUTTON(button), &color);
	script = g_strdup_printf(
			"document.body.style.backgroundColor = \"#%x%x%x\";",
			color.red / 256, color.green / 256, color.blue / 256);
	script = g_strdup_printf(
			"document.body.style.backgroundColor=\"#ff0000\";");
	webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), script);
}

static GtkWidget* web_view_create_plugin_widget_cb(GtkWidget* webview,
		const gchar* mime_type, const gchar* uri, GHashTable* param,
		gpointer userdata) {
	if (g_str_equal(mime_type, "application/x-gtk-color-button")) {
		GtkWidget* btn = gtk_color_button_new();
		GdkColor color;
		gdk_color_parse("#3A47EF", &color);
		gtk_color_button_set_color(GTK_COLOR_BUTTON(btn), &color);
		g_signal_connect(btn, "color-set", G_CALLBACK(cb_setButtonColor),
				webview);
		return btn;
	}
	return NULL;
}
*/

/*
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


//##############################################

/*
static JSValueRef testplugin_init() {
}
*/


