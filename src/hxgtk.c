
#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <neko.h>

static value hxgtk_init() {
	if (!g_thread_supported())
		g_thread_init(NULL);
	g_type_init();
	gtk_init_check(NULL, NULL);
	return val_null;
}

static value hxgtk_run() {
	gtk_main();
	return val_null;
}

static value hxgtk_exit() {
	gtk_main_quit();
	return val_null;
}


DEFINE_KIND(k_window);

//value *cb_close = NULL;

void reportClose( value *cb ) {
	printf("---------------Window closed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	//val_call0(*cb);
}

//TODO window_constructor
value hxgtk_window_init(value title, value width, value height, value onClose ) {

	val_check( title, string);
	val_check( width, int);
	val_check( height, int);
	val_check_function(onClose,0);
	value *cb_close = alloc_root(1);
	*cb_close = onClose;

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
	g_signal_connect(win, "destroy", G_CALLBACK(reportClose), cb_close );

	return alloc_abstract(k_window, win);
}

value hxgtk_window_close(value w) {
	gtk_widget_destroy(val_data(w));
	return val_null;
}

value hxgtk_window_active(value w) {
	//TODO test/clean
	gboolean b;
	b = gtk_window_is_active(val_data(w));
	//printf("########%i\n",b);
	return alloc_bool(b);
}

value hxgtk_window_gettitle(value w) {
	return alloc_string(gtk_window_get_title(val_data(w)));
}
value hxgtk_window_settitle(value w, value t) {
	gtk_window_set_title(val_data(w), val_string(t));
	return t;
}

value hxgtk_window_getresizeable(value w) {
	//printf("%i\n",gtk_window_get_resizable(val_data(w)));
	gboolean b;
	b = gtk_window_get_resizable(val_data(w));
	return alloc_bool(b);
}
//TODO this sets the  window size to 0,0 wtf!?
value hxgtk_window_setresizeable(value w, value v) {
	//printf("%i\n",gtk_window_get_resizable(val_data(w)));
	gtk_window_set_resizable(val_data(w), val_bool(v));
	return v;
}

//TODO
/*
value hxgtk_window_getposition( value w) {
	//printf("TODO get pos \n");
	int rx;
	int ry;
	gtk_window_get_position( GTK_WINDOW(val_data(w)),&rx,&ry);
	//printf("PX %i \n",rx);
	//printf("PY %i \n",ry);
	return val_null;
}
*/
value hxgtk_window_setposition( value w, value p) {
	GtkWindowPosition pos;
	switch(val_int(p)) {
	case 0 :
		pos = GTK_WIN_POS_NONE;
		break;
	case 1 :
		pos = GTK_WIN_POS_CENTER;
		break;
	case 2 :
		pos = GTK_WIN_POS_MOUSE;
		break;
	case 3 :
		pos = GTK_WIN_POS_CENTER_ALWAYS;
		break;
	case 4 :
		pos = GTK_WIN_POS_CENTER_ON_PARENT;
		break;
	}
	gtk_window_set_position( val_data(w), pos );
	return val_null;
}

value hxgtk_window_getopacity(value w) {
	if (!val_is_abstract(w) || !val_is_kind(w, k_window))
		neko_error();
	return alloc_float(gtk_window_get_opacity(val_data(w)));
}
value hxgtk_window_setopacity(value w, value v) {
	val_check(v,float);
	if (!val_is_abstract(w) || !val_is_kind(w, k_window))
		neko_error();
	gtk_window_set_opacity(val_data(w), val_float(v));
	return v;
}

value hxgtk_window_gethastoplevelfocus(value w) {
	return alloc_bool(gtk_window_has_toplevel_focus(GTK_WINDOW(val_data(w))));
}

value hxgtk_window_maximize(value w) {
	gtk_window_maximize(val_data(w));
	return val_null;
}
value hxgtk_window_unmaximize(value w) {
	gtk_window_unmaximize(val_data(w));
	return val_null;
}

value hxgtk_window_fullscreen(value w) {
	gtk_window_fullscreen(val_data(w));
	return val_null;
}
value hxgtk_window_unfullscreen(value w) {
	gtk_window_unfullscreen(val_data(w));
	return val_null;
}

value hxgtk_window_resize(value win, value w, value h) {
	gtk_window_resize(val_data(win), val_int(w), val_int(h));
	return val_null;
}

value hxgtk_window_iconify(value win) {
	gtk_window_iconify(val_data(win));
	return val_null;
}
value hxgtk_window_deiconify(value win) {
	gtk_window_deiconify(val_data(win));
	return val_null;
}

value hxgtk_window_present(value win, value timestamp) {
	gtk_window_present_with_time(val_data(win),val_int(timestamp));
	return val_null;
}


value hxgtk_window_setkeepabove(value win, value v) {
	gtk_window_set_keep_above(val_data(win),val_bool(v));
	return val_null;
}
value hxgtk_window_setkeepbelow(value win, value v) {
	gtk_window_set_keep_below(val_data(win),val_bool(v));
	return val_null;
}

value hxgtk_window_setdecorated(value w, value v) {
	gtk_window_set_decorated(val_data(w),val_bool(v));
	return val_null;
}

value hxgtk_window_setdeleteable(value w, value v) {
	gtk_window_set_deletable(val_data(w),val_bool(v));
	return val_null;
}

value hxgtk_window_move(value w, value x, value y) {
	gtk_window_move(val_data(w),val_int(x),val_int(y));
	return val_null;
}

DEFINE_PRIM( hxgtk_init, 0);
DEFINE_PRIM( hxgtk_run, 0);
DEFINE_PRIM( hxgtk_exit, 0);

DEFINE_PRIM( hxgtk_window_init, 4);
DEFINE_PRIM( hxgtk_window_close, 1);
DEFINE_PRIM( hxgtk_window_active, 1);
DEFINE_PRIM( hxgtk_window_gettitle, 1);
DEFINE_PRIM( hxgtk_window_settitle, 2);
DEFINE_PRIM( hxgtk_window_getresizeable, 1);
DEFINE_PRIM( hxgtk_window_setresizeable, 2);
DEFINE_PRIM( hxgtk_window_getopacity, 1);
DEFINE_PRIM( hxgtk_window_setopacity, 2);
DEFINE_PRIM( hxgtk_window_gethastoplevelfocus, 1);
//DEFINE_PRIM( hxgtk_window_getposition, 1);
DEFINE_PRIM( hxgtk_window_setposition, 2);
DEFINE_PRIM( hxgtk_window_maximize, 1);
DEFINE_PRIM( hxgtk_window_unmaximize, 1);
DEFINE_PRIM( hxgtk_window_fullscreen, 1);
DEFINE_PRIM( hxgtk_window_unfullscreen, 1);
DEFINE_PRIM( hxgtk_window_resize, 3);
DEFINE_PRIM( hxgtk_window_iconify, 1);
DEFINE_PRIM( hxgtk_window_deiconify, 1);
DEFINE_PRIM( hxgtk_window_present, 2);
DEFINE_PRIM( hxgtk_window_setkeepabove, 2);
DEFINE_PRIM( hxgtk_window_setkeepbelow, 2);
DEFINE_PRIM( hxgtk_window_setdecorated, 2);
DEFINE_PRIM( hxgtk_window_setdeleteable, 2);
DEFINE_PRIM( hxgtk_window_move, 3);
