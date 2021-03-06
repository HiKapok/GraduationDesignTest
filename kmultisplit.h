#ifndef KMULTISPLIT_H
#define KMULTISPLIT_H

#include "kregion.h"
#include "gdal_priv.h"

#include <QString>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

#include <tuple>
#include <unordered_map>

class KMultiSplit
{
public:
    typedef enum {
        OutPic = 0,
        OutXML = 1,
    } K_OutTypes;
    typedef typename boost::property<boost::edge_weight_t, float> EdgeWeightProperty;
    typedef typename boost::property<boost::vertex_name_t, long> VertexIDProperty;
    // hash_setS,listS
    typedef typename boost::adjacency_list<boost::hash_setS, boost::hash_setS,boost::undirectedS,VertexIDProperty,EdgeWeightProperty> RAGraph;
    typedef typename boost::property_map<RAGraph,boost::edge_weight_t>::type weightMap;
    typedef typename boost::property_map<RAGraph,boost::vertex_name_t>::type indexMap;
    typedef typename boost::graph_traits<RAGraph>::edge_iterator edgeIterator;
    typedef typename boost::graph_traits<RAGraph>::vertex_iterator vertexIterator;
    ~KMultiSplit();
    KMultiSplit(QString,QString,QString,K_OutTypes=OutPic);
    void quickSplit(float);
    void runMultiSplit(float,float,float,bool=false,RAGraph::edges_size_type=5);
    void testXMLOutput();
    void testXMLInput();
private:
    QString m_sInput;
    QString m_sOutPut;
    QString m_sOutPutLabel;
    K_OutTypes m_tTypeOut;
    QString m_extName;
    GDALDriver *m_poDriver;
    int m_nBand;
    int m_iXSize;
    int m_iYSize;
    float *m_imgBuff;
    float **m_orgImgBuff;
    long *labels;
    float m_maxScale;
    float *m_adfMinMax;
    const int penWidth = 3;
    std::unordered_map<long,KRegion> m_mapRegion;
    RAGraph m_RAG;
    //float m_quickSplitThres;
    int getQuickColorMean(KRegion&,double *);
    float getQuickColorDiff(KRegion&,KRegion &);
    void saveSplit(QString);
    void buildRAG();
    inline bool isFloatEqual(float &a,float &b,float min=.1){ return std::fabs(a-b)<min; }
    void mergeIn(long&,long&);
    void mergeIn(RAGraph::edge_descriptor&);
    void mergeCurScale(float);
    int getColorVariance(KRegion&,float *);
    std::tuple<float,float> getMinArea(KRegion &, std::vector<std::tuple<int,int>>&);
    std::tuple<float,float,float,float,float,float> getRotateArea(std::vector<std::tuple<int,int>> &,float);
    RAGraph::vertex_descriptor getVertex(long);
    float getRegionDiff(KRegion&,KRegion &);
    std::tuple<float,float> getGraphScale();
    void testMinArea();
    void drawSquare(std::vector<std::tuple<int,int> > &,int = 0);
};

#endif // KMULTISPLIT_H
