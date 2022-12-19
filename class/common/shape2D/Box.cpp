#include <DxLib.h>
#include "Box.h"
#include "../../_debug/_DebugDispOut.h"

Box::Box(BOX_PLACE_TYPE placeType, Position2F pos, Vector2F size) 
	:Shape(pos),type_(placeType)
{
	SetSize(size);
}

Box::~Box()
{
}

ShapeType Box::GetShapeType(void) const
{
	return ShapeType::Box; 
}

void Box::dbgDraw(int color, bool isFill) const
{
	auto halfSize = size_ / 2.0f;
	switch (type_)
	{
	case BOX_PLACE_TYPE::LT:
		_dbgDrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::LB:
		_dbgDrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y - size_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::RT:
		_dbgDrawBox(static_cast<int>(basePos_.x- size_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x ), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::RB:
		_dbgDrawBox(static_cast<int>(basePos_.x - size_.x), static_cast<int>(basePos_.y - size_.x), static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CT:
		_dbgDrawBox(static_cast<int>(basePos_.x - halfSize.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + halfSize.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CB:
		_dbgDrawBox(static_cast<int>(basePos_.x - halfSize.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + halfSize.x), static_cast<int>(basePos_.y - size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CL:
		_dbgDrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y - halfSize.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + halfSize.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CR:
		_dbgDrawBox(static_cast<int>(basePos_.x - size_.x), static_cast<int>(basePos_.y - halfSize.y), static_cast<int>(basePos_.x), static_cast<int>(basePos_.y + halfSize.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CC:
		_dbgDrawBox(static_cast<int>(basePos_.x - halfSize.x), static_cast<int>(basePos_.y - halfSize.y), static_cast<int>(basePos_.x + halfSize.x), static_cast<int>(basePos_.y + halfSize.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::MAX:
		_dbgDrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	default:
		_dbgDrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	}
	_dbgDrawCircle(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), 7, 0xffffff, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::LT).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::LT).y), 5, 0xff0000, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::LB).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::LB).y), 5, 0xff0000, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::RT).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::RT).y), 5, 0xff0000, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::RB).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::RB).y), 5, 0xff0000, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CT).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CT).y), 5, 0x00ff00, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CB).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CB).y), 5, 0x00ff00, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CL).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CL).y), 5, 0x00ff00, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CR).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CR).y), 5, 0x00ff00, true);
	_dbgDrawCircle(static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CC).x), static_cast<int>(GetSelectPos(BOX_PLACE_TYPE::CC).y), 5, 0x00ff00, true);
}

void Box::Draw(int color, bool isFill) const
{
	auto halfSize = size_ / 2.0f;
	switch (type_)
	{
	case BOX_PLACE_TYPE::LT:
		DrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::LB:
		DrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y - size_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::RT:
		DrawBox(static_cast<int>(basePos_.x - size_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::RB:
		DrawBox(static_cast<int>(basePos_.x - size_.x), static_cast<int>(basePos_.y - size_.x), static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CT:
		DrawBox(static_cast<int>(basePos_.x - halfSize.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + halfSize.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CB:
		DrawBox(static_cast<int>(basePos_.x - halfSize.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + halfSize.x), static_cast<int>(basePos_.y - size_.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CL:
		DrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y - halfSize.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + halfSize.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CR:
		DrawBox(static_cast<int>(basePos_.x - size_.x), static_cast<int>(basePos_.y - halfSize.y), static_cast<int>(basePos_.x), static_cast<int>(basePos_.y + halfSize.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::CC:
		DrawBox(static_cast<int>(basePos_.x - halfSize.x), static_cast<int>(basePos_.y - halfSize.y), static_cast<int>(basePos_.x + halfSize.x), static_cast<int>(basePos_.y + halfSize.y), color, isFill);
		break;
	case BOX_PLACE_TYPE::MAX:
		DrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	default:
		DrawBox(static_cast<int>(basePos_.x), static_cast<int>(basePos_.y), static_cast<int>(basePos_.x + size_.x), static_cast<int>(basePos_.y + size_.y), color, isFill);
		break;
	}
}

Position2F Box::GetSelectPos(BOX_PLACE_TYPE placeType)const
{
	Position2F rePos;
	auto halfSize = size_ / 2.0f;
	switch (placeType)
	{
	case BOX_PLACE_TYPE::LT:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = basePos_ - size_;
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x - halfSize.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x ,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - size_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = basePos_ - halfSize;
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = basePos_;
			break;
		default:
			rePos = basePos_;
			break;
		}
		break;
	case BOX_PLACE_TYPE::LB:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - size_.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x - size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x - halfSize.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - size_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x - halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x,basePos_.y + size_.y };
			break;
		default:
			rePos = { basePos_.x,basePos_.y + size_.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::RT:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x + size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x + size_.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x + halfSize.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x + size_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x + halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x + size_.x,basePos_.y };
			break;
		default:
			rePos = { basePos_.x + size_.x,basePos_.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::RB:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x + size_.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x + size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x + halfSize.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x + size_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x + halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x + size_.x,basePos_.y + size_.y };
			break;
		default:
			rePos = { basePos_.x + size_.x,basePos_.y + size_.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::CT:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x + halfSize.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x - halfSize.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x + halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		default:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::CB:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x + halfSize.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - halfSize.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x,basePos_.y + size_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x + halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x + halfSize.x,basePos_.y + size_.y };
			break;
		default:
			rePos = { basePos_.x + halfSize.x,basePos_.y + size_.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::CL:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - size_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x - size_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x - halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x - halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		default:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::CR:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = { basePos_.x + size_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x + size_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x + halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x + halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x + size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = { basePos_.x + size_.x,basePos_.y + halfSize.y };
			break;
		default:
			rePos = { basePos_.x + size_.x,basePos_.y + halfSize.y };
			break;
		}
		break;
	case BOX_PLACE_TYPE::CC:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = basePos_ + halfSize;
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x + halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - halfSize.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = { basePos_.x - halfSize.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x,basePos_.y + halfSize.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x + halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = basePos_ + halfSize;
			break;
		default:
			rePos = basePos_ + halfSize;
			break;
		}
		break;
	case BOX_PLACE_TYPE::MAX:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = basePos_ - size_;
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x - halfSize.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x ,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - size_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = basePos_ - halfSize;
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = basePos_;
			break;
		default:
			rePos = basePos_;
			break;
		}
		break;
	default:
		switch (type_)
		{
		case BOX_PLACE_TYPE::LT:
			rePos = basePos_;
			break;
		case BOX_PLACE_TYPE::LB:
			rePos = { basePos_.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::RT:
			rePos = { basePos_.x - size_.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::RB:
			rePos = basePos_ - size_;
			break;
		case BOX_PLACE_TYPE::CT:
			rePos = { basePos_.x - halfSize.x,basePos_.y };
			break;
		case BOX_PLACE_TYPE::CB:
			rePos = { basePos_.x - halfSize.x,basePos_.y - size_.y };
			break;
		case BOX_PLACE_TYPE::CL:
			rePos = { basePos_.x ,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CR:
			rePos = { basePos_.x - size_.x,basePos_.y - halfSize.y };
			break;
		case BOX_PLACE_TYPE::CC:
			rePos = basePos_ - halfSize;
			break;
		case BOX_PLACE_TYPE::MAX:
			rePos = basePos_;
			break;
		default:
			rePos = basePos_;
			break;
		}
		break;
	}

	return rePos;
}

void Box::SetSize(Vector2F size)
{
	size_ = { std::fabsf(size.x) ,std::fabsf(size.y) };
}

const Vector2F& Box::GetSize(void) const
{
	return size_;
}

void Box::ChangeBasePosType(BOX_PLACE_TYPE placeType)
{
	type_ = placeType;
}

bool Box::IsHit(Position2 pos, bool inLine)
{
	auto LT = this->GetSelectPos(BOX_PLACE_TYPE::LT);
	auto RB = this->GetSelectPos(BOX_PLACE_TYPE::RB);
	if (inLine) 
	{
		if (!(LT.x <= pos.x && RB.x >= pos.x))
		{
			return false;
		}
		if (!(LT.y <= pos.y && RB.y >= pos.y))
		{
			return false;
		}
	}
	else 
	{
		if (!(LT.x < pos.x && RB.x > pos.x))
		{
			return false;
		}
		if (!(LT.y < pos.y && RB.y > pos.y))
		{
			return false;
		}
	}

	return true;
}
