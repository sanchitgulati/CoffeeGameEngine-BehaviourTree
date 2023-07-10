#include "Gem.hpp"
#include "../GameValues.hpp"
using namespace Coffee;

std::shared_ptr<Gem> Gem::createWithFile(const std::string& filePath)
{
	auto candy = std::make_shared<Gem>();
	candy->init(filePath);
	candy->Sprite::init();
	return candy;
}

void Gem::init(const std::string& filepath)
{
	initWithFile(filepath);
	_defaultScale = 0.2f;
	_selectedScale = 0.25f;
	_popAudio = GameValues::sfxBLOP;
	_unpopAudio = GameValues::sfxPLOB;
	_popAnimationCurve = { .11f, 0.f, .1f, 1.95f };
	_clickAnimationCurve = { .11f, 0.f, .1f, 1.95f };
	_shakeAnimationCurve = { .07f, .86f, .19f, .9f };
	_moveAnimationCurve = { .07f, .86f, .19f, .9f };
	_animationTimeFast = 0.1f;
	_animationTimeSlow = 0.2f;
	_shakeDelta = 10.f;
	setScale(0.f);
}

int Gem::getType()
{
	return _type;
}

void Gem::setType(int type)
{
	_type = type;
}

void Gem::pop(float delay)
{
	makeSequence()->add(DELAY(delay))
		->add(FUNC_CALL([this]() {AudioManager.playAudio(_popAudio); }))
		->add(SCALE_TO(shared_from_this(), 0.f, _defaultScale+0.1f, _animationTimeSlow, _popAnimationCurve))
		->add(SCALE_TO(shared_from_this(), _defaultScale+0.1f, _defaultScale, _animationTimeFast, _popAnimationCurve));
}

void Gem::normal()
{
	makeSequence()
		->add(SCALE_TO(shared_from_this(), _selectedScale, _defaultScale, _animationTimeSlow, _clickAnimationCurve));
}

void Gem::selected()
{
	makeSequence()
		->add(SCALE_TO(shared_from_this(), _defaultScale, _selectedScale, _animationTimeSlow, _clickAnimationCurve));
}
void Gem::removeWithAnim(std::shared_ptr<GameObject> grid, std::function<void()> func)
{
	AudioManager.playAudio(_unpopAudio);
	makeSequence()
		->add(DELAY((static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*0.2f))
		->add(SCALE_TO(shared_from_this(), _defaultScale, 0.f, _animationTimeFast, _popAnimationCurve))
		->add(FUNC_CALL([this, grid]() {grid->removeChild(shared_from_this()); }))
		->add(FUNC_CALL([func]() { if (func != nullptr)std::invoke(func); }));
}

void Gem::shake(Direction direction)
{
	vector2 shakeDeltaVector {0,0};
	switch (direction)
	{
	case Direction::UP:
		shakeDeltaVector.y = -_shakeDelta;
		break;
	case Direction::DOWN:
		shakeDeltaVector.y = _shakeDelta;
		break;
	case Direction::RIGHT:
		shakeDeltaVector.x = _shakeDelta;
		break;
	case Direction::LEFT:
		shakeDeltaVector.x = -_shakeDelta;
		break;
	default:
		break;
	}
	auto p1 = getPosition();
	auto p2 = vector2(p1.x + shakeDeltaVector.x, p1.y + shakeDeltaVector.y);
	auto p3 = p1;
	auto p4 = vector2(p1.x - shakeDeltaVector.x, p1.y - shakeDeltaVector.y);
	auto p5 = p1;
	makeSequence()
		->add(MOVE_TO(shared_from_this(), p1, p2, _animationTimeFast, _shakeAnimationCurve))
		->add(MOVE_TO(shared_from_this(), p2, p3, _animationTimeFast, _shakeAnimationCurve))
		->add(MOVE_TO(shared_from_this(), p3, p4, _animationTimeFast, _shakeAnimationCurve))
		->add(MOVE_TO(shared_from_this(), p4, p5, _animationTimeFast, _shakeAnimationCurve));
}

void Gem::moveTo(vector2 pos1, vector2 pos2,std::function<void()> func)
{
	makeSequence()
		->add(MOVE_TO(shared_from_this(), pos1, pos2, _animationTimeSlow))
		->add(FUNC_CALL([func]() { if(func != nullptr )std::invoke(func); }));
}
