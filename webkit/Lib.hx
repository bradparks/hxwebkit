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
	
	#if DEBUG_WEBKIT
	
	public static function printWebViewProperties( view : WebView ) {
	
		neko.Lib.println( "  WebView properties:" );
		
		neko.Lib.println( "    canCopyClipboard : "+view.canCopyClipboard );
		neko.Lib.println( "    canCopyClipboard : "+view.canCopyClipboard );
		neko.Lib.println( "    canCutClipboard : "+view.canCutClipboard );
		neko.Lib.println( "    canGoBack : "+view.canGoBack );
		neko.Lib.println( "    canGoForward : "+view.canGoForward );
		neko.Lib.println( "    canPasteClipboard: "+view.canPasteClipboard );
		neko.Lib.println( "    canRedo : "+view.canRedo );
		neko.Lib.println( "    canUndo : "+view.canUndo );
		neko.Lib.println( "    canShowMimeType [application/png] : "+view.canShowMimeType("application/png") );
		//neko.Lib.println( "    getBackForwardList : "+view.getBackForwardList() );
		//neko.Lib.println( "    getCopyTargetList : "+view.getCopyTargetList() );
		neko.Lib.println( "    customEncoding : "+view.customEncoding );
		//neko.Lib.println( "    domDocument : "+view.domDocument( );
		neko.Lib.println( "    editable : "+view.editable );
		neko.Lib.println( "    encoding : "+view.encoding );
		//neko.Lib.println( "    focusedFrame : "+view.focusedFrame );
		neko.Lib.println( "    fullContentZoom : "+view.fullContentZoom );
		//hit_test
		neko.Lib.println( "    iconURI : "+view.iconURI );
		//inspector
		neko.Lib.println( "    loadStatus : "+view.loadStatus );
		//neko.Lib.println( "    mainFrame : "+view.mainFrame );
		//neko.Lib.println( "    pasteTargetList : "+view.pasteTargetList );
		neko.Lib.println( "    progress : "+view.progress );
		//settings
		neko.Lib.println( "    title : "+view.title );
		neko.Lib.println( "    transparent : "+view.transparent );
		neko.Lib.println( "    uri : "+view.uri );
		neko.Lib.println( "    viewMode : "+view.viewMode );
		neko.Lib.println( "    viewSourceMode : "+view.viewSourceMode );
		neko.Lib.println( "    viewportAttributes : "+view.viewportAttributes );
		neko.Lib.println( "    zoomLevel : "+view.zoomLevel );
		neko.Lib.println( "    hasSelection : "+view.hasSelection );
		neko.Lib.println( "    windowFeatures : "+view.windowFeatures );
	}
	
	public static function printWebViewSettings( view : WebView ) {
		neko.Lib.println( "  WebView settings:" );
		var settings = view.getSettings();
		for( f in Reflect.fields( settings ) ) { neko.Lib.println( "    "+f+" : "+Reflect.field(settings,f) ); }
	}
	
	//static inline function printProperty( view : webkit.WebView, f : String ) neko.Lib.println( "    "+f+" : "+Reflect.field( view, f ) )
	
	#end
	
}
