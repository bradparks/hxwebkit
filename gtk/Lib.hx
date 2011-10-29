package gtk;

class Lib {

	static var _init = x( "init" );
	static var _run = x( "run" );
	static var _exit = x( "exit" );
	
	public static inline function init() : Bool return _init()
	public static inline function run() : Bool return _run()
	public static inline function exit() : Bool return _exit()
	
	public static inline function x( f : String, args : Int = 0 ) : Dynamic {
		#if cpp
		return cpp.Lib.load( "webkit", "_gtk_"+f, args );
		#elseif neko
		return neko.Lib.load( "webkit", "_gtk_"+f, args );
		#end
	}
	
}
