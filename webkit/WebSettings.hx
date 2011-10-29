package webkit;

typedef WebSettings = {
	
	var auto_load_images : Bool;
	var auto_resize_window : Bool;
	var auto_shrink_images : Bool;
	var cursive_font_family : String;
	var default_encoding : String;
	var default_font_family : String;
	var default_font_size : Int;
	var default_monospace_font_size : Int;
	
	//var editing_behavior : EditingBehavior; //Int;
	var enable_caret_browsing : Bool;
	var enable_default_context_menu : Bool;
	var enable_developer_extras : Bool;
	var enable_dns_prefetching : Bool;
	var enable_dom_paste : Bool;
	var enable_file_access_from_file_uris : Bool;
  	var enable_frame_flattening : Bool;
  	var enable_fullscreen : Bool;
  	var enable_html5_database : Bool;
  	var enable_html5_local_storage : Bool;
  	var enable_hyperlink_auditing : Bool;
  	var enable_java_applet : Bool;
  	var enable_offline_web_application_cache : Bool;
  	var enable_page_cache : Bool;
  	var enable_plugins : Bool;
  	var enable_private_browsing : Bool;
  	var enable_scripts : Bool;
  	var enable_site_specific_quirks : Bool;
  	var enable_spatial_navigation : Bool;
  	var enable_spell_checking : Bool;
  	var enable_universal_access_from_file_uris : Bool;
  	var enable_webgl : Bool;
  	var enable_xss_auditor : Bool;
  	
  	var enforce_96_dpi : Bool;
  	var fantasy_font_family : String;
  	var html5_local_storage_database_path : String;
  	var javascript_can_access_clipboard : Bool;
  	var javascript_can_open_windows_automatically : Bool;
  	var minimum_font_size : Int;
  	var minimum_logical_font_size : Int;
  	var monospace_font_family : String;
  	var print_backgrounds : Bool;
  	var resizable_text_areas : Bool;
  	var sans_serif_font_family : String;
  	var serif_font_family : String;
  	var spell_checking_languages : String;
  	var tab_key_cycles_through_elements : Bool;
  	var user_agent : String;
  	var user_stylesheet_uri : String;
  	var zoom_step : Float;
}
