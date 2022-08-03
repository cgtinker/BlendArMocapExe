#include "session_manager.h"
#include <iostream>


namespace BlendArMocap{
    GraphRunner my_graph;
    cv::Mat rawImage;

    cv::Mat RawTexture(){
        int cols = 640;
        int rows = 480;
        uint8_t gArr[rows][cols];
        for (int row = 0; row < rows; row++){
            for (int col = 0; col < cols; col++){
                gArr[row][col] = 0;
            }
        }
        cv::Mat image = cv::Mat(rows, cols, CV_8U, &gArr);
        cv::cvtColor(image, image, cv::COLOR_BGR2RGBA);
        return image;
    }

    bool SessionManager::StartSession(int *detection_type, int *input_type, int *webcam_slot, char *movie_path){
        my_graph.InitGraphRunner("src/mp/graphs/face_mesh/face_mesh_desktop_live.pbtxt");
        // absl::Status state = this->graph.Start("src/mp/graphs/face_mesh/face_mesh_desktop_live.pbtxt");
        return true;
    }

    bool SessionManager::Update(){
        if (my_graph.isActive)
        {
            if(my_graph.Update()){
                this->frame = my_graph.Frame;
            }
            else{
                this->frame = RawTexture();
            }
        }
        else
        {
            this->frame = RawTexture();
        }
        return true;
    }

    void SessionManager::EndSession(){
        my_graph.StopGraph();
    }
}