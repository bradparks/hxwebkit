package webkit;

enum ViewMode {
	windowed;
	floating;
	fullscreen;
	maximized;
	minized;
}

enum LoadStatus {
	provisional;
	commited;
	load_finished;
	first_visually_non_empty_layout;
	failed;
}

typedef WindowFeatures = {
	var x : Int;
	var y : Int;
	var fullscreen : Bool;
	var width : Int;
	var height : Int;
	var locationbar_visible : Bool;
	var menubar_visible : Bool;
	var scrollbar_visible : Bool;
	var statusbar_visible : Bool;
	var toolbar_visible : Bool;
}

typedef ViewportAttributes = {
	var valid : Bool;
	var height : Int;
	var width : Int;
	var available_width : Int;
	var available_height : Int;
	var desktop_width : Int;
	var device_width : Int;
	var device_height : Int;
	var device_dpi : Int;
	var device_pixel_ratio : Int;
	var user_scalable : Bool;
	var initial_scale_factor : Float;
	var minimum_scale_factor : Float;
	var maximum_scale_factor : Float;
}

class WebView {
	
	public var canCopyClipboard(getCanCopyClipboard,null) : Bool;
	public var canCutClipboard(getCanCutClipboard,null) : Bool;
	public var canGoBack(getCanGoBack,null) : Bool;
	public var canGoForward(getCanGoForward,null) : Bool;
	public var canPasteClipboard(getCanPasteClipboard,null) : Bool;
	public var canRedo(getCanRedo,null) : Bool;
	public var canUndo(getCanUndo,null) : Bool;
	//public var backForwardList(getBackForwardList,null) : List<>;
	//public var copyTargetList(getCopyTargetList,null) : Array<Dynamic>;
	public var customEncoding(getCustomEncoding,setCustomEncoding) : String;
	//public var domDocument(getDOMDocument,null) : DOMDocument;
	public var editable(getEditable,setEditable) : Bool;
	public var encoding(getEncoding,null) : String;
	//public var focusedFrame(getFocusedFrame,null) : WebFrame;
	public var fullContentZoom(getFullContentZoom,setFullContentZoom) : Bool;
	//public var hit_test
	public var iconURI(getIconURI,null) : String;
	//public var inspector(getWebInspector,null) : WebInspector;
	public var loadStatus(getLoadStatus,null) : LoadStatus;
	//public var mainFrame(getMainFrame,null) : LoadStatus;
	//public var pasteTargetList(getPasteTargetList,null) : List<>;
	public var progress(getProgress,null) : Float;
	///////public var settings(getSettings,setSettings) : Float;
	public var title(getTitle,null) : Float;
	public var transparent(getTransparent,setTransparent) : Bool;
	public var uri(getUri,null) : String;
	public var viewMode(getViewMode,setViewMode) : ViewMode;
	public var viewSourceMode(getViewSourceMode,setViewSourceMode) : Bool;
	public var viewportAttributes(getViewportAttributes,null) : ViewportAttributes;
	public var zoomLevel(getZoomLevel,setZoomLevel) : Float;
	public var hasSelection(getHasSelection,null) : Bool;
	public var windowFeatures(getWindowFeatures,null) : WindowFeatures;
	
	var __i : Void;
	
	public function new( win : gtk.Window ) {
		__i = _constructor( untyped win.__i );
	}
	
	inline function getCanCopyClipboard() : Bool return _can_copy_clipboard(__i)
	inline function getCanCutClipboard() : Bool return _can_cut_clipboard(__i)
	inline function getCanGoBack() : Bool return _can_go_back(__i)
	inline function getCanGoForward() : Bool return _can_go_foward(__i)
	inline function getCanPasteClipboard() : Bool return _can_paste_clipboard(__i)
	inline function getCanRedo() : Bool return _can_copy_clipboard(__i)
	inline function getCanUndo() : Bool return _can_copy_clipboard(__i)
	public inline function canGoBackOrForward( steps : Int ) : Bool return _can_go_back_or_foward(__i,steps)
	public inline function canShowMimeType( mimetype : String ) : Bool return _can_go_back_or_foward(__i,untyped mimetype.__S)
	public inline function copyClipboard() _copy_clipboard(__i)
	public inline function cutClipboard() _cut_clipboard(__i)
	public inline function deleteSelection() _delete_selection(__i)
	public inline function executeScript( script : String ) _execute_script(__i,untyped script.__s)
	//inline function getBackForwardList() : Array<> _get_back_forward_list(__i)
	inline function getCopyTargetList() : Array<Dynamic> return _get_copy_target_list(__i)
	inline function getCustomEncoding() : String return _get_custom_encoding(__i)
	inline function setCustomEncoding(encoding:String) : String return _set_custom_encoding(__i,untyped encoding.__s)
	//inline function getDOMDocument() : DOMDocument return _get_dom_document(__i)
	inline function getEditable() : Bool return _get_editable(__i)
	inline function setEditable(v:Bool) : Bool return _set_editable(__i,v)
	inline function getEncoding() : String return _get_encoding(__i)
	//inline function getFocusedFrame() : WebFrame return _get_focused_frame(__i)
	inline function getFullContentZoom() : Bool return _get_full_content_zoom(__i)
	inline function setFullContentZoom(v:Bool) : Bool return _set_full_content_zoom(__i,v)
	//hittest
	inline function getIconURI() : String return _get_icon_uri(__i)
	//inline function getWebInspector() : WebInspector return _get_icon_uri(__i)
	inline function getLoadStatus() : LoadStatus return Type.createEnumIndex(LoadStatus,_get_load_status(__i))
	//inline function getMainFrame() : WebFrame return _get_main_frame(__i)
	//inline function getPasteTargetList() : List<> return _get_paste_target_list(__i)
	inline function getProgress() : Float return _get_progress(__i)
	
	 //TODO
	public inline function getSettings() : WebSettings return _get_settings(__i)
	public inline function setSettings( settings : WebSettings ) : WebSettings return _set_settings(__i,settings)
	
	inline function getTitle() : Float return _get_title(__i)
	inline function getTransparent() : Bool return _get_transparent(__i)
	inline function setTransparent( v : Bool ) : Bool { _set_transparent(__i,v); return v; }
	inline function getUri() : String return _get_uri(__i)
	inline function getViewMode() : ViewMode return Type.createEnumIndex( ViewMode, _get_view_mode(__i) )
	inline function setViewMode( v : ViewMode ) : ViewMode {
		var i = _set_view_mode( Type.enumIndex( v ) );
		return v;
	}
	inline function getViewSourceMode() : Bool return _get_view_source_mode(__i)
	inline function setViewSourceMode( v : Bool ) : Bool { _set_view_source_mode(__i,v); return v; }
	inline function getViewportAttributes() : ViewportAttributes return _get_viewport_attributes(__i)
	inline function getZoomLevel() : Float return _get_zoom_level(__i)
	inline function setZoomLevel(v:Float) : Float return _set_zoom_level(__i,v)
	public inline function goBack() _go_back(__i)
	public inline function goBackOrForward(steps:Int) _go_back_or_forward(__i,steps)
	public inline function goForward() _go_forward(__i)
//	public inline function goBackForwardItem(item:WebHistoryItem) : Bool return _go_to_back_forward_item(__i,item)
	inline function getHasSelection() : Bool return _has_selection(__i)
	public inline function loadHtmlString(content:String,?base_uri:String) _load_html_string(__i,untyped content.__s,untyped base_uri.__s)
	//public inline function loadRequest(r:NetworkRequest) _load_request(__i,r)
	public inline function loadString(content:String,?mime_type:String,?encoding:String,?base_uri:String) {
		_load_string( __i, untyped content.__s,
			(mime_type!=null) ? untyped mime_type.__s : null,
			(encoding!=null) ? untyped encoding.__s : null,
			(base_uri!=null) ? untyped base_uri.__s : null );
	}
	public inline function loadUri(uri:String) _load_uri(__i,untyped uri.__s)
	public inline function markTextMatches(string:String,case_sensitive:Bool,limit:Int) _mark_text_matches(__i,untyped string.__s,case_sensitive,limit)
	public inline function moveCursor(step:Bool,count:Int) _move_cursor(__i,step,count)
	public inline function pasteClipboard() _paste_clipboard(__i)
	public inline function redo() _redo(__i)
	public inline function reload() _reload(__i)
	public inline function reloadBypassCache() _reload_bypass_cache(__i)
	public inline function searchText(text:String,case_sensitive:Bool,forward:Bool,wrap:Bool) _search_text(__i,untyped text.__s,case_sensitive,forward,wrap)
	public inline function selectAll() _select_all(__i)
	public inline function stopLoading() _stop_loading(__i)
	public inline function undo() _undo(__i)
	public inline function unmarkTextMatches() _unmark_text_matches(__i)
	public inline function zoomIn() _zoom_in(__i)
	public inline function zoomOut() _zoom_out(__i)
	inline function getWindowFeatures() : WindowFeatures return _get_window_features(__i)
	
	static var _constructor = x( "constructor" );
	
	static var _can_copy_clipboard = x( "can_copy_clipboard" );
	static var _can_cut_clipboard = x( "can_cut_clipboard" );
	static var _can_go_back = x( "can_go_back" );
	static var _can_go_back_or_foward = x( "can_go_back_or_foward", 1 );
	static var _can_go_foward = x( "can_go_foward" );
	static var _can_paste_clipboard = x( "can_paste_clipboard" );
	static var _can_go_redo = x( "can_go_redo" );
	static var _can_show_mimetype = x( "can_show_mimetype", 1 );
	static var _can_go_undo = x( "can_go_undo" );
	
	static var _copy_clipboard = x( "copy_clipboard" );
	static var _cut_clipboard = x( "cut_clipboard" );
	static var _delete_selection = x( "delete_selection" );
	static var _execute_script = x( "execute_script", 1 );
	
	static var _get_back_forward_list = x( "get_back_forward_list" );
	static var _get_copy_target_list = x( "get_copy_target_list" );
	static var _get_custom_encoding = x( "get_custom_encoding" );
	static var _get_dom_document = x( "get_dom_document" );
	static var _get_editable = x( "get_editable" );
	static var _get_encoding = x( "get_encoding" );
	static var _get_focused_frame = x( "get_focused_frame" );
	static var _get_full_content_zoom = x( "get_full_content_zoom" );
	static var _get_hit_test_result = x( "get_hit_test_result" );
	static var _get_icon_uri = x( "get_icon_uri" );
	static var _get_inspector = x( "get_inspector" );
	static var _get_load_status = x( "get_load_status" );
	static var _get_main_frame = x( "get_main_frame" );
	static var _get_paste_target_list = x( "get_paste_target_list" );
	static var _get_progress = x( "get_progress" );
	static var _get_settings = x( "get_settings" );
	static var _get_title = x( "get_title" );
	static var _get_transparent = x( "get_transparent" );
	static var _get_uri = x( "get_uri" );
	static var _get_view_mode = x( "get_view_mode" );
	static var _get_view_source_mode = x( "get_view_source_mode" );
	static var _get_viewport_attributes = x( "get_viewport_attributes" );
	static var _get_zoom_level = x( "get_zoom_level" );
	
	static var _go_back = x( "go_back" );
	static var _go_back_or_forward = x( "go_back_or_forward", 1 );
	static var _go_forward = x( "go_forward" );
	static var _go_to_back_forward_item = x( "go_to_back_forward_item", 1 );
	static var _has_selection = x( "has_selection" );
	static var _load_html_string = x( "load_html_string", 2 );
	static var _load_request = x( "load_request" );
	static var _load_string = x( "load_string", 4 );
	static var _load_uri = x( "load_uri", 1 );
	static var _mark_text_matches = x( "mark_text_matches", 3 );
	static var _move_cursor = x( "move_cursor", 2 );
	static var _paste_clipboard = x( "paste_clipboard" );
	static var _redo = x( "redo" );
	static var _reload = x( "reload" );
	static var _reload_bypass_cache = x( "reload_bypass_cache" );
	static var _search_text = x( "search_text", 4 );
	static var _select_all = x( "select_all" );
	
	static var _set_custom_encoding = x( "set_custom_encoding", 1 );
	static var _set_editable = x( "set_editable", 1 );
	static var _set_full_content_zoom = x( "set_full_content_zoom", 1 );
	static var _set_highlight_text_matches = x( "set_highlight_text_matches", 1 );
	static var _set_maintains_back_forward_list = x( "set_maintains_back_forward_list", 1 );
	static var _set_settings = x( "set_settings", 1 );
	static var _set_transparent = x( "set_transparent", 1 );
	static var _set_view_mode = x( "set_view_mode", 1 );
	static var _set_view_source_mode = x( "set_view_source_mode", 1 );
	static var _set_zoom_level = x( "set_zoom_level", 1 );
	
	static var _stop_loading = x( "stop_loading" );
	static var _undo = x( "undo" );
	static var _unmark_text_matches = x( "unmark_text_matches" );
	static var _zoom_in = x( "zoom_in" );
	static var _zoom_out = x( "zoom_out" );
	
	static var _get_window_features = x( "get_window_features" );
	
	static inline function x( f : String, n : Int = 0 ) : Dynamic return webkit.Lib.load( "webview_"+f, 1+n )
		
}
