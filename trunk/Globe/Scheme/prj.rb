
require 'mxx_ru/cpp/qt5'

Mxx_ru::Cpp::lib_target {

	rtl_mode( Mxx_ru::Cpp::RTL_SHARED )
	rtti_mode( Mxx_ru::Cpp::RTTI_ENABLED )
	threading_mode( Mxx_ru::Cpp::THREADING_MULTI )

    required_prj( 'Como/prj.rb' )

	target( 'lib/Globe.Scheme' )
	
	qt = generator( MxxRu::Cpp::Qt5.new( self ) )
	qt.use_modules( QT_GUI, QT_WIDGETS, QT_SQL, QT_NETWORK )
	
	qt.ui( 'size_dialog.ui' )
	qt.ui( 'text_dialog.ui' )
	
	qt.qrc2cpp( 'scheme_resources.qrc' )
	
	qt.h2moc( 'scene.hpp' )
	qt.h2moc( 'size_dialog.hpp' )
	qt.h2moc( 'source.hpp' )
	qt.h2moc( 'text.hpp' )
	qt.h2moc( 'text_dialog.hpp' )
	qt.h2moc( 'view.hpp' )
	qt.h2moc( 'window.hpp' )

	cpp_source( 'item_base_cfg.cpp' )
	cpp_source( 'mm_pixels.cpp' )
	cpp_source( 'scene.cpp' )
	cpp_source( 'scheme_cfg.cpp' )
	cpp_source( 'selection.cpp' )
	cpp_source( 'size_dialog.cpp' )
	cpp_source( 'source.cpp' )
	cpp_source( 'source_cfg.cpp' )
	cpp_source( 'text.cpp' )
	cpp_source( 'text_cfg.cpp' )
	cpp_source( 'text_dialog.cpp' )
	cpp_source( 'view.cpp' )
	cpp_source( 'window.cpp' )
	cpp_source( 'window_cfg.cpp' )
}
