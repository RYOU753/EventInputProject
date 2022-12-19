#pragma once
#include <memory>
#include <algorithm>
#include <cmath>
#include <string>
#include <string_view>
#include <fstream>
#include <DxLib.h>
#include <json.hpp>
#include "Vector2.h"
//#include "TimeMng.h"
//#include "shape/Capsule.h"
//#include "shape/Circle.h"

//時間があるときにクラスに分割
namespace utility
{
	constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
	constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };
	// 方向
	constexpr VECTOR DIR_F = { 0.0f, 0.0f, 1.0f };
	constexpr VECTOR DIR_B = { 0.0f, 0.0f, -1.0f };
	constexpr VECTOR DIR_R = { 1.0f, 0.0f, 0.0f };
	constexpr VECTOR DIR_L = { -1.0f, 0.0f, 0.0f };
	constexpr VECTOR DIR_U = { 0.0f, 1.0f, 0.0f };
	constexpr VECTOR DIR_D = { 0.0f, -1.0f, 0.0f };

	constexpr VECTOR AXIS_X = { 1.0f,0.0f,0.0f };
	constexpr VECTOR AXIS_Y = { 0.0f,1.0f,0.0f };
	constexpr VECTOR AXIS_Z = { 0.0f,0.0f,1.0f };

	constexpr float kEpsilonNormalSqrt = 1e-15F;

	constexpr float colorMaxNum = 255.0f;

	//1m=100
	constexpr double metre = 100.;
	constexpr float metreF = 100.f;
	//constexpr double metre = 10.;

	//値を範囲内にまとめる関数
	struct Clamp
	{
		double operator()(double value, double minVal = 0.0, double maxVal = 1.0)
		{
			return std::clamp(value, minVal, maxVal);
		}
	};

	//カプセルと円の当たり判定
	/*struct isHitCapCircle
	{
		bool operator()(const Capsule& cap, const Circle& cc)
		{
			Vector2D vp = cc.pos - cap.posA;
			Vector2D v = cap.posB - cap.posA;

			auto vDot = vp.Dot(v);
			auto vMag = v.Magnitude();

			v = v * Clamp()(vDot / (vMag * vMag));

			return (vp - v).Magnitude() < cap.radius + cc.radius;
		}
	};*/

	//反射ベクトルの導出
	struct VecReflection
	{
		Vector2D operator()(Vector2D vec, Vector2D nVec)
		{
			nVec.normal();

			return vec + 2 * (-vec.dot(nVec)) * nVec;
		}
	};

	//ラジアン値を0～2πに収める
	struct RadIn2PI
	{
		double operator()(double rad)
		{
			rad = fmod(rad, DX_TWO_PI);
			return rad < 0.0 ? rad + DX_TWO_PI : rad;
		}
		float operator()(float rad)
		{
			rad = fmod(rad, DX_TWO_PI_F);
			return rad < 0.0 ? rad + DX_TWO_PI_F : rad;
		}
		VECTOR operator()(VECTOR radVec)
		{
			return VECTOR(RadIn2PI()(radVec.x), RadIn2PI()(radVec.y), RadIn2PI()(radVec.z));
		}
	};

	//ラジアン値の差分を導出
	struct DiffRad
	{
		double operator()(double base, double target)
		{
			base = RadIn2PI()(base);
			target = RadIn2PI()(target);

			double ret = target - base;

			if (ret < 0.0)
			{
				ret = abs(ret) > DX_PI ? ret + DX_TWO_PI : ret;
			}
			else
			{
				ret = abs(ret) > DX_PI ? ret - DX_TWO_PI : ret;
			}

			return ret;
		}
	};

	//指定した秒数に一回trueを返す
	/*struct Timer
	{
		bool operator()(const double& cnt, double inv)
		{
			return (static_cast<int>((cnt + lpTimeMng.GetDeltaTime()) / inv) - static_cast<int>(cnt / inv));
		}
	};*/

	//std::string(UTF-8)からstd::string(Shift-JIS)に変換
	struct ConvertUTF8ToSJIS
	{
		std::string operator()(std::string utf8Str)
		{
			std::wstring wstr;
			wstr.resize(MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), static_cast<int>(utf8Str.size()), NULL, 0));

			MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), static_cast<int>(utf8Str.size()), &wstr[0], static_cast<int>(wstr.size()));

			std::string sjisStr;
			sjisStr.resize(static_cast<size_t>(WideCharToMultiByte(CP_THREAD_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL)) - 1);

			WideCharToMultiByte(CP_THREAD_ACP, 0, &wstr[0], static_cast<int>(wstr.size()), &sjisStr[0], static_cast<int>(sjisStr.size()), NULL, NULL);

			return sjisStr;
		}
	};

	//ラジアンから度
	struct RadToDeg
	{
		double operator()(double rad)
		{
			return rad * 180.0 / DX_PI;
		}

		float operator()(float rad)
		{
			return rad * 180.0f / DX_PI_F;
		}
	};

	//度からラジアン
	struct DegToRad
	{
		double operator()(double deg)
		{
			return deg * DX_PI / 180.0;
		}

		float operator()(float deg)
		{
			return deg * DX_PI_F / 180.0f;
		}
	};

	struct RadToDegVec
	{
		VECTOR operator()(VECTOR rad)
		{
			VECTOR retVec = VScale(rad, 180.0f);
			retVec.x /= DX_PI_F;
			retVec.y /= DX_PI_F;
			retVec.z /= DX_PI_F;
			return retVec;
		}
	};
	struct DegToRadVec
	{
		VECTOR operator()(VECTOR rad)
		{
			VECTOR retVec = VScale(rad, DX_PI_F);
			retVec.x /= 180.0f;
			retVec.y /= 180.0f;
			retVec.z /= 180.0f;
			return retVec;
		}
		VECTOR operator()(float x, float y, float z)
		{
			VECTOR retVec = VScale(VGet(x, y, z), DX_PI_F);
			retVec.x /= 180.0f;
			retVec.y /= 180.0f;
			retVec.z /= 180.0f;
			return retVec;
		}
	};

	//JSONの読み込み用
	struct JSONLoader
	{
		bool operator()(std::string_view path, nlohmann::json& j)
		{
			std::ifstream ifs(path.data());
			if (!ifs)
			{
				ifs.close();
				return false;
			}

			ifs >> j;
			ifs.close();
			return true;
		}
	};

	//JSONの書き込み用
	struct JSONWriter
	{
		bool operator()(std::string_view path, const nlohmann::json& j)
		{
			std::ofstream ofs(path.data());
			if (!ofs)
			{
				ofs.close();
				return false;
			}

			ofs << j.dump(2);
			ofs.close();

			return true;
		}
	};

	//JSONの展開
	struct DeployJSON
	{
		bool operator()(nlohmann::json& j)
		{
			if (j.is_string())
			{
				if (!JSONLoader()(j.get<std::string>(), j))
				{
					return false;
				}
				return true;
			}
			else if (j.is_object())
			{
				//何もしない
				return true;
			}

			return false;
		}
	};

	//nullまたは存在しないことを判定
	struct CheckExistJSONKey
	{
		bool operator()(const nlohmann::json& doc, std::string_view key, std::function<void(const nlohmann::json&)> func)
		{
			if (!doc.count(key))
			{
				return false;
			}

			if (doc.at(key.data()).is_null())
			{
				return false;
			}

			func(doc.at(key.data()));
			return true;
		}
	};

	struct Equals
	{
		bool operator()(const DxLib::VECTOR& v1, const DxLib::VECTOR& v2)
		{
			if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
			{
				return true;
			}
			return false;
		}
	};

	struct EqualsVZero
	{
		bool operator()(const DxLib::VECTOR& v1)
		{
			VECTOR v2 = VECTOR_ZERO;
			if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
			{
				return true;
			}
			return false;
		}
	};

	struct VNormalize
	{
		DxLib::VECTOR operator()(const DxLib::VECTOR& v)
		{
			if (EqualsVZero()(v))
			{
				// Quaternion計算でゼロを渡して、
				// エラー(-1, -1, -1)が返ってくると困る
				return v;
			}
			return VNorm(v);
		}
	};

	struct SqrMagnitude
	{
		float operator()(const VECTOR& v)
		{
			return v.x * v.x + v.y * v.y + v.z * v.z;
		}
	};
	//二つのベクトルのなす角を求める
	struct AngleDeg
	{
		float operator()(const VECTOR& from, const VECTOR& to)
		{
			// sqrt(a) * sqrt(b) = sqrt(a * b) -- valid for real numbers
			auto sqrMag = SqrMagnitude();
			float fLen = sqrMag(from);
			float tLen = sqrMag(to);
			float denominator = sqrt(fLen * tLen);
			if (denominator < kEpsilonNormalSqrt)
			{
				return 0.0f;
			}

			//float dot = std::clamp(Dot(from, to) / denominator, -1.0f, 1.0f);
			//auto dot = Dot(from, to) / denominator;
			auto dot = VDot(from, to) / denominator;
			if (dot < -1.0f)
			{
				dot = -1.0f;
			}
			if (dot > 1.0f)
			{
				dot = 1.0f;
			}

			auto cross = VCross(from, to);
			auto bit = cross.y < 0 ? -1.0f : 1.0f;

			auto d = acosf(dot) * (180.0f / DX_PI_F) * bit;
			//整数部格納変数
			float integ = 0.0f;
			//小数点以下格納用変数
			float decimal = 0.0f;
			//degreeなので小数点以下を切り捨て
			decimal = modf(d, &integ);
			return integ;
		}
	};
	struct VECTORtoString
	{
		std::string operator()(const VECTOR& vec)
		{
			return "x:" + std::to_string(vec.x) + "y:" + std::to_string(vec.y) + "z:" + std::to_string(vec.z);
		}
		std::string operator()(const Vector2& vec)
		{
			return "x:" + std::to_string(vec.x) + "y:" + std::to_string(vec.y);
		}
		std::string operator()(const Vector2F& vec)
		{
			return "x:" + std::to_string(vec.x) + "y:" + std::to_string(vec.y);
		}
		std::string operator()(const Vector2D& vec)
		{
			return "x:" + std::to_string(vec.x) + "y:" + std::to_string(vec.y);
		}
	};
	struct VECTORLerp
	{
		VECTOR operator()(const VECTOR& begin, const VECTOR& end, float t)
		{
			VECTOR re;
			re.x = std::lerp(begin.x, end.x, t);
			re.y = std::lerp(begin.y, end.y, t);
			re.z = std::lerp(begin.z, end.z, t);
			return re;
		}
		Vector2D operator()(const Vector2D& begin, const Vector2D& end, float t)
		{
			Vector2D re;
			re.x = std::lerp(begin.x, end.x, static_cast<double>(t));
			re.y = std::lerp(begin.y, end.y, static_cast<double>(t));
			return re;
		}
		Vector2F operator()(const Vector2F& begin, const Vector2F& end, float t)
		{
			Vector2F re;
			re.x = std::lerp(begin.x, end.x, t);
			re.y = std::lerp(begin.y, end.y, t);
			return re;
		}
	};

	struct ConertValueRange
	{
		template<
			class ToType,
			class FromType
		>
		ToType operator()(const FromType& val, const ToType& toMin, const ToType& toMax, FromType fromMin = 0, FromType fromMax = 1)
		{
			return toMin + (toMax - toMin) * static_cast<ToType>((val - fromMin) / (fromMax - fromMin));
		}
	};

	//指定座標が指定範囲内にあるか
	struct IsSearchPos
	{
		bool operator()(const VECTOR& origin, const float& radius, const VECTOR& searchpos)
		{
			auto dist = VSize(VSub(origin, searchpos));
			return dist < radius;
		}
	};

	//色を指定値以上に収める
	struct ColorMax
	{
		COLOR_F operator()(const COLOR_F& col, const COLOR_F& maxcol)
		{
			COLOR_F retcol;

			retcol.r = (std::max)(col.r, maxcol.r);
			retcol.g = (std::max)(col.g, maxcol.g);
			retcol.b = (std::max)(col.b, maxcol.b);
			retcol.a = (std::max)(col.a, maxcol.a);

			return retcol;
		}

		COLOR_F operator()(const COLOR_F& col, const float& maxcol)
		{
			COLOR_F retcol;

			retcol.r = (std::max)(col.r, maxcol);
			retcol.g = (std::max)(col.g, maxcol);
			retcol.b = (std::max)(col.b, maxcol);
			retcol.a = (std::max)(col.a, maxcol);

			return retcol;
		}
	};

	//色を指定値以下に収める
	struct ColorMin
	{
		COLOR_F operator()(const COLOR_F& col, const COLOR_F& mincol)
		{
			COLOR_F retcol;

			retcol.r = (std::min)(col.r, mincol.r);
			retcol.g = (std::min)(col.g, mincol.g);
			retcol.b = (std::min)(col.b, mincol.b);
			retcol.a = (std::min)(col.a, mincol.a);

			return retcol;
		}

		COLOR_F operator()(const COLOR_F& col, const float& mincol)
		{
			COLOR_F retcol;

			retcol.r = (std::min)(col.r, mincol);
			retcol.g = (std::min)(col.g, mincol);
			retcol.b = (std::min)(col.b, mincol);
			retcol.a = (std::min)(col.a, mincol);

			return retcol;
		}
	};

	//色を指定範囲に収める
	struct ColorClamp
	{
		COLOR_F operator()(const COLOR_F& col, const COLOR_F& mincol, const COLOR_F& maxcol)
		{
			COLOR_F retcol;

			retcol.r = std::clamp(col.r, mincol.r, maxcol.r);
			retcol.g = std::clamp(col.g, mincol.g, maxcol.g);
			retcol.b = std::clamp(col.b, mincol.b, maxcol.g);
			retcol.a = std::clamp(col.a, mincol.a, maxcol.a);

			return retcol;
		}

		COLOR_F operator()(const COLOR_F& col, const float& mincol, const float& maxcol)
		{
			COLOR_F retcol;

			retcol.r = std::clamp(col.r, mincol, maxcol);
			retcol.g = std::clamp(col.g, mincol, maxcol);
			retcol.b = std::clamp(col.b, mincol, maxcol);
			retcol.a = std::clamp(col.a, mincol, maxcol);

			return retcol;
		}
	};

	struct ConvertColorRateToRealNumber
	{
		//0.0f～1.0fの色情報を0.0f～255.0fに変換
		COLOR_F operator()(const COLOR_F& col)
		{
			COLOR_F retcol = ColorClamp()(col, 0.0f, 1.0f);

			retcol.r = colorMaxNum * retcol.r;
			retcol.g = colorMaxNum * retcol.g;
			retcol.b = colorMaxNum * retcol.b;
			retcol.a = colorMaxNum * retcol.a;

			return retcol;
		}

		//0.0f～1.0fの色情報を0.0f～255.0fに変換し余剰分をoverColに格納
		COLOR_F operator()(const COLOR_F& col, COLOR_F& overCol)
		{
			COLOR_F retcol = ColorMax()(col, 0.0f);

			retcol.r = colorMaxNum * retcol.r;
			retcol.g = colorMaxNum * retcol.g;
			retcol.b = colorMaxNum * retcol.b;
			retcol.a = colorMaxNum * retcol.a;

			overCol.r = retcol.r > 255.0f ? retcol.r - 255.0f : 0.0f;
			overCol.g = retcol.g > 255.0f ? retcol.g - 255.0f : 0.0f;
			overCol.b = retcol.b > 255.0f ? retcol.b - 255.0f : 0.0f;
			overCol.a = retcol.a > 255.0f ? retcol.a - 255.0f : 0.0f;

			return retcol;
		}

		//0.0f～1.0fの色情報を0.0f～255.0fに変換
		float operator()(const float& col)
		{
			float retcol = std::clamp(col, 0.0f, 1.0f);

			return colorMaxNum * retcol;
		}

		//0.0f～1.0fの特定の色情報を0.0f～255.0fに変換し余剰分をoverColに格納
		float operator()(const float& col, float& overCol)
		{
			float retcol = (std::max)(col, 0.0f);
			retcol *= colorMaxNum;

			overCol = retcol > 255.0f ? retcol - 255.0f : 0.0f;
			return retcol;
		}
	};

	struct ConvertColorRealNumberToRate
	{
		//0.0f～255.0fの色情報を0.0f～1.0fに変換
		COLOR_F operator()(const COLOR_F& col)
		{
			COLOR_F retcol = ColorClamp()(col, 0.0f, colorMaxNum);

			retcol.r = retcol.r / colorMaxNum;
			retcol.g = retcol.g / colorMaxNum;
			retcol.b = retcol.b / colorMaxNum;
			retcol.a = retcol.a / colorMaxNum;

			return retcol;
		}

		//0.0f～255.0fの色情報を0.0f～1.0fに変換し余剰分をoverColに格納
		COLOR_F operator()(const COLOR_F& col, COLOR_F& overCol)
		{
			COLOR_F retcol = ColorMax()(col, 0.0f);

			retcol.r = retcol.r / colorMaxNum;
			retcol.g = retcol.g / colorMaxNum;
			retcol.b = retcol.b / colorMaxNum;
			retcol.a = retcol.a / colorMaxNum;

			overCol.r = retcol.r > 1.0f ? retcol.r - 1.0f : 0.0f;
			overCol.g = retcol.g > 1.0f ? retcol.g - 1.0f : 0.0f;
			overCol.b = retcol.b > 1.0f ? retcol.b - 1.0f : 0.0f;
			overCol.a = retcol.a > 1.0f ? retcol.a - 1.0f : 0.0f;

			return retcol;
		}

		//0.0f～255.0fの特定の色情報を0.0f～1.0fに変換
		float operator()(const float& col)
		{
			float retcol = std::clamp(col, 0.0f, 255.0f);

			return retcol / colorMaxNum;
		}

		//0.0f～255.0fの特定の色情報を0.0f～1.0fに変換し余剰分をoverColに格納
		float operator()(const float& col, float& overCol)
		{
			float retcol = (std::max)(col, 0.0f);
			retcol /= colorMaxNum;

			overCol = retcol > 1.0f ? retcol - 1.0f : 0.0f;
			return retcol;
		}
	};

#if __has_include(<btBulletCollisionCommon.h>)
#include <btBulletCollisionCommon.h>
	struct DXVECTOR_CAST
	{
		VECTOR operator()(const btVector3& vec)
		{
			return VGet(static_cast<float>(vec.x()), static_cast<float>(vec.y()), static_cast<float>(vec.z()));
		}
	};
	struct btVector3_CAST
	{
		btVector3 operator()(const VECTOR& vec)
		{
			return btVector3(static_cast<btScalar>(vec.x), static_cast<btScalar>(vec.y), static_cast<btScalar>(vec.z));
		}
	};
	struct VECTORtoString
	{
		std::string operator()(const btVector3& vec)
		{
			return "x:" + std::to_string(vec.x()) + "y:" + std::to_string(vec.y()) + "z:" + std::to_string(vec.z());
		}
	};
#endif
}
