
require 'mxx_ru/cpp/qt5'

Mxx_ru::Cpp::exe_target {

	rtl_mode( Mxx_ru::Cpp::RTL_SHARED )
	rtti_mode( Mxx_ru::Cpp::RTTI_ENABLED )
	threading_mode( Mxx_ru::Cpp::THREADING_MULTI )

	required_prj( 'Globe/Core/prj.rb' )
	required_prj( 'Globe/Scheme/prj.rb' )
	
	target( "Globe" )

	screen_mode( Mxx_ru::Cpp::SCREEN_WINDOW )
	
	if 'mswin' == toolset.tag( 'target_os' )
        mswin_rc_file( 'globe.rc' )
	end

	qt = generator( MxxRu::Cpp::Qt5.new( self ) )
	qt.use_modules( QT_GUI, QT_NETWORK, QT_SQL, QT_WIDGETS, QT_MULTIMEDIA )

	qt.lib_qtmain

	qt.qrc2cpp( '../Core/resources.qrc' )
	qt.qrc2cpp( '../Scheme/scheme_resources.qrc' )

	cpp_source( 'main.cpp' )
}
