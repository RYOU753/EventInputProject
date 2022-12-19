#pragma once
class Timer
{
public:
	Timer(float limit=0.0f,float currenttime=0.0f);
	~Timer();
	void Update(const double& delta);
	//���Ԃ���������
	bool IsTimeOver();
	//�O�`�P�ɐ��K���������Ԃ��擾
	float NormalizedTime();
	//���݂̌o�ߎ��Ԃ��擾
	float GetDurationTime();
	//1����O�`�P�ɐ��K���������Ԃ����������Ԃ��擾
	float InversNormalizedTime();
	//Limit���猻�݂̌o�ߎ��Ԃ����������Ԃ��擾
	float InversTime();
	//�o�ߎ��Ԃ�0�ɂ���
	void ResetTime();
	//�o�ߎ��Ԃ��D���Ȏ��Ԃɐݒ�
	void SetTime(float time);
	//�������D���Ȏ��Ԃɐݒ�
	void SetLimitTime(float limit);
	const float& GetLimitTime(void);
	//���Z�b�g�����񐔂��擾����
	const int& GetResetCount(void);
private:
	float currentTime_;
	float limitTime_;
	int resetCounter_;
};
