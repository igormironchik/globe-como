
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2012 - 2013 Igor Mironchik

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GLOBE__PROPERTIES_WIDGET_MODEL_HPP__INCLUDED
#define GLOBE__PROPERTIES_WIDGET_MODEL_HPP__INCLUDED

// Qt include.
#include <QtCore/QAbstractTableModel>
#include <QtCore/QScopedPointer>

// Globe include.
#include <Globe/properties.hpp>


namespace Globe {

//
// PropertiesListModel
//

class PropertiesListModelPrivate;

//! Model with Como::Source sources.
class PropertiesListModel
	:	public QAbstractTableModel
{
	Q_OBJECT

signals:
	//! Wrong properties.
	void wrongProperties();
	//! Changed.
	void changed();

public:
	explicit PropertiesListModel( Como::Source::Type valueType,
		QObject * parent = 0 );
	~PropertiesListModel();

	//! \return Properties.
	Properties properties() const;
	//! Init model with the properties.
	void setProperties( const Properties & props );

	//! Clear model.
	void clear();

	//! \return Is otherwise condition exists?
	bool isOtherwiseConditionExists() const;

	//! Add condition.
	void addCondition();
	//! Add otherwise condition.
	void addOtherwiseCondition();
	//! Remove condition. \return Is operation completed successfully?
	bool removeCondition( int row );
	//! Move condition up. \return Is operation completed successfully?
	bool moveConditionUp( int row );
	//! Move condition down. \return Is operation completed successfully?
	bool moveConditionDown( int row );

	//! \return Count of the rows.
	int rowCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Count of the columns.
	int columnCount( const QModelIndex & parent = QModelIndex() ) const;
	//! \return Data by the given index and role.
	QVariant data( const QModelIndex & index,
		int role = Qt::DisplayRole ) const;
	//! Insert rows to the model.
	bool insertRows( int row, int count,
		const QModelIndex & parent = QModelIndex() );
	//! Remove rows from the model.
	bool removeRows( int row, int count,
		const QModelIndex & parent = QModelIndex() );
	//! Set data.
	bool setData( const QModelIndex & index, const QVariant & value,
		int role = Qt::EditRole );
	//! \return Flags.
	Qt::ItemFlags flags( const QModelIndex & index ) const;
	//! \return Header data.
	QVariant headerData( int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole ) const;

private:
	Q_DISABLE_COPY( PropertiesListModel )

	QScopedPointer< PropertiesListModelPrivate > d;
}; // class PropertiesListModel

} /* namespace Globe */

#endif // GLOBE__PROPERTIES_WIDGET_MODEL_HPP__INCLUDED
