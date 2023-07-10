#include "../include/ActionTypes.hpp"


namespace Coffee {

	ScaleTo::ScaleTo(std::shared_ptr<GameObject> target, float valueFrom, float valueTo, float seconds, std::vector<float> curveInfo) : Action() {
		_isDone = false;
		_startTime = Time::GetTicks();
		_endTime = static_cast<int>(_startTime + seconds * 1000);
		_valueFrom = valueFrom;
		_valueTo = valueTo;
		_curveInfo = curveInfo;
		_target = target;
	}

	void ScaleTo::execute() {
		if (Time::GetTicks() < _endTime) {
			auto t = Time::GetTicks();
			float cur = (t - _startTime) / (static_cast<float>(_endTime - _startTime));
			auto val = Curve::cubicBezier(cur, _curveInfo);
			_target->setScale(_valueFrom + (_valueTo - _valueFrom) * val);
		}
		else {
			_target->setScale(_valueTo);
			_isDone = true;
		}
	}


	void Delay::execute() {
		if (_dt + _startTime < Time::GetTicks()) {
			_isDone = true;
		}
	}


	Delay::Delay(float dt) : Action() {
		_isDone = false;
		_startTime = Time::GetTicks();
		_dt = static_cast<int>(dt * 1000);
	}


	FuncCall::FuncCall(std::function<void()> function)
	{
		_func = function;
	}

	void FuncCall::execute() {
		std::invoke(_func);
		_isDone = true;
	}

	MoveTo::MoveTo(std::shared_ptr<GameObject> target, vector2 valueFrom, vector2 valueTo, float seconds, std::vector<float> curveInfo)
	{
		_isDone = false;
		_startTime = Time::GetTicks();
		_endTime = static_cast<int>(_startTime + seconds * 1000);
		_valueFrom = valueFrom;
		_valueTo = valueTo;
		_curveInfo = curveInfo;
		_target = target;
	}

	void MoveTo::execute()
	{
		if (Time::GetTicks() < _endTime) {
			auto t = Time::GetTicks();
			float cur = (t - _startTime) / (static_cast<float>(_endTime - _startTime));
			auto val = Curve::cubicBezier(cur, _curveInfo);
			_target->setPosition(_valueFrom + (_valueTo - _valueFrom) * val);
		}
		else {
			_target->setPosition(_valueTo);
			_isDone = true;
		}
	}

}