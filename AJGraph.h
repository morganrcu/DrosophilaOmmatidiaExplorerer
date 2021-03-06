#ifndef AJGRAPH_H
#define AJGRAPH_H

#include <itkDataObject.h>
#include <itkMacro.h>
#include <itkObjectFactory.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "FeatureDescriptor.h"
#include <itkArray.h>
template<class TAJVertex,class TAJEdge> class AJGraph : public itk::DataObject {


public:

    struct AJVertexPropertyTag {
        typedef boost::vertex_property_tag kind;
    };

    struct AJEdgePropertyTag {
                typedef boost::edge_property_tag kind;
    };

    typedef boost::property<AJVertexPropertyTag, typename TAJVertex::Pointer,

			boost::property<boost::vertex_index_t, int> >   VertexProperty;

    typedef boost::property<AJEdgePropertyTag,typename TAJEdge::Pointer,
    		boost::property<boost::edge_index_t,int,
			boost::property<boost::edge_weight_t,double>
    > > EdgeProperty;
public:
    typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS,VertexProperty,EdgeProperty,boost::no_property> BoostGraphType;
private:

    BoostGraphType m_Graph;
public:

    typedef AJGraph<TAJVertex,TAJEdge> Self;
    typedef itk::DataObject Superclass;
    typedef itk::SmartPointer<Self> Pointer;


    typedef TAJVertex AJVertexType;
    typedef TAJEdge AJEdgeType;


    typedef typename boost::graph_traits<BoostGraphType>::vertex_descriptor AJVertexHandler;
    typedef typename boost::graph_traits<BoostGraphType>::edge_descriptor AJEdgeHandler;

    typedef typename boost::graph_traits<BoostGraphType>::vertex_iterator VertexIterator;
    typedef typename boost::graph_traits<BoostGraphType>::edge_iterator EdgeIterator;

    typedef typename boost::graph_traits<BoostGraphType>::adjacency_iterator AdjacencyIterator;
    typedef typename boost::graph_traits<BoostGraphType>::out_edge_iterator OutEdgesIterator;
public:

    itkNewMacro(Self)

	BoostGraphType & GetBoostGraph(){
    	return m_Graph;
    }

    virtual  AJVertexHandler GetAJEdgeSource(const AJEdgeHandler & source){
        return boost::source(source,m_Graph);
    }

    virtual AJEdgeHandler GetAJEdgeHandler(const AJVertexHandler & source,const AJVertexHandler & target){
        return boost::edge(source,target,m_Graph).first;
    }

    virtual AJVertexHandler GetAJEdgeTarget(const AJEdgeHandler & target){
        return boost::target(target,m_Graph);
    }

    virtual typename AJVertexType::Pointer GetAJVertex(const AJVertexHandler & vertex){
        return boost::get(AJVertexPropertyTag(),m_Graph,vertex);

    }

    virtual int AJVertexDegree(const AJVertexHandler & vertex){
        return boost::degree(vertex,m_Graph);
    }

    virtual AdjacencyIterator AdjacentAJVerticesBegin(const AJVertexHandler & vertex){
        return boost::adjacent_vertices(vertex,m_Graph).first;
    }

    virtual AdjacencyIterator AdjacentAJVerticesEnd(const AJVertexHandler & vertex){
        return boost::adjacent_vertices(vertex,m_Graph).second;
    }

    virtual AJVertexHandler AddAJVertex(const typename AJVertexType::Pointer & vertex){

        AJVertexHandler result=boost::add_vertex(m_Graph);

        boost::get(AJVertexPropertyTag(),m_Graph,result)=vertex;
        return result;

    }
    virtual void DeleteAJVertex(const AJVertexHandler & vertex){
        boost::clear_vertex(vertex,m_Graph);
        boost::remove_vertex(vertex,m_Graph);
    }

    virtual void DeleteAJEdge(const AJEdgeHandler & edge){
        boost::remove_edge(edge,m_Graph);
    }


    virtual AJEdgeHandler AddAJEdge(const AJVertexHandler & a, const AJVertexHandler & b){
        AJEdgeHandler result= boost::add_edge(a,b,m_Graph).first;
        boost::get(AJEdgePropertyTag(),m_Graph,result)=AJEdgeType::New();
        return result;
    }

    virtual typename AJEdgeType::Pointer GetAJEdge(const AJEdgeHandler & edge){
    	return boost::get(AJEdgePropertyTag(),m_Graph,edge);
    }

    unsigned long GetNumVertices(){
        return boost::num_vertices(m_Graph);
    }

    unsigned long GetNumEdges(){
        return boost::num_edges(m_Graph);
    }

    EdgeIterator EdgesBegin(){
        return boost::edges(m_Graph).first;
    }


    EdgeIterator EdgesEnd(){
        return boost::edges(m_Graph).second;
    }

    VertexIterator VerticesBegin(){
        return boost::vertices(m_Graph).first;
    }

    VertexIterator VerticesEnd(){
        return boost::vertices(m_Graph).second;
    }

    OutEdgesIterator BeginOutEdges( const AJVertexHandler & vertex){
    	return boost::out_edges(vertex,m_Graph).first;
    }

    OutEdgesIterator EndOutEdges( const AJVertexHandler & vertex){
    	return boost::out_edges(vertex,m_Graph).second;
    }

protected:
    AJGraph(){

    }

};

#endif // AJGRAPH_H
