#include <fstream>
#include <sstream>
#include <string>

#include "../draw/DrawMng.h"
#include "../draw/command/DrawLine3DDC.h"
#include "../draw/command/DrawSphere3DDC.h"

#include "MovePath.h"
#include "Transform.h"
#include "Utility.h"
#include "../../_debug/_DebugDispOut.h"

using namespace std;

MovePath::MovePath(std::string filepath)
{
    PathDataLoader(filepath);

	currentLimits_ = sectionTimes_.begin();
	currentTime_.SetLimitTime(*currentLimits_);
	currentSections_.first = pathPoints_.begin();
	currentSections_.second = pathPoints_.begin() + 1;
	currentPos_ =*(currentSections_.first);

	isEndPathMove_ = false;
}

MovePath::MovePath(std::string filepath, std::shared_ptr<Transform> relative)
{
	PathDataLoader(filepath);

	currentLimits_ = sectionTimes_.begin();
	currentTime_.SetLimitTime(*currentLimits_);
	currentSections_.first = pathPoints_.begin();
	currentSections_.second = pathPoints_.begin() + 1;
	currentPos_ = *(currentSections_.first);

	relative_ = relative;

	isEndPathMove_ = false;
}

MovePath::~MovePath()
{
}

void MovePath::Draw(DrawMng& drawMng)
{
	for (auto itr = pathPoints_.begin(); itr + 1 < pathPoints_.end(); itr++)
	{
		VECTOR p1 = VGet(itr->x, itr->y, itr->z);
		VECTOR p2 = VGet((itr + 1)->x, (itr + 1)->y, (itr + 1)->z);
		if (!relative_.expired())
		{
			p1 = VAdd(p1, relative_.lock()->GetPosition());
			p2 = VAdd(p2, relative_.lock()->GetPosition());
		}
		drawMng.SetDrawCommand(std::make_unique<DrawSphere3DDC>(DRAW_ORDER::Camera, p1, 10.0f, 10, 0x00ff00, 0xffffff, true));
		drawMng.SetDrawCommand(std::make_unique<DrawSphere3DDC>(DRAW_ORDER::Camera, p2, 10.0f, 10, 0x00ff00, 0xffffff, true));
		drawMng.SetDrawCommand(std::make_unique<DrawLine3DDC>(DRAW_ORDER::Camera, p1, p2, 0xff0000));
	}
	drawMng.SetDrawCommand(std::make_unique<DrawSphere3DDC>(DRAW_ORDER::Camera, pathPoints_.back(), 10.0f, 10, 0xff0000, 0xffffff, true));;
}

void MovePath::Update(const double& delta)
{
	currentTime_.Update(delta);
	_TRACE_M(0x0000ff, "Moving Time:%lf", currentTime_.GetDurationTime());
	_TRACE_M(0x0000ff, "Now Section:%d %d", std::distance(pathPoints_.begin(), currentSections_.first), std::distance(pathPoints_.begin(), currentSections_.second));

	if (!(currentSections_.second + 1 < pathPoints_.end()))
	{
		if (!currentTime_.IsTimeOver())
		{
			currentPos_ = utility::VECTORLerp()(*(currentSections_.first), *(currentSections_.second), currentTime_.NormalizedTime());
			_TRACE_M(0x0000ff, "cameraPos:" + utility::VECTORtoString()(currentPos_));
		}
		isEndPathMove_ = true;
		return;
	}

	if (currentTime_.IsTimeOver())
	{
		currentPos_ = *(currentSections_.second);
		currentSections_.first++;
		currentSections_.second++;
		currentTime_.ResetTime();
		currentTime_.SetLimitTime(*(++currentLimits_));
	}
	else
	{
		currentPos_ = utility::VECTORLerp()(*(currentSections_.first), *(currentSections_.second), currentTime_.NormalizedTime());
	}

	_TRACE_M(0x0000ff, "cameraPos:" + utility::VECTORtoString()(currentPos_));
}

bool MovePath::IsEndPathMove(void)
{
    return false;
}

void MovePath::PathDataLoader(std::string filepath)
{
	auto split = [](string& input, char delimiter)
	{
		istringstream stream(input);
		string field;
		vector<string> result;
		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	};

	ifstream ifs(filepath);
	
	string line;
	int cnt = 0;
	while (getline(ifs, line))
	{
		if (cnt++ == 0)
		{
			continue;
		}

		vector<string> strvec = split(line, ',');
		VECTOR work = VGet(0, 0, 0);
		work.x = stof(strvec[0]);
		work.y = stof(strvec[1]);
		work.z = stof(strvec[2]);
		pathPoints_.emplace_back(work);
		sectionTimes_.emplace_back(stof(strvec[3]));
	}
}

VECTOR MovePath::GetCurrentPos()
{
	if (!relative_.expired())
	{
		return VAdd(currentPos_, relative_.lock()->GetPosition());
	}
	return currentPos_;
}
