#pragma once
#include<vector>
#include<memory>
#include<algorithm>
#include "SDL_rect.h"
#include <SDL.h>
#include "Transform.hpp"
#include "ActionSystem.hpp"
#include "Sequence.hpp"

namespace Coffee {
	class GameObject : public std::enable_shared_from_this<GameObject> {
	public:
		static std::shared_ptr<GameObject> create();
		virtual void init();
		virtual void draw(matrix4 &projection);
		virtual void update(float dt);
		bool isVisible() const;
		void setVisible(const bool& visibility);
		void addChild(const std::shared_ptr<GameObject>& child);
		std::vector<std::shared_ptr<GameObject>> getChildren() const;
		void removeChild(const std::shared_ptr<GameObject>& child);
		void deleteChild(const std::shared_ptr<GameObject>& child);
		virtual void removeChildren();
		void setParent(const std::shared_ptr<GameObject>& parent);
		std::shared_ptr<GameObject> getParent() const;

		void setPosition(vector2 position);
		void setPosition(float x, float y);
		void setGlobalPosition(vector2 position);
		void setGlobalPosition(float x, float y);
		vector2 getPosition();
		void setScale(vector2 scale);
		void setScale(float scale);
		vector2 getScale();
		void setRotation(float rotation);
		float getRotation();
		bool isIntersecting(vector2& point);
		std::shared_ptr<Sequence> makeSequence();
		vector2 isTestingIntersecting(vector2& point);

	protected:
		bool _isDirty;
		std::vector<std::shared_ptr<Sequence>> _sequence;
		matrix4 _mTransform, _mTransformInverse;
		virtual void objectAddedAsAChild();
		std::vector<std::shared_ptr<GameObject>> _children;
		Transform2D _transform;
		Transform2D _globalTransform;
		Transform2D getWorldTransform();
		glm::vec4 AABB();
		vector2 _size;
		void refreshTransform();
		vector2 PointRotate(vector2 point, float angle, vector2 centerOfRotation);
	private:
		std::shared_ptr<GameObject> _parent = nullptr;
		bool _visible = true;
	};
}