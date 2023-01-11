#pragma once
#include <map>
#include <memory>
//#include "Ray.h"
#include "Box.h"
#include "Circle.h"
#include "../../_debug/_DebugConOut.h"

class Collision
{
public:
	~Collision() {};
	virtual bool IsHitObject(const Shape& s1, const Shape& s2) = 0;
};

//class RayAndRay :public Collision
//{
//public:
//	RayAndRay() {};
//	bool IsHitObject(const Shape& s1, const Shape& s2)override
//	{
//		auto& r1 = dynamic_cast<const Ray&>(s1);
//		auto& r2 = dynamic_cast<const Ray&>(s2);
//		Vector2F ray_to_line[2] = { r1.pos - r2.pos,r1.end() - r2.pos };
//		Vector2F line_to_ray[2] = { r2.pos - r1.pos ,r2.end() - r1.pos };
//		auto checkcross = [](Vector2F vec1, Vector2F vec[2])
//		{
//			auto t = vec1.cross(vec[0]);
//			auto d = vec1.cross(vec[1]);
//			return std::signbit(static_cast<float>(t)) ^ std::signbit(static_cast<float>(d));
//		};
//		if (checkcross(r2.vec, ray_to_line) && checkcross(r1.vec, line_to_ray))
//		{
//			return true;
//		}
//		return false;
//	};
//};

//class RayAndBox :public Collision
//{
//public:
//	RayAndBox() {};
//	bool IsHitObject(const Shape& s1, const Shape& s2)override
//	{
//		auto& r1 = dynamic_cast<const Ray&>(s1);
//		auto& b1 = dynamic_cast<const Box&>(s2);
//		auto checkcross = [](Vector2F vec1, Vector2F vec[2])
//		{
//			auto t = vec1.cross(vec[0]);
//			auto d = vec1.cross(vec[1]);
//			return std::signbit(static_cast<float>(t)) ^ std::signbit(static_cast<float>(d));
//		};
//		auto rtn = [&checkcross,r1](Line line)
//		{
//			Vector2F ray_to_line[2] = { r1.pos - line.Begin,r1.end() - line.End };
//			Vector2F line_to_ray[2] = { line.Begin - r1.pos ,line.End - r1.pos };
//			return checkcross(line.dir(), ray_to_line) && checkcross(r1.vec, line_to_ray);
//		};
//		if (rtn(b1.topline))
//		{
//			return true;
//		}
//		if (rtn(b1.bottomline))
//		{
//			return true;
//		}
//		if (rtn(b1.leftline))
//		{
//			return true;
//		}
//		if (rtn(b1.rightline))
//		{
//			return true;
//		}
//		return false;
//		/*Vector2F ray_to_line[2] = { r1.pos - b1.topline.Begin,r1.end() - b1.topline.End };
//		Vector2F line_to_ray[2] = { b1.topline.Begin - r1.pos ,b1.topline.End - r1.pos };
//		if (checkcross(b1.topline.dir(), ray_to_line) && checkcross(r1.vec, line_to_ray))
//		{
//			return true;
//		}
//		ray_to_line[0] = r1.pos - b1.bottomline.Begin;
//		ray_to_line[1] = r1.end() - b1.bottomline.End;
//		line_to_ray[0] = b1.bottomline.Begin - r1.pos;
//		line_to_ray[1] = b1.bottomline.End - r1.pos;
//		if (checkcross(b1.bottomline.dir(), ray_to_line) && checkcross(r1.vec, line_to_ray))
//		{
//			return true;
//		}
//		ray_to_line[0] = r1.pos - b1.leftline.Begin;
//		ray_to_line[1] = r1.end() - b1.leftline.End;
//		line_to_ray[0] = b1.leftline.Begin - r1.pos;
//		line_to_ray[1] = b1.leftline.End - r1.pos;
//		if (checkcross(b1.leftline.dir(), ray_to_line) && checkcross(r1.vec, line_to_ray))
//		{
//			return true;
//		}
//		ray_to_line[0] = r1.pos - b1.rightline.Begin;
//		ray_to_line[1] = r1.end() - b1.rightline.End;
//		line_to_ray[0] = b1.rightline.Begin - r1.pos;
//		line_to_ray[1] = b1.rightline.End - r1.pos;
//		if (checkcross(b1.rightline.dir(), ray_to_line) && checkcross(r1.vec, line_to_ray))
//		{
//			return true;
//		}
//		return false;*/
//	}
//};

//class RayAndCircle :public Collision
//{
//public:
//	RayAndCircle() {};
//	bool IsHitObject(const Shape& s1, const Shape& s2)override
//	{
//		auto& r1 = dynamic_cast<const Ray&>(s1);
//		auto& c1 = dynamic_cast<const Circle&>(s2);
//		auto lengthSQ1 = (c1.center - r1.pos).lengthSQ();
//		auto lengthSQ2 = (c1.center - r1.end()).lengthSQ();
//		//端の点が円内に入ってないか
//		if (lengthSQ1 <= (c1.radius * c1.radius) || lengthSQ2 <= (c1.radius * c1.radius))
//		{
//			return true;
//		}
//		//角度
//		auto kakudo1 = (c1.center - r1.pos).normalized().dot(r1.vec.normalized());
//		auto kakudo2 = -(c1.center - r1.end()).normalized().dot(r1.vec.normalized());
//		//TRACE("1:%lf 2:%lf\n", kakudo1, kakudo2);
//		Vector2F vec1 = (c1.center - r1.pos);
//		Vector2F vec2 = r1.vec;
//		//最短距離の二乗
//		auto lengthSQ3 = std::powf(vec1.length() * vec1.normalized().cross(vec2.normalized()),2);
//		//TRACE("%lf\n", lengthSQ3);
//		//最短距離と両端内に円が入っているとき
//		if (lengthSQ3 <= (c1.radius * c1.radius) && !std::signbit(kakudo1) && !std::signbit(kakudo2))
//		{
//			return true;
//		}
//		return false;
//	}
//};

class BoxAndBox :public Collision
{
public:
	BoxAndBox() {};
	bool IsHitObject(const Shape& s1, const Shape& s2)override
	{
		auto& b1 = dynamic_cast<const Box&>(s1);
		auto& b2 = dynamic_cast<const Box&>(s2);
		auto hitcheck = [](const Box& b1,const Box& b2)
		{
			auto LT1 = b1.GetSelectPos(BOX_PLACE_TYPE::LT);
			auto RB1 = b1.GetSelectPos(BOX_PLACE_TYPE::RB);
			auto LT2 = b2.GetSelectPos(BOX_PLACE_TYPE::LT);
			auto RB2 = b2.GetSelectPos(BOX_PLACE_TYPE::RB);

			bool flag1 = (LT1.x >= LT2.x && LT1.x <= RB2.x);
			bool flag2 = (LT1.y >= LT2.y && LT1.y <= RB2.y);
			bool flag3 = (RB1.x >= LT2.x && RB1.x <= RB2.x);
			bool flag4 = (RB1.y >= LT2.y && RB1.y <= RB2.y);
			if (flag1 && flag2)
			{
				return true;
			}
			if (flag3 && flag2)
			{
				return true;
			}
			if (flag1 && flag4)
			{
				return true;
			}
			if (flag3 && flag4)
			{
				return true;
			}
			return false;
		};
		if (hitcheck(b1, b2))
		{
			return true;
		}
		if (hitcheck(b2, b1))
		{
			return true;
		}
		return false;
	};
};
class BoxAndCircle :public Collision
{
public:
	BoxAndCircle() {};
	bool IsHitObject(const Shape& s1, const Shape& s2)override
	{
		auto& b1 = dynamic_cast<const Box&>(s1);
		auto& c1 = dynamic_cast<const Circle&>(s2);
		auto hitcheck = [&c1](const Position2F& pos)
		{
			if (c1.GetBasePos().distanceSQ(pos) <= std::powf(c1.GetRadius(), 2.0f))
			{
				return true;
			}
			return false;
		};
		//四角の角と円の中心の距離の2乗と半径の2乗の比較
		if (hitcheck(b1.GetSelectPos(BOX_PLACE_TYPE::LT)) || hitcheck(b1.GetSelectPos(BOX_PLACE_TYPE::LB)) ||
			hitcheck(b1.GetSelectPos(BOX_PLACE_TYPE::RT)) || hitcheck(b1.GetSelectPos(BOX_PLACE_TYPE::RB)))
		{
			return true;
		}
		auto LT = b1.GetSelectPos(BOX_PLACE_TYPE::LT);
		auto RB = b1.GetSelectPos(BOX_PLACE_TYPE::RB);
		bool flag1 = ((LT.x - c1.GetRadius() <= c1.GetBasePos().x) && (RB.x + c1.GetRadius() >= c1.GetBasePos().x));
		bool flag2 = (LT.y - c1.GetRadius() <= c1.GetBasePos().y && RB.y + c1.GetRadius() >= c1.GetBasePos().y);
		if (flag1 && flag2)
		{
			return true;
		}

		return false;
	}
};

class CircleAndCircle :public Collision
{
public:
	CircleAndCircle() {};
	bool IsHitObject(const Shape& s1, const Shape& s2)override
	{
		auto& c1 = dynamic_cast<const Circle&>(s1);
		auto& c2 = dynamic_cast<const Circle&>(s2);

		auto lengthSQ = std::powf(c1.GetRadius() + c2.GetRadius(),2.0f);
		auto lengthSQ2 = (c1.GetBasePos() - c2.GetBasePos()).lengthSQ();
		if (lengthSQ >= lengthSQ2)
		{
			return true;
		}
		return false;
	}
};

class FlexibleCollision :public Collision
{
public:
	FlexibleCollision()
	{
		//組み合わせ関係なし
		//ColNotCombiTable_.emplace(std::make_pair(ShapeType::Ray, ShapeType::Ray), std::make_unique<RayAndRay>());
		ColNotCombiTable_.emplace(std::make_pair(ShapeType::Box, ShapeType::Box), std::make_unique < BoxAndBox>());
		ColNotCombiTable_.emplace(std::make_pair(ShapeType::Circle, ShapeType::Circle), std::make_unique < CircleAndCircle>());
		//組み合わせあり
		//ColCombiTable_.emplace(std::make_pair(ShapeType::Ray, ShapeType::Box), std::make_unique < RayAndBox>());
		//ColCombiTable_.emplace(std::make_pair(ShapeType::Ray, ShapeType::Circle), std::make_unique < RayAndCircle>());
		ColCombiTable_.emplace(std::make_pair(ShapeType::Box, ShapeType::Circle), std::make_unique < BoxAndCircle>());
	}
	~FlexibleCollision()
	{
	}
	virtual bool IsHitObject(const Shape& s1, const Shape& s2)
	{
		auto s1type = s1.GetShapeType();
		auto s2type = s2.GetShapeType();
		if (s1type == s2type)//組み合わせ関係
		{
			return ColNotCombiTable_.at(std::make_pair(s1type, s2type))->IsHitObject(s1, s2);
		}
		else
		{
			if (ColCombiTable_.count({s1type,s2type}))//ある組み合わせにあわせる
			{
				return ColCombiTable_.at(std::make_pair(s1type, s2type))->IsHitObject(s1, s2);
			}
			else
			{
				return ColCombiTable_.at(std::make_pair(s2type, s1type))->IsHitObject(s2, s1);
			}
		}
	}
private:
	std::map<std::pair<ShapeType, ShapeType>, std::unique_ptr<Collision>> ColNotCombiTable_;
	std::map<std::pair<ShapeType, ShapeType>, std::unique_ptr<Collision>> ColCombiTable_;
};