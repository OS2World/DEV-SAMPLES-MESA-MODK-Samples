/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994                               *
 *                     Athena Design, Inc.                                *
 *                                                                        *
 *                                                                        *
 *                ALL RIGHTS RESERVED                                     *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 **************************************************************************/

#ifndef _MH_grXf

#define _MH_grXf

#include "range.h"
#include "color.h"
#include "graphel.h"
#include "rect.h"
#include "object.h"

class MFrameXfer : public MObject
{
    public:
    MFrameXfer();
    virtual void copyFrom(const MFrameXfer *);
    virtual ~MFrameXfer();
    
    virtual int getFrameClass() const {return frameClass;};
    virtual void setFrameClass(int i) {frameClass = i;};
    virtual int isChartClass() const {if (frameClass < 100) return 1; return 0;};
    virtual int isShapeClass() const
    {
        if (frameClass >= 200 && frameClass < 300) return 1;
        return 0;
    };
    virtual int isImageClass() const
    {
        if (frameClass >= 100 && frameClass < 200) return 1;
        return 0;
    };
    
    virtual void setNoMerge();
    
    virtual void setAnchor(const MAddress *ad) {anchor = *ad; mergeAnchor = 1;};
    virtual const MAddress *getAnchor() const {return &anchor;};
    virtual int getMergeAnchor() const {return mergeAnchor;};
    
    virtual int getFrameSize() const {return frameSize;};
    virtual int getMergeFrameSize() const {return mergeFrameSize;};
    virtual void setFrameSize(int i) {frameSize = i; mergeFrameSize = 1;};
    
    virtual void setPos(const MRect *re) {pos = *re; mergePos = 1;};
    virtual const MRect *getPos() const {return &pos;};
    virtual int getMergePos() const {return mergePos;};
    
    virtual void setOrder(int i) {order = i; mergeOrder = 1;};
    virtual int getOrder() const {return order;};
    virtual int getMergeOrder() const {return mergeOrder;};
    
    virtual void setName(const char *);
    virtual const char *getName() const {return name;};
    virtual int getMergeName() const {return mergeName;};
    
    virtual void setScript(const char *);
    virtual const char *getScript() const {return script;};
    virtual int getMergeScript() const {return mergeScript;};
    
    
    virtual const MRange *getRange() const {return &theData;};
    virtual int getMergeRange() const {return mergeRange;};
    virtual void setRange(const MRange *ra) {theData = *ra; mergeRange = 1;};

    virtual void setBkgColor(const MColor *c) {bkgColor = *c; mergeBkgColor = 1;};
    virtual void setFrameColor(const MColor *c) {frameColor = *c; mergeFrameColor = 1;};
    virtual void setLegendPosition(int i) {legendPosition = i; mergeLegendPosition = 1;};
    virtual void setLegendInfo(const MGraphElement *ge) {legendInfo.free();
        legendInfo.init(ge); mergeLegendInfo = 1;};
    virtual void setTitles(int,const char *);
    virtual void setTitleInfo(int x,const MGraphElement *ge)
        {titleInfo[x].free();
            titleInfo[x].init(ge); mergeTitleInfo[x] = 1;};
    virtual void setOrientation(int i) {orientation = i; mergeOrient = 1;};
    virtual void setXAutoScale(int i) {xautoScale = i; mergeXAuto = 1;};
    virtual void setYAutoScale(int i) {yautoScale = i; mergeYAuto = 1;};
    virtual void setXLogScale(int i) {xlogScale = i; mergeXLog = 1;};
    virtual void setYLogScale(int i) {ylogScale = i; mergeYLog = 1;};
    virtual void setXAxisRot(int i) {xAxisRot = i; mergeXAxisRot = 1;};
    virtual void setYAxisRot(int i) {yAxisRot = i; mergeYAxisRot = 1;};
    virtual void setMinX(double d) {minX = d; mergeScale = 1;};
    virtual void setMinY(double d) {minY = d; mergeScale = 1;};
    virtual void setMaxX(double d) {maxX = d; mergeScale = 1;};
    virtual void setMaxY(double d) {maxY = d; mergeScale = 1;};
    virtual void setDisplayFormat(int n,int df) {displayFormat[n] = df; mergeDispForm = 1;};
    virtual void setTopTitles(int i) {topTitles = i; mergeTopTitles = 1;};
    virtual void setSideTitles(int i) {sideTitles = i; mergeSideTitles = 1;};
    virtual void setWallCol(const MColor *c) {wallCol = *c; mergeWallCol = 1;};
    virtual void setXRot(int i) {xRot = i; mergeXRot = 1;};
    virtual void setYRot(int i) {yRot = i; mergeYRot = 1;};
    virtual void setWireFrame(int i) {wireFrame = i; mergeWireFrame = 1;};
    virtual void setXMajorTicks(int i) {xMajorTicks = i; mergeXMajorTicks = 1;};
    virtual void setYMajorTicks(int i) {yMajorTicks = i; mergeYMajorTicks = 1;};
    virtual void setXMinorTicks(int i) {xMinorTicks = i; mergeXMinorTicks = 1;};
    virtual void setYMinorTicks(int i) {yMinorTicks = i; mergeYMinorTicks = 1;};
    virtual void setXAxisLoc(int i) {xAxisLoc = i; mergeXAxisLoc = 1;};
    virtual void setYAxisLoc(int i) {yAxisLoc = i; mergeYAxisLoc = 1;};
    virtual void setXMajorGrid(int i) {xMajorGrid = i; mergeXMajorGrid = 1;};
    virtual void setYMajorGrid(int i) {yMajorGrid = i; mergeYMajorGrid = 1;};
    virtual void setXMinorGrid(int i) {xMinorGrid = i; mergeXMinorGrid = 1;};
    virtual void setYMinorGrid(int i) {yMinorGrid = i; mergeYMinorGrid = 1;};
    virtual void setGraphBorder(int i) {graphBorder = i; mergeGraphBorder = 1;};
    virtual void setXGridCol(const MColor *c) {xGridCol = *c; mergeXGridCol = 1;};
    virtual void setYGridCol(const MColor *c) {yGridCol = *c; mergeYGridCol = 1;};
    virtual void setBorderCol(const MColor *c) {borderCol = *c; mergeBorderCol = 1;};
    virtual void setLineWid(int i) {lineWid = i; mergeLineWid = 1;};
    virtual void setBarColWid(int i) {barColWid = i; mergeBarColWid = 1;};
    virtual void setShowPoint(int i) {showPoint = i; mergeShowPoint = 1;};
    virtual void setShowLine(int i) {showLine = i; mergeShowLine = 1;};
    virtual void setXMajTickSize(int i) {xMajTickSize = i; mergeXMajTickSize = 1;};
    virtual void setYMajTickSize(int i) {yMajTickSize = i; mergeYMajTickSize = 1;};
    virtual void setXMinTickSize(int i) {xMinTickSize = i; mergeXMinTickSize = 1;};
    virtual void setYMinTickSize(int i) {yMinTickSize = i; mergeYMinTickSize = 1;};
    virtual void setSingleXRange(int i) {singleXRange = i; mergeSingleXRange = 1;};
    virtual void setGraphElements(int,const MGraphElement *);
    virtual void setAxisInfo(const MGraphElement *ge) 
        {axisInfo.free(); axisInfo.init(ge); mergeAxisInfo = 1;};

    virtual int getMergeBkgColor() const {return mergeBkgColor;};
    virtual const MColor *getBkgColor() const {return &bkgColor;};
        
    virtual int getMergeFrameColor() const {return mergeFrameColor;};
    
    virtual const MColor *getFrameColor() const {return &frameColor;};
            
    virtual int getMergeLegendPosition() const {return mergeLegendPosition;};
    virtual int getLegendPosition() const {return legendPosition;};
        
    virtual int getMergeLegendInfo() const {return mergeLegendInfo;};
    virtual const MGraphElement *getLegendInfo() const {return &legendInfo;};
    virtual int getMergeTitles(int x) const {return mergeTitles[x];};
    virtual const char *getTitles(int x) const {return titles[x];};
    virtual int getMergeTitleInfo(int x) const {return mergeTitleInfo[x];};
    virtual const MGraphElement *getTitleInfo(int x) const {return &titleInfo[x];};
    
    virtual int getMergeOrientation() const {return mergeOrient;};
    virtual int getOrientation() const {return orientation;};
        
    virtual int getMergeXAutoScale() const {return mergeXAuto;};
    virtual int getMergeYAutoScale() const {return mergeYAuto;};
    virtual int getXAutoScale() const {return xautoScale;};
    virtual int getYAutoScale() const {return yautoScale;};
            
    virtual int getMergeXLogScale() const {return mergeXLog;};
    virtual int getMergeYLogScale() const {return mergeYLog;};
    virtual int getXLogScale() const {return xlogScale;};
    virtual int getYLogScale() const {return ylogScale;};
    
    virtual int getMergeXAxisRot() const {return mergeXAxisRot;};
    virtual int getXAxisRot() const {return xAxisRot;};
    virtual int getMergeYAxisRot() const {return mergeYAxisRot;};
    virtual int getYAxisRot() const {return yAxisRot;};
            
    virtual int getMergeScale() const {return mergeScale;};
    
    virtual double getMinX() const {return minX;};
    virtual double getMinY() const {return minY;};
    virtual double getMaxX() const {return maxX;};
    virtual double getMaxY() const {return maxY;};
        
    virtual int getMergeDisplayFormat() const {return mergeDispForm;};
    virtual int getDisplayFormat(int i) const {return displayFormat[i];};
    
    virtual int getMergeTopTitles() const {return mergeTopTitles;};
    virtual int getTopTitles() const {return topTitles;};
            
    virtual int getMergeSideTitles() const {return mergeSideTitles;};
    virtual int getSideTitles() const {return sideTitles;};
            
    virtual int getMergeWallCol() const {return mergeWallCol;};
    virtual const MColor *getWallCol() const {return &wallCol;};
        
    virtual int getMergeXRot() const {return mergeXRot;};
    virtual int getXRot() const {return xRot;};
            
    virtual int getMergeYRot() const {return mergeYRot;};
    virtual int getYRot() const {return yRot;};
            
    virtual int getMergeWireFrame() const {return mergeWireFrame;};
    virtual int getWireFrame() const {return wireFrame;};
            
    virtual int getMergeXMajorTicks() const {return mergeXMajorTicks;};
    virtual int getXMajorTicks() const {return xMajorTicks;};
            
    virtual int getMergeYMajorTicks() const {return mergeYMajorTicks;};
    virtual int getYMajorTicks() const {return yMajorTicks;};
            
    virtual int getMergeXMinorTicks() const {return mergeXMinorTicks;};
    virtual int getXMinorTicks()const {return xMinorTicks;};
            
    virtual int getMergeYMinorTicks() const {return mergeYMinorTicks;};
    virtual int getYMinorTicks() const {return yMinorTicks;};
            
    virtual int getMergeXAxisLoc() const {return mergeXAxisLoc;};
    virtual int getXAxisLoc() const {return xAxisLoc;};
            
    virtual int getMergeYAxisLoc() const {return mergeYAxisLoc;};
    virtual int getYAxisLoc()const {return yAxisLoc;};
            
    virtual int getMergeXMajorGrid() const {return mergeXMajorGrid;};
    virtual int getXMajorGrid() const {return xMajorGrid;};
            
    virtual int getMergeYMajorGrid() const {return mergeYMajorGrid;};
    virtual int getYMajorGrid() const {return yMajorGrid;};
    
        
    virtual int getMergeXMinorGrid() const {return mergeXMinorGrid;};
    virtual int getXMinorGrid() const {return xMinorGrid;};
            
    virtual int getMergeYMinorGrid() const {return mergeYMinorGrid;};
    virtual int getYMinorGrid() const {return yMinorGrid;};
        
    virtual int getMergeGraphBorder() const {return mergeGraphBorder;};
    virtual int getGraphBorder() const {return graphBorder;};
            
    virtual int getMergeXGridCol() const {return mergeXGridCol;};
    virtual const MColor *getXGridCol() const {return &xGridCol;};
        
    virtual int getMergeYGridCol() const {return mergeYGridCol;};
    virtual const MColor *getYGridCol() const {return &yGridCol;};

    virtual int getMergeBorderCol() const {return mergeBorderCol;};
    virtual const MColor *getBorderCol() const {return &borderCol;};
        
    virtual int getMergeLineWid() const {return mergeLineWid;};
    virtual int getLineWid() const {return lineWid;};
            
    virtual int getMergeBarColWid() const {return mergeBarColWid;};
    virtual int getBarColWid() const {return barColWid;};
            
    virtual int getMergeShowPoint() const {return mergeShowPoint;};
    virtual int getShowPoint() const {return showPoint;};
            
    virtual int getMergeShowLine() const {return mergeShowLine;};
    virtual int getShowLine() const {return showLine;};
            
    virtual int getMergeXMajTickSize() const {return mergeXMajTickSize;};
    virtual int getXMajTickSize() const {return xMajTickSize;};
    
    virtual int getMergeYMajTickSize() const {return mergeYMajTickSize;};
    virtual int getYMajTickSize() const {return yMajTickSize;};
            
    virtual int getMergeXMinTickSize() const {return mergeXMinTickSize;};
    virtual int getXMinTickSize() const {return xMinTickSize;};
            
    virtual int getMergeYMinTickSize() const {return mergeYMinTickSize;};
    virtual int getYMinTickSize() const {return yMinTickSize;};
        
    virtual int getMergeSingleXRange() const {return mergeSingleXRange;};
    virtual int getSingleXRange() const {return singleXRange;};
            
    virtual int getMergeAxisInfo() const {return mergeAxisInfo;};
    virtual const MGraphElement * getAxisInfo() const {return &axisInfo;};
            
    virtual int getMergeElements() const {return mergeElements;};
    virtual int getNumElements() const {return numElements;};
    virtual MGraphElement *getGraphElements() const;
    
    private:
    int frameClass;
    
    virtual MFrameXfer &operator=(const MFrameXfer &) {return *this;};
    
    MAddress anchor;
    
    MRect pos;
    
    int order;
    
    char *name;
    
    char *script;
    
    MRange theData;

    MColor bkgColor,frameColor;
    
    int frameSize;
    
    int legendPosition;                // where do we put the legend?
    
    MGraphElement legendInfo;        // get info for the legend
    
    char *titles[4];                // the x, y, first, and second titles
    MGraphElement titleInfo[4];        // display format of the title
        
    // some variables that describe the data...
    int orientation;                // is the data oriented by row or column
    
    int xautoScale;                    // are we scaling ourselves based on the data
    int yautoScale;                    // are we scaling ourselves based on the data
    
    int xlogScale;                    // is the data being log-scaled
    int ylogScale;                    // is the data being log-scaled
    
    int xAxisRot,yAxisRot;
        
    double minX,maxX,minY,maxY;        // the scale values
    
    int displayFormat[2];            // the number formating for the X and Y axises
    
    int topTitles,sideTitles;

    MColor wallCol;                    // the color of the "wall" behind the graphs
    
    int xRot,yRot;                    // x and y rotation perspective
    
    int wireFrame;                    // is this a wire-frame?
    
    int xMajorTicks,yMajorTicks;        // do we draw tick marks for major items
    
    int xMinorTicks,yMinorTicks;        // do we draw tick marks for minor items
    
    int xAxisLoc,yAxisLoc;                // the locations of the x and y axises
    
    int xMajorGrid,xMinorGrid;            // do we have x and y grids
    
    int yMajorGrid,yMinorGrid;
    
    int graphBorder;                    // is there a border around the graph?
    
    MColor xGridCol,yGridCol,borderCol;    // colors of the above items
    
    int lineWid,barColWid;
    int showPoint,showLine;
    int xMajTickSize,xMinTickSize;
    int yMajTickSize,yMinTickSize;
    int singleXRange;
    
    MGraphElement axisInfo;
    int numElements;
    MGraphElement *elements; 


    char mergeAnchor;
    
    char mergePos;
    
    char mergeOrder;
    
    char mergeName;
    
    char mergeScript;
    
    char mergeRange;

    char mergeBkgColor,mergeFrameColor;
    
    char mergeFrameSize;
    
    char mergeLegendPosition;
    
    char mergeLegendInfo;
    
    char mergeTitles[4];
    
    char mergeTitleInfo[4];
        
    char mergeOrient;
    
    char mergeXAuto;
    char mergeYAuto;
    
    char mergeXLog;
    char mergeYLog;
    
    char mergeXAxisRot;
    char mergeYAxisRot;
    
    char mergeScale;
    
    char mergeDispForm;
    
    char mergeTopTitles,mergeSideTitles;

    char mergeWallCol;
    
    char mergeXRot,mergeYRot;
    
    char mergeWireFrame;
    
    char mergeXMajorTicks,mergeYMajorTicks;
    
    char mergeXMinorTicks,mergeYMinorTicks;
    
    char mergeXAxisLoc,mergeYAxisLoc;
    
    char mergeXMajorGrid,mergeXMinorGrid;
    
    char mergeYMajorGrid, mergeYMinorGrid;
    
    char mergeGraphBorder;
    
    char mergeXGridCol,mergeYGridCol, mergeBorderCol;
    
    char mergeLineWid,mergeBarColWid;
    
    char mergeShowPoint,mergeShowLine;
    
    char mergeXMajTickSize,mergeXMinTickSize;
    
    char mergeYMajTickSize,mergeYMinTickSize;
    
    char mergeSingleXRange;
    char mergeAxisInfo,mergeElements;
    
};

/*
    
}
*/

// ifndef _MH_grXf
#endif
