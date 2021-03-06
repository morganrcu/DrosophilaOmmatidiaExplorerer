#ifndef VERTEXLISTDOCKWIDGET_H
#define VERTEXLISTDOCKWIDGET_H

#include <QDockWidget>
#include "AJGraph.h"
#include "AJVertex.h"
#include "AJEdge.h"
#include "OmmatidiaTissue.h"
namespace Ui {
class VertexListDockWidget;
}

class VertexListDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    typedef OmmatidiaTissue<3>::AJGraphType VertexContainer;
private:

     VertexContainer::Pointer m_VertexContainer;
public:
    explicit VertexListDockWidget(QWidget *parent = 0);
    ~VertexListDockWidget();
    virtual void Draw();

    virtual VertexContainer::AJVertexHandler GetSelectedVertex();
    virtual void SetSelectedVertex(const VertexContainer::AJVertexHandler &);
    virtual void ClearSelection();

    inline void SetVertexContainer(const   VertexContainer::Pointer & vertexContainer){
        m_VertexContainer=vertexContainer;
    }
public slots:
    void slotVertexTableSelectionChanged();
signals:
    void SelectedVertexChanged(VertexContainer::AJVertexHandler);

private:
    Ui::VertexListDockWidget *m_pUI;
};

#endif // VERTEXLISTDOCKWIDGET_H
