#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Timer.h"

using SectionTime = float;
class MovePath
{
public:
	MovePath(std::string filepath);
    MovePath(std::string filepath, std::shared_ptr<class Transform> relative);
	~MovePath();
    void Draw(class DrawMng& drawMng);
    void Update(const double& delta);
    VECTOR GetCurrentPos();
private:
    //カメラがパスに沿って移動を終えたか
    bool IsEndPathMove(void);
    //カメラの通るパスをデータから取得する
    void PathDataLoader(std::string filepath);
private:
    struct PointDate
    {
        VECTOR point;
        SectionTime time;
    };
    std::vector<VECTOR> pathPoints_;
    std::pair<std::vector<VECTOR>::iterator, std::vector<VECTOR>::iterator> currentSections_;
    std::vector<SectionTime> sectionTimes_;
    Timer currentTime_;
    std::vector<SectionTime>::iterator currentLimits_;
    VECTOR currentPos_;

    std::weak_ptr<class Transform> relative_;

    bool isEndPathMove_;
};

