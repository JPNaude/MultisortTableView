#include <QHeaderView>
#include <QIcon>
#include <QApplication>

#include "MultisortTreeView.h"
#include "AlphanumSortProxyModel.h"


MultisortTreeView::MultisortTreeView ( QWidget *parent ) :
    QTreeView ( parent )
{
    m_isSortingEnabled = false;
    m_proxyModel = new AlphanumSortProxyModel( this );
    m_modifier = Qt::ControlModifier;

    // Default icons
    setSortIcons( style()->standardIcon( QStyle::SP_ArrowUp ),
                  style()->standardIcon( QStyle::SP_ArrowDown ) );

    header()->setSectionsClickable(true);
    header()->setDefaultAlignment( Qt::AlignLeft );

    // Handler to sorting table
    connect( header(), SIGNAL(sectionClicked(int)),
             this,     SLOT(headerClicked(int)) );
}

// Set icons to decorate sorted table headers
void MultisortTreeView::setSortIcons ( QIcon ascIcon, QIcon descIcon )
{
    m_proxyModel->setSortIcons( ascIcon, descIcon );
}

// Set key modifier to handle multicolumn sorting
void MultisortTreeView::setModifier ( Qt::KeyboardModifier modifier )
{
    m_modifier = modifier;
}


// Reimplemented to self handling of sorting enable state
void MultisortTreeView::setSortingEnabled( bool enable )
{
    m_isSortingEnabled = enable;
}

// Reimplemented to use AlphanumSortProxyModel
void MultisortTreeView::setModel( QAbstractItemModel *model )
{
    if ( model ) {
        m_proxyModel->setSourceModel( model );
        QTreeView::setModel( m_proxyModel );
    }
}

// Handler to sort table
void MultisortTreeView::headerClicked ( int column )
{
    if ( m_isSortingEnabled ) {
        bool isModifierPressed = QApplication::keyboardModifiers() & m_modifier;
        m_proxyModel->sortColumn( column, isModifierPressed );
    }
}
