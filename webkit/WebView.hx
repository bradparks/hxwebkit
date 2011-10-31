package webkit;

class WebView {
	
	public var transparent(getTransparent,setTransparent) : Bool;
	public var canCopyClipboard(getCanCopyClipboard,null) : Bool;
	public var canCutClipboard(getCanCutClipboard,null) : Bool;
	public var canGoBack(getCanGoBack,null) : Bool;
	public var canGoForward(getCanGoForward,null) : Bool;
	public var canPasteClipboard(getCanPasteClipboard,null) : Bool;
	public var canRedo(getCanRedo,null) : Bool;
	public var canUndo(getCanUndo,null) : Bool;
	
	public var uri(getUri,null) : String;
	
	var __i : Void;
	
	public function new( win : gtk.Window ) {
		__i = _init( untyped win.__i );
	}
	
	inline function getTransparent() : Bool return _gettransparent(__i)
	inline function setTransparent( v : Bool ) : Bool return _settransparent(__i,v)
	inline function getUri() : String return _uri(__i)
	
	inline function getCanCopyClipboard() : Bool return _can_copy_clipboard(__i)
	inline function getCanCutClipboard() : Bool return _can_cut_clipboard(__i)
	inline function getCanGoBack() : Bool return _can_go_back(__i)
	inline function getCanGoForward() : Bool return _can_go_foward(__i)
	inline function getCanPasteClipboard() : Bool return _can_paste_clipboard(__i)
	inline function getCanRedo() : Bool return _can_copy_clipboard(__i)
	inline function getCanUndo() : Bool return _can_copy_clipboard(__i)
	
	public inline function canGoBackOrForward( steps : Int ) : Bool return _can_go_back_or_foward(__i,steps)
	public inline function canShowMimeType( mimetype : String ) : Bool return _can_go_back_or_foward(__i,untyped mimetype.__S)
	
	public inline function getSettings() : WebSettings return _getwebsettings(__i)
	public inline function setSettings( settings : WebSettings ) {
		_setwebsettings(__i,settings);
		return null;
	}
	public inline function setSetting( id : String, value : Dynamic ) {
		_setwebsetting(__i,untyped id.__s,value);
		//TODO
		return null;
	}
	public inline function loadHtmlFile( path : String ) loadString( neko.io.File.getContent("file://"+path) )
	public inline function loadString(t:String) _loadstring(__i,untyped t.__s)
	public inline function loadUri(t:String) _loaduri(__i,untyped t.__s)
	public inline function reload() _reload(__i)
	public inline function reloadBypassCache() _reloadbypasscache(__i)
	public inline function undo() _undo(__i)
	public inline function redo() _redo(__i)
	
	static var _init = x( "init" );
	
	static var _can_copy_clipboard = x( "can_copy_clipboard" );
	static var _can_cut_clipboard = x( "can_cut_clipboard" );
	static var _can_go_back = x( "can_go_back" );
	static var _can_go_back_or_foward = x( "can_go_back_or_foward", 1 );
	static var _can_go_foward = x( "can_go_foward" );
	static var _can_paste_clipboard = x( "can_paste_clipboard" );
	static var _can_go_redo = x( "can_go_redo" );
	static var _can_show_mimetype = x( "can_show_mimetype", 1 );
	static var _can_go_undo = x( "can_go_undo" );
	
	static var _getwebsettings = x( "getwebsettings" );
	static var _setwebsettings = x( "setwebsettings", 1 );
	static var _setwebsetting = x( "setwebsetting", 2 );
	
	static var _uri = x( "uri" );
	
	static var _gettransparent = x( "gettransparent" );
	static var _settransparent = x( "settransparent", 1 );
	static var _loadstring = x( "loadstring", 1);
	static var _loaduri = x( "loaduri", 1 );
	static var _reload = x( "reload" );
	static var _reloadbypasscache = x( "reloadbypasscache" );
	static var _undo = x( "undo" );
	static var _redo = x( "redo" );
	
	static inline function x( f : String, n : Int = 0 ) : Dynamic return webkit.Lib.load( "webview_"+f, 1+n )
		
}
