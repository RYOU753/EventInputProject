#pragma once
class Timer
{
public:
	Timer(float limit=0.0f,float currenttime=0.0f);
	~Timer();
	void Update(const double& delta);
	//ŠÔ‚ª‚·‚¬‚½‚©
	bool IsTimeOver();
	//‚O`‚P‚É³‹K‰»‚µ‚½ŠÔ‚ğæ“¾
	float NormalizedTime();
	//Œ»İ‚ÌŒo‰ßŠÔ‚ğæ“¾
	float GetDurationTime();
	//1‚©‚ç‚O`‚P‚É³‹K‰»‚µ‚½ŠÔ‚ğˆø‚¢‚½ŠÔ‚ğæ“¾
	float InversNormalizedTime();
	//Limit‚©‚çŒ»İ‚ÌŒo‰ßŠÔ‚ğˆø‚¢‚½ŠÔ‚ğæ“¾
	float InversTime();
	//Œo‰ßŠÔ‚ğ0‚É‚·‚é
	void ResetTime();
	//Œo‰ßŠÔ‚ğD‚«‚ÈŠÔ‚Éİ’è
	void SetTime(float time);
	//§ŒÀ‚ğD‚«‚ÈŠÔ‚Éİ’è
	void SetLimitTime(float limit);
	const float& GetLimitTime(void);
	//ƒŠƒZƒbƒg‚µ‚½‰ñ”‚ğæ“¾‚·‚é
	const int& GetResetCount(void);
private:
	float currentTime_;
	float limitTime_;
	int resetCounter_;
};
