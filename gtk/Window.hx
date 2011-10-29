package gtk;

/**
	GTK window
*/
class Window {
	
	public dynamic function onClose() {}
	
	public var active(getActive,null) : Bool;
	public var title(getTitle,setTitle) : String;
	public var resizeable(getResizeable,setResizeable) : Bool;
	public var opacity(getOpacity,setOpacity) : Float;
	//public var screen(getScreen,setScreen) : Screen; //TODO
	public var hasTopLevelFocus(getHasTopLevelFocus,null) : Bool; //TODO
	//public var topLevelList(getHasTopLevelFocus,null) : List<WindowInfo>; //TODO
	public var decorated(getDecorated,setDecorated) : Bool;
	public var deletable(getDeleteable,setDeleteable) : Bool;
	//public var typeHint(getTypeHint,setTypeHint) : WindowTypeHint; //TODO
	//public var taskbarHint(getTaskbarHint,setTaskbarHint) : Bool; //TODO
	//public var skipPagerHint(getSkipPagerHint,setSkipPagerHint) : Bool; //TODO
	//public var urgentHint(getUrgentHint,setUrgentHint) : Bool; //TODO
	//public var acceptFocus(getAcceptFocus,setAcceptFocus) : Bool; //TODO
	//public var setFocusOnMap(getSetFocusOnMap,setSetFocusOnMap) : Bool; //TODO
	//..........
	//............
	
	var __i : Void;
	var _decorated : Bool;
	var _deletable : Bool;
	
	public function new( title : String, w : Int = 600, h : Int = 400 ) {
		__i = _init( untyped title.__s, w, h, handleClose );
		_decorated = _deletable = true;
	}
	
	inline function handleClose() onClose()
	
	inline function getActive() : Bool return _active(__i)
	inline function getTitle() : String return _gettitle(__i)
	inline function setTitle(t:String) return _settitle(__i,untyped t.__s)
	inline function getResizeable() : Bool return _getresizeable(__i)
	inline function setResizeable(v:Bool) : Bool {
		var r : Bool = _setresizeable(__i,v);
		return r; //(_setresizeable(__i,v)==1) ? true : false
	}
	/*
	inline function getResizeable() : Bool return (_getresizeable(__i)==1) ? true : false
	inline function setResizeable(v:Bool) : Bool {
		var r : Bool = _setresizeable(__i,v);
		trace("RRRRRRRRRRRRRRRRRR "+r );
	
		return r;//(_setresizeable(__i,v)==1) ? true : false
	}
	*/
	
	inline function getOpacity() : Float return _getopacity(__i)
	inline function setOpacity(v:Float) return _setopacity(__i,v)
	inline function getHasTopLevelFocus() : Bool return _gethastoplevelfocus(__i)
	inline function getDecorated() : Bool return _decorated
	inline function setDecorated(v:Bool) : Bool {
		_setdecorated(__i,v);
		return _decorated = v;
	}
	inline function getDeleteable() : Bool return _deletable
	inline function setDeleteable(v:Bool) : Bool {
		_setdeletable(__i,v);
		return _deletable = v;
	}
	
	//TODO
	/*
	public inline function getPosition() : WindowPosition {
		_getposition(__i);
		return null;
	}
	*/
	public inline function setPosition(p:WindowPosition) : WindowPosition {
		_setposition( __i, Type.enumIndex(p) );
		return p;
	}
	
	public inline function maximize() _maximize(__i)
	public inline function unmaximize() _unmaximize(__i)
	public inline function fullscreen() _fullscreen(__i)
	public inline function unfullscreen() _unfullscreen(__i)
	public inline function resize(w:Int,h:Int) _resize(__i,w,h)
	public inline function iconify() _iconify(__i)
	public inline function deiconify() _deiconify(__i)
	public inline function present(?timestamp:Int=-1) _present(__i,timestamp)
	//TODO public inline function stick() _stick(__i)
	//TODO public inline function unstick() _stick(__i)
	public inline function setKeepAbove(v:Bool) _setkeepabove(__i,v)
	public inline function setKeepBelow(v:Bool) _setkeepbelow(__i,v)
	public inline function move(x:Int,y:Int) _move(__i,x,y)
	
	static var _init = x( "init", 4 );
	static var _active = x( "active", 1 );
	static var _gettitle = x( "gettitle", 1 );
	static var _settitle = x( "settitle", 2 );
	static var _getresizeable = x( "getresizeable", 1 );
	static var _setresizeable = x( "setresizeable", 2 );
	static var _getopacity = x( "getopacity", 1 );
	static var _setopacity = x( "setopacity", 2 );
	static var _gethastoplevelfocus = x( "gethastoplevelfocus", 1 );
	//static var _getposition = x( "getposition", 1 );
	static var _setposition = x( "setposition", 2 );
	static var _maximize = x( "maximize", 1 );
	static var _unmaximize = x( "unmaximize", 1 );
	static var _fullscreen = x( "fullscreen", 1 );
	static var _unfullscreen = x( "unfullscreen", 1 );
	static var _resize = x( "resize", 3 );
	static var _iconify = x( "iconify", 1 );
	static var _deiconify = x( "deiconify", 1 );
	static var _present = x( "present", 2 );
	static var _setkeepabove = x( "setkeepabove", 2 );
	static var _setkeepbelow = x( "setkeepbelow", 2 );
	static var _setdecorated = x( "setdecorated", 2 );
	static var _setdeletable = x( "setdeleteable", 2 );
	static var _move = x( "move", 3 );
	
	static inline function x( f : String, n : Int = 0 ) : Dynamic return webkit.Lib.x( "window_"+f, n ) //TODO 1+n

}
