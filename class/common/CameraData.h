#pragma once
#include <vector>
#include "Vector2.h"
#include "shape2D/Box.h"

struct CameraData
{
    Vector2 WorldArea_;//���E�̑傫��(�O���b�h�̐�)
    Vector2 ViewArea_;//��ʂɌ�����傫��(�O���b�h�̐�)
    float cameraMoveRangeL_;//�J�����������͈�Left
    float cameraMoveRangeR_;//�J�����������͈�Right
    float cameraMoveRangeT_;//�J�����������͈�Top
    float cameraMoveRangeB_;//�J�����������͈�Bottom
    Box cameraMoveRange_;
    int chipSize_;
};