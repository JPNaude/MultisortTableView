#ifndef MULTISORTTREEVIEW_H
#define MULTISORTTREEVIEW_H

#include <QTreeView>

class AlphanumSortProxyModel;
class QIcon;


class MultisortTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit MultisortTreeView ( QWidget *parent = 0 );

    // Set icons to decorate sorted table headers
    void setSortIcons ( QIcon ascIcon, QIcon descIcon );
    // Set key modifier to handle multicolumn sorting
    void setModifier ( Qt::KeyboardModifier modifier );

    virtual void setSortingEnabled ( bool enable );
    virtual void setModel ( QAbstractItemModel *model );

private:
    // Sorting enable state
    bool m_isSortingEnabled;
    // ProxyModel to sorting columns
    AlphanumSortProxyModel *m_proxyModel;
    // Modifier to handle multicolumn sorting
    Qt::KeyboardModifier m_modifier;

private slots:
    void headerClicked ( int column );
};

#endif // MULTISORTTREEVIEW_H
