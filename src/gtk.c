
#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <neko.h>



static value wk_init() {
	if (!g_thread_supported())
		g_thread_init(NULL);
	g_type_init();
	gtk_init_check(NULL, NULL);
	return val_null;
}

static value wk_run() {
	gtk_main();
	return val_null;
}

static value wk_exit() {
	gtk_main_quit();
	return val_null;
}



DEFINE_KIND(k_window);

value *cb_close = NULL;

value window_init(value title, value width, value height/*, value cb_close*/) {

	val_check( title, string);
	val_check( width, int);
	val_check( height, int);
	//val_check_function(cb_close,0);

	GtkWidget* win;
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(win), val_string(title));
	gtk_window_set_default_size(GTK_WINDOW(win), val_int(width),
			val_int(height));
	//gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	//	gtk_window_set_icon(GTK_WINDOW(win), create_pixbuf("icon_16.png"));
	//gtk_window_set_decorated(true);
	//gtk_window_set_deletable

	//gtk_widget_show_all(win);

	//g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	return alloc_abstract(k_window, win);
}

value window_close(value w) {
	gtk_widget_destroy(val_data(w));
	return val_null;
}

value window_active(value w) {
	return alloc_bool(gtk_window_is_active(val_data(w)));
}

value window_gettitle(value w) {
	return alloc_string(gtk_window_get_title(val_data(w)));
}
value window_settitle(value w, value t) {
	gtk_window_set_title(val_data(w), val_string(t));
	return t;
}

value window_getresizeable(value w) {
	return alloc_bool(gtk_window_get_resizable(val_data(w)));
}
value window_setresizeable(value w, value v) {
	gtk_window_set_resizable(val_data(w), val_bool(v));
	return v;
}

/*
 value window_getposition(value w) {
 //p gtk_window_get_position(val_data(w));
 //printf("ä################ %i\n", gtk_window_get_position(val_data(w) );
 gint * tx = 0;
 gint * ty = 0;
 gtk_window_get_position(val_data(w),tx,ty);
 printf("###%i \n",tx);
 printf("###%i \n",ty);

 return val_null;
 //return alloc_string( gtk_window_get_title(val_data(w)) );
 }
 value window_setposition(value w,value p) {
 printf("sET pos\n");
 gtk_window_set_position(val_data(w),GTK_WIN_POS_MOUSE);
 gtk_widget_show_all(val_data(w));
 return val_null;
 }
 */


value window_getopacity(value w) {
	if (!val_is_abstract(w) || !val_is_kind(w, k_window))
		neko_error();
	return alloc_float(gtk_window_get_opacity(val_data(w)));
}
value window_setopacity(value w, value v) {
	val_check(v,float);
	if (!val_is_abstract(w) || !val_is_kind(w, k_window))
		neko_error();
	gtk_window_set_opacity(val_data(w), val_float(v));
	return v;
}

value window_maximize(value w) {
	gtk_window_maximize(val_data(w));
	return val_null;
}
value window_unmaximize(value w) {
	gtk_window_unmaximize(val_data(w));
	return val_null;
}

value window_fullscreen(value w) {
	gtk_window_fullscreen(val_data(w));
	return val_null;
}
value window_unfullscreen(value w) {
	gtk_window_unfullscreen(val_data(w));
	return val_null;
}

value window_resize(value win, value w, value h) {
	gtk_window_resize(val_data(win), val_int(w), val_int(h));
	return val_null;
}


DEFINE_PRIM( wk_init, 0);
DEFINE_PRIM( wk_run, 0);
DEFINE_PRIM( wk_exit, 0);

DEFINE_PRIM( window_init, 3);
DEFINE_PRIM( window_close, 1);
DEFINE_PRIM( window_active, 1);
DEFINE_PRIM( window_gettitle, 1);
DEFINE_PRIM( window_settitle, 2);
DEFINE_PRIM( window_getresizeable, 1);
DEFINE_PRIM( window_setresizeable, 2);
DEFINE_PRIM( window_getopacity, 1);
DEFINE_PRIM( window_setopacity, 2);
//DEFINE_PRIM( window_getposition, 1);
//DEFINE_PRIM( window_setposition, 2);
DEFINE_PRIM( window_maximize, 1);
DEFINE_PRIM( window_unmaximize, 1);
DEFINE_PRIM( window_fullscreen, 1);
DEFINE_PRIM( window_unfullscreen, 1);
DEFINE_PRIM( window_resize, 3);
