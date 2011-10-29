package webkit;

class Lib {
	
	public static inline function x( f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( "webkit", f, args );
		#elseif neko
		return neko.Lib.load( "webkit", f, args );
		#end
		//loadLib( "webkit", f, args );
	}
	
	/*
	public static inline function loadLib( id : String, f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( id, f, args );
		#elseif neko
		return neko.Lib.load( id, f, args );
		#end
	}
	*/
}
