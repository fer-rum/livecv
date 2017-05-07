import QtQuick 2.3
import lcvcore 1.0
import lcvimgproc 1.0

Row{
    
    // This sample shows how to iterate or 
    // access values from an image directly
    // from the qml file and create a custom filter.
    
    ImRead{
       id : src
       file : project.dir() + '/../_images/buildings_0246.jpg'
    }
    
    ChannelSelect{
        input : src.output
        width : src.width
        height : src.height
        
        onOutputChanged : {
            var data = output.data()
            var rows = data.rows()
            var cols = data.cols()
            var channels = data.channels()
            
            var vals = data.values()
            
            for ( var i = 0; i < rows; ++i ){
                for ( var j = 0; j < cols; ++j ){
                    if ( vals[i][j * channels] > 160 ){
                        vals[i][j * channels + 0] = 200
                        vals[i][j * channels + 1] = 200
                        vals[i][j * channels + 2] = 200
                    }
                }
            }
            
            
            data.setValues(vals)
        }
    }
    
}
