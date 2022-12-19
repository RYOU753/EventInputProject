#include "Transform.h"


Transform::Transform(void)
{
	matAll = {};
	matPos = {};
	matRot = {};
	matScl = {};
	pos = {};
	rot = {};
	scl = {};
}

Transform::Transform(VECTOR pos, Quaternion qRot, VECTOR scale, Quaternion qRotLocal)
{
	SetPosition(pos);
	SetQuaternionRot(qRot);
	SetScale(scale);
	SetQuaternionRotLocal(qRotLocal);
}

Transform::~Transform()
{
}

void Transform::SetScale(VECTOR scl)
{
	this->scl = scl;
	matScl = MGetScale(scl);
}

void Transform::SetPosition(VECTOR pos)
{
	this->pos = pos;
	matPos = MGetTranslate(pos);
}

void Transform::SetQuaternionRot(Quaternion qua)
{
	quaRot = qua;
	rot = quaRot.ToEuler();
	matRot = quaRot.ToMatrix();
}

void Transform::SetRotX(float rotx)
{
	SetQuaternionRot(Quaternion::Euler(VGet(rotx,rot.y,rot.x)));
}

void Transform::SetRotY(float roty)
{
	SetQuaternionRot(Quaternion::Euler(VGet(rot.x, roty, rot.z)));
}

void Transform::SetRotZ(float rotz)
{
	SetQuaternionRot(Quaternion::Euler(VGet(rot.x, rot.y, rotz)));
}

void Transform::SetQuaternionRotLocal(Quaternion quaLocal)
{
	quaRotLocal = quaLocal;
}

void Transform::SetRotLocalX(const float& rotx)
{
	SetQuaternionRotLocal(Quaternion::Euler(rotx, quaRotLocal.y, quaRotLocal.z));
}

void Transform::SetRotLocalY(const float& roty)
{
	SetQuaternionRotLocal(Quaternion::Euler(quaRotLocal.x, roty, quaRotLocal.z));
}

void Transform::SetRotLocalZ(const float& rotz)
{
	SetQuaternionRotLocal(Quaternion::Euler(quaRotLocal.x, quaRotLocal.y, rotz));
}

const VECTOR&& Transform::GetForward(void)
{
	return GetDir({ 0.0f, 0.0f, 1.0f });
}

const VECTOR&& Transform::GetBack(void)
{
	return GetDir({ 0.0f, 0.0f, -1.0f });
}

const VECTOR&& Transform::GetRight(void)
{
	return GetDir({ 1.0f, 0.0f, 0.0f });
}

const VECTOR&& Transform::GetLeft(void)
{
	return GetDir({ -1.0f, 0.0f, 0.0f });
}

const VECTOR&& Transform::GetUp(void)
{
	return GetDir({ 0.0f, 1.0f, 0.0f });
}

const VECTOR&& Transform::GetDown(void)
{
	return GetDir({ 0.0f, -1.0f, 0.0f });
}

const VECTOR&& Transform::GetDir(VECTOR vec)
{
	return std::move(VNorm(VTransform(vec, matRot)));
}
