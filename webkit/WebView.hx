package webkit;

class WebView {
	
	public var transparent(getTransparent,setTransparent) : Bool;
	public var uri(getUri,null) : String;
	
	var __i : Void;
	
	public function new( win : gtk.Window ) {
		__i = _init( untyped win.__i );
	}
	
	inline function getTransparent() : Bool return _gettransparent(__i)
	inline function setTransparent( v : Bool ) : Bool return _settransparent(__i,v)
	inline function getUri() : String return _uri(__i)
	
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
