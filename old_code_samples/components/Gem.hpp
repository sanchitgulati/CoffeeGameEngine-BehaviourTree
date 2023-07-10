#pragma once
#include "../../Coffee/Coffee.hpp"
#include "../Direction.hpp"

using namespace Coffee;
class Gem : public Coffee::Sprite
{
public:
	static std::shared_ptr<Gem> createWithFile(const std::string& filePath);
	void init(const std::string& filepath);
	int getType();
	void setType(int type);
	void pop(float delay);
	void normal();
	void selected();
	void removeWithAnim(std::shared_ptr<GameObject> grid, std::function<void()> func = nullptr);
	void shake(Direction direction);
	void moveTo(vector2 pos1, vector2 pos2, std::function<void()> func = nullptr);
private:
	float _defaultScale;
	float _selectedScale;
	float _shakeDelta;
	std::string _popAudio;
	std::string _unpopAudio;
	std::vector<float> _popAnimationCurve;
	std::vector<float> _clickAnimationCurve;
	std::vector<float> _shakeAnimationCurve;
	std::vector<float> _moveAnimationCurve;
	float _animationTimeFast;
	float _animationTimeSlow;
	int _type;
};
