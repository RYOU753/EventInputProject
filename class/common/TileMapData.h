#pragma once
#include <vector>
#include <map>
#include <string>
#include "Vector2.h"
#include "CameraData.h"

struct TileMapData
{
    TileMapData();
    std::vector<int> tileDatas_;//�}�b�v�^�C���̃f�[�^�̏W����
    std::map<std::string,std::vector<int>> layerTileDatas_;
    Vector2 WorldArea_;//���E�̑傫��(�O���b�h�̐�)
    Vector2 ViewArea_;//��ʂɌ�����傫��(�O���b�h�̐�)
    float cameraMoveRangeL_;//�J�����������͈�Left
    float cameraMoveRangeR_;//�J�����������͈�Right
    float cameraMoveRangeT_;//�J�����������͈�Top
    float cameraMoveRangeB_;//�J�����������͈�Bottom
    int chipSize_;
    struct tileinfo {
        int firstID_;
        int tilecount_;
        std::string tilename_;
    };
    std::vector<tileinfo> tileinfos_;
};
