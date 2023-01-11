#pragma once
#include <vector>
#include <map>
#include <string>
#include "Vector2.h"
#include "CameraData.h"

struct TileMapData
{
    TileMapData();
    std::vector<int> tileDatas_;//マップタイルのデータの集合体
    std::map<std::string,std::vector<int>> layerTileDatas_;
    Vector2 WorldArea_;//世界の大きさ(グリッドの数)
    Vector2 ViewArea_;//画面に見える大きさ(グリッドの数)
    float cameraMoveRangeL_;//カメラが動く範囲Left
    float cameraMoveRangeR_;//カメラが動く範囲Right
    float cameraMoveRangeT_;//カメラが動く範囲Top
    float cameraMoveRangeB_;//カメラが動く範囲Bottom
    int chipSize_;
    struct tileinfo {
        int firstID_;
        int tilecount_;
        std::string tilename_;
    };
    std::vector<tileinfo> tileinfos_;
};
