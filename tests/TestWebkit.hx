
import neko.io.File;

private class Win extends gtk.Window {
	public var view(default,null) : webkit.WebView;
	public function new( title : String, w : Int = 600, h : Int = 500 ) {
		super( title, w, h );
		view = new webkit.WebView( this );
	}
}

class TestWebkit {
	
	static inline function print(t) neko.Lib.println(t)
	
	static function main() {
		
		var cwd = neko.Sys.getCwd();
		
		gtk.Lib.init();
		webkit.Lib.init();
		
		notify.Lib.init( "TestHXLibnotify" );
		print( "  notify.ServerInfo: "+notify.Lib.getServerInfo() );
		var notifyCaps = notify.Lib.getServerCaps();
		print( "  notify.ServerCapabilities: "+notifyCaps );
		var n = new notify.Notification( "HXWebkit", 'Version: '+webkit.Lib.VERSION, cwd+'img/haxe_128.png', 1000 );
		n.show();
		
		var win = new Win( "HXWebkit.test", 480, 720 );
		win.view.setSettings( {
			default_monospace_font_size: 12,
		    enable_scripts: true,
		    resizable_text_areas: true,
		    enable_frame_flattening: false,
		    enable_html5_local_storage: true,
		    default_font_size: 12,
		    user_agent: 'Mozilla/5.0 (X11; Linux i686) AppleWebKit/534.26+ (KHTML, like Gecko) Version/5.0 Safari/534.26+',
		    enable_hyperlink_auditing: false,
		    enable_offline_web_application_cache: false,
		    minimum_font_size: 5,
		    enable_fullscreen: true,
		    enable_html5_database: true,
		    fantasy_font_family: "serif",
		    user_stylesheet_uri: "style.css",
		    enable_developer_extras: false,
		    serif_font_family: "serif",
		    zoom_step: 0.1000000015,
		    monospace_font_family: "monospace",
		    print_backgrounds: true,
		    enable_private_browsing: false,
		    enable_universal_access_from_file_uris: true,
		    tab_key_cycles_through_elements: true,
		    sans_serif_font_family: "sans-serif",
		    enable_spell_checking: false,
		    enable_dns_prefetching: true,
		    enable_caret_browsing: false,
		    auto_resize_window: false,
		    cursive_font_family: "serif",
		    enable_file_access_from_file_uris: true,
		    default_encoding: "iso-8859-1",
		    enable_plugins: true,
		    javascript_can_open_windows_automatically: true,
		    minimum_logical_font_size: 5,
		    enable_page_cache: false,
		    enable_dom_paste: true,
		    enforce_96_dpi: false,
		    auto_shrink_images: true,
		    javascript_can_access_clipboard: true,
		    enable_java_applet: false,
		    enable_spatial_navigation: false,
		    enable_default_context_menu: false,
		    spell_checking_languages: null,
		    default_font_family: "sans-serif",
		    enable_site_specific_quirks: true,
		    enable_xss_auditor: true,
		});
		
		print( "  WebSettings:" );
		var settings = win.view.getSettings();
		for( f in Reflect.fields( settings ) ) { print( "    "+f+": "+Reflect.field(settings,f) ); }
		
		win.view.loadString( File.getContent( cwd+"app.html" ) );
		
		gtk.Lib.run();
		notify.Lib.uninit();
		gtk.Lib.quit();
	}
	
}
