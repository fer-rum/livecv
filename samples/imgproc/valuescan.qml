import QtQuick 2.3
import lcvcore 1.0
import lcvimgproc 1.0

Row{
    
    // Scan values and set custom pixels
    
    id : root
    
    property string imagePath : project.dir() + '/../_images/buildings_0246.jpg'
    
    Rectangle{
        
        width  : sc.width
        height : sc.height
        
        ImRead{
            id : sc
            file : root.imagePath
            RegionSelection{
                item : matRoi
                anchors.fill : parent
            }

        }
    }
    
    Rectangle{
        width : matRoi.width
        height : matRoi.height
        
    
        MatRoi{
            id : matRoi
            width : imgval.width
            height : imgval.height
            regionWidth  : 20
            regionHeight : 20
            regionX : 0
            regionY : 0
            linearFilter: false
            input : sc.output
        }
    
        MatRead{
            id : imgval
            input : matRoi.output
            opacity : 0.5
            squareCell : true
        }
    }    
}

