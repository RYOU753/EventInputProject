#pragma once
#include <vector>
#include "Vector2.h"
#include "shape2D/Box.h"

struct CameraData
{
    Vector2 WorldArea_;//世界の大きさ(グリッドの数)
    Vector2 ViewArea_;//画面に見える大きさ(グリッドの数)
    float cameraMoveRangeL_;//カメラが動く範囲Left
    float cameraMoveRangeR_;//カメラが動く範囲Right
    float cameraMoveRangeT_;//カメラが動く範囲Top
    float cameraMoveRangeB_;//カメラが動く範囲Bottom
    Box cameraMoveRange_;
    int chipSize_;
};