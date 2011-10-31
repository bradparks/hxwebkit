package webkit;

class Lib {
	
	public static inline var VERSION = "0.1";
	
	public static function init() {
		//_set_handler_window_close( cb );
		_set_hxr_handler( hxr_cb );
		//_javasctip_init();
	}
	
	public static function remoting_neko2js(t:String) {
		_javascript_hxr( untyped t.__s );
	}
	
	static function hxr_cb( t : String ) {
		trace( "Recieved from javascript:"+t );
	}

	static var _set_hxr_handler = load( "set_hxr_handler", 1 );
	//static var _javasctip_init = x( "javasctip_init", 1 );
	static var _javascript_hxr = load( "javascript_hxr", 1 );
	
	public static inline function load( f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( "webkit", "hxwebkit_"+f, args );
		#elseif neko
		return neko.Lib.load( "webkit", "hxwebkit_"+f, args );
		#end
	}

}
