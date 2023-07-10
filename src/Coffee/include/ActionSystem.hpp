#pragma once
#include<vector>
#include<memory>
#include<algorithm>
#include<queue>
#include "Time.hpp"
#include <vector>

namespace Coffee {
	class Curve
	{
	public:
		static float linear(float curValue, float finalValue, float delta) { return curValue + (finalValue - curValue) * delta; }

		//refer to https://cubic-bezier.com/ for desired curve
		static float cubicBezier(double delta, std::vector<float> curveData = { 0.33f, 1.f, 0.68f, 1.f }) {
			return static_cast<float>(pow(1.0 - delta, 3.0) * curveData[0] + 3.0 * delta * pow(1.0 - delta, 2.0) * curveData[1] + 3 * pow(delta, 2.0) * (1.0 - delta) * curveData[2]
				+ pow(delta, 3) * curveData[3]);
		}
	};

	class Action : public std::enable_shared_from_this<Action>{
	protected:
	public:
		bool _isDone;
		Action();
		virtual void execute() {};
	};

}
