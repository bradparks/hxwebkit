package webkit;

class Lib {
	
	public static inline function x( f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( "webkit", "hxwebkit_"+f, args );
		#elseif neko
		return neko.Lib.load( "webkit", "hxwebkit_"+f, args );
		#end
	}

}
