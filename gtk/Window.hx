package gtk;

/**
	Gtk window
*/
class Window {
	
	public dynamic function onClose() {}
	
	public var active(getActive,null) : Bool;
	public var title(getTitle,setTitle) : String;
	public var resizeable(getResizeable,setResizeable) : Bool;
	public var opacity(getOpacity,setOpacity) : Float;
	
	var __i : Void;
	
	public function new( title : String, w : Int = 600, h : Int = 400 ) {
		__i = _init( untyped title.__s, w, h );
	}
	
	inline function getActive() : Bool return _active(__i)
	inline function getTitle() : String return _gettitle(__i)
	inline function setTitle(t:String) return _settitle(__i,untyped t.__s)
	inline function getResizeable() : Bool return _getresizeable(__i)
	inline function setResizeable(v:Bool) : Bool return _setresizeable(__i,v)
	inline function getOpacity() : Float return _getopacity(__i)
	inline function setOpacity(v:Float) return _setopacity(__i,v)
	
	//public inline function getPosition() : Int return _getposition(__i)
	//public inline function setPosition(p:Int) _setposition(__i,p)
	public inline function maximize() _maximize(__i)
	public inline function unmaximize() _unmaximize(__i)
	public inline function fullscreen() _fullscreen(__i)
	public inline function unfullscreen() _unfullscreen(__i)
	public inline function resize(w:Int,h:Int) _resize(__i,w,h)
	
	static var _init = x( "init", 3 );
	static var _active = x( "active", 1 );
	static var _gettitle = x( "gettitle", 1 );
	static var _settitle = x( "settitle", 2 );
	static var _getresizeable = x( "getresizeable", 1 );
	static var _setresizeable = x( "setresizeable", 2 );
	static var _getopacity = x( "getopacity", 1 );
	static var _setopacity = x( "setopacity", 2 );
	//static var _getposition = x( "getposition", 1 );
	//static var _setposition = x( "setposition", 2 );
	static var _maximize = x( "maximize", 1 );
	static var _unmaximize = x( "unmaximize", 1 );
	static var _fullscreen = x( "fullscreen", 1 );
	static var _unfullscreen = x( "unfullscreen", 1 );
	static var _resize = x( "resize", 3 );
	
	static inline function x( f : String, n : Int = 0 ) : Dynamic return webkit.Lib.x( "window_"+f, n )

}
