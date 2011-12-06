/****************************************************************************
** GLWidget meta object code from reading C++ file 'glwidget.h'
**
** Created: Tue Dec 6 17:26:44 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "glwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GLWidget::className() const
{
    return "GLWidget";
}

QMetaObject *GLWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GLWidget( "GLWidget", &GLWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GLWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GLWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GLWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GLWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"GLWidget", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GLWidget.setMetaObject( metaObj );
    return metaObj;
}

void* GLWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GLWidget" ) )
	return this;
    return QGLWidget::qt_cast( clname );
}

bool GLWidget::qt_invoke( int _id, QUObject* _o )
{
    return QGLWidget::qt_invoke(_id,_o);
}

bool GLWidget::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool GLWidget::qt_property( int id, int f, QVariant* v)
{
    return QGLWidget::qt_property( id, f, v);
}

bool GLWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
