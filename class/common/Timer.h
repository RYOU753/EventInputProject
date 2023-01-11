#pragma once
class Timer
{
public:
	Timer(float limit=0.0f,float currenttime=0.0f);
	~Timer();
	void Update(const double& delta);
	//時間がすぎたか
	bool IsTimeOver();
	//０～１に正規化した時間を取得
	float NormalizedTime();
	//現在の経過時間を取得
	float GetDurationTime();
	//1から０～１に正規化した時間を引いた時間を取得
	float InversNormalizedTime();
	//Limitから現在の経過時間を引いた時間を取得
	float InversTime();
	//経過時間を0にする
	void ResetTime();
	//経過時間を好きな時間に設定
	void SetTime(float time);
	//制限を好きな時間に設定
	void SetLimitTime(float limit);
	const float& GetLimitTime(void);
	//リセットした回数を取得する
	const int& GetResetCount(void);
private:
	float currentTime_;
	float limitTime_;
	int resetCounter_;
};
