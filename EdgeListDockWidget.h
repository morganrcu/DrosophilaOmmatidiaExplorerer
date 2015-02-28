#ifndef EDGELISTDOCKWIDGET_H
#define EDGELISTDOCKWIDGET_H

#include <QDockWidget>
#include <AJGraph.h>
#include <AJVertex.h>
#include <QPoint>
namespace Ui {
class EdgeListDockWidget;
}

class EdgeListDockWidget : public QDockWidget
{
    Q_OBJECT

private:
    typedef AJGraph<AJVertex> EdgeContainer;
    typename EdgeContainer::Pointer m_EdgesContainer;

    typename std::map<int,typename EdgeContainer::AJEdgeHandler> m_RowToEdge;

public:
    explicit EdgeListDockWidget(QWidget *parent = 0);
    ~EdgeListDockWidget();

    inline void SetEdgesContainer(const  typename EdgeContainer::Pointer & edgesContainer){
        m_EdgesContainer=edgesContainer;
    }

    virtual void Draw();

    typename EdgeContainer::AJEdgeHandler GetSelectedEdge();
public slots:
    void slotEdgeTableSelectionChanged();
    void slotDisplayMenu(const QPoint &pos);
signals:
    void SelectedEdgeChanged(AJGraph<AJVertex>::AJEdgeHandler);
    void DrawEdgeRequested(AJGraph<AJVertex>::AJEdgeHandler);
private:
    Ui::EdgeListDockWidget *m_pUI;


};

#endif // EDGELISTDOCKWIDGET_H
