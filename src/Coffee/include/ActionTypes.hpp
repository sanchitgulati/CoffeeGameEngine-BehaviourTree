#pragma once


#pragma once
#include<vector>
#include<memory>
#include<algorithm>
#include<queue>
#include "Time.hpp"
#include <vector>
#include "../include/ActionSystem.hpp"
#include "GameObject.hpp"
#include <functional>

namespace Coffee {
	

	class ScaleTo : public Action {
		int _startTime;
		int _endTime;
		std::shared_ptr<GameObject> _go;
		std::vector<float> _curveInfo;
		float _valueFrom;
		float _valueTo;
		std::shared_ptr<GameObject> _target;
	public:
		ScaleTo(std::shared_ptr<GameObject> target, float valueFrom, float valueTo, float seconds, std::vector<float> curveInfo = { 0.33f, 1.f, 0.68f, 1.f });
		void execute() override;
	};


	class MoveTo : public Action {
		int _startTime;
		int _endTime;
		std::shared_ptr<GameObject> _go;
		std::vector<float> _curveInfo;
		vector2 _valueFrom;
		vector2 _valueTo;
		std::shared_ptr<GameObject> _target;
	public:
		MoveTo(std::shared_ptr<GameObject> target, vector2 valueFrom, vector2 valueTo, float seconds, std::vector<float> curveInfo = { 0.33f, 1.f, 0.68f, 1.f });
		void execute() override;
	};


	class FuncCall : public Action {
	private:
		std::function<void()> _func;
	public:
		FuncCall(std::function<void()> function);
		void execute() override;
	};

	class Delay : public Action {
		int _dt;
		int _startTime;
	public:
		Delay(float dt);
		void execute() override;
	};

#define SCALE_TO std::make_shared<ScaleTo>
#define DELAY std::make_shared<Delay>
#define FUNC_CALL std::make_shared<FuncCall>
#define MOVE_TO std::make_shared<MoveTo>
}
