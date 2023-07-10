#include "../include/GameObject.hpp"
#pragma once

namespace Coffee {
	std::shared_ptr<GameObject> GameObject::create()
	{
		auto go = std::make_shared<GameObject>();
		go->init();
		return go;
	}
	void GameObject::init() {
		_sequence = std::vector<std::shared_ptr<Sequence>>();
	}

	void GameObject::draw(glm::mat4 &projection) {
		for (auto child : _children) {
			if (child->isVisible()) {
				child->draw(projection);
			}
		}
	}

	void GameObject::update(float dt) {
		for (auto seq : _sequence) {
			seq->execute();
		}
		for (auto child : _children) {
			if(child != nullptr) child->update(dt);
		}
	}

	bool GameObject::isVisible() const {
		return _visible;
	}

	void GameObject::setVisible(const bool& visibility) {
		_visible = visibility;
	}

	void GameObject::addChild(const std::shared_ptr<GameObject>& child) {
		if (shared_from_this() == child)
		{
			printf("ERROR::ADDED_CHILD_TO_SELF");
		}
		child->_parent = shared_from_this();
		_children.push_back(child);
		objectAddedAsAChild();
	}

	std::vector<std::shared_ptr<GameObject>> GameObject::getChildren() const {
		return _children;
	}

	void GameObject::deleteChild(const std::shared_ptr<GameObject>& child) {
		child->removeChildren();
		removeChild(child);
	}

	void GameObject::removeChild(const std::shared_ptr<GameObject>& child) {
		std::vector<std::shared_ptr<GameObject>>::iterator it = find(_children.begin(), _children.end(), child);
		if(it != _children.end())_children.erase(it);
	}

	void GameObject::removeChildren() {
		for (auto child : _children) {
			child->removeChildren();
		}
		_children.clear();
	}

	void GameObject::setParent(const std::shared_ptr<GameObject>& parent) {
		_parent->removeChild(shared_from_this());
		_parent = parent;
		parent->addChild(shared_from_this());
	}

	std::shared_ptr<GameObject> GameObject::getParent() const {
		return _parent;
	}

	void GameObject::setPosition(vector2 position)
	{
		_transform.position = position;
		refreshTransform();
	}

	void GameObject::setPosition(float x, float y)
	{
		setPosition(vector2(x, y));
	}

	void GameObject::setGlobalPosition(vector2 position)
	{
		//setPosition(_globalTransform.position + position);
		_globalTransform.position = position;
		_isDirty = true;
	}

	void GameObject::setGlobalPosition(float x, float y)
	{
		setGlobalPosition(vector2(x, y));
	}

	vector2 GameObject::getPosition()
	{
		return _transform.position;
	}

	void GameObject::setScale(vector2 scale)
	{
		_transform.scale = scale;
		refreshTransform();
	}

	void GameObject::setScale(float scale)
	{
		setScale(vector2(scale, scale));
	}

	vector2 GameObject::getScale()
	{
		return _transform.scale;
	}

	void GameObject::setRotation(float rotation)
	{
		_transform.rotation = rotation;
		refreshTransform();
	}

	float GameObject::getRotation()
	{
		return _transform.rotation;
	}

	bool GameObject::isIntersecting(vector2& point)
	{
		auto aabb = AABB();
		auto aaPoint = PointRotate(point, glm::radians(_globalTransform.rotation), _globalTransform.position);

		if (aaPoint.x > aabb.x && aaPoint.x < aabb.w) {
			if (aaPoint.y > aabb.y && aaPoint.y < aabb.z) {
				return true;
			}
		}
		return false;
	}

	std::shared_ptr<Sequence> GameObject::makeSequence()
	{
		auto seq = std::make_shared<Sequence>();
		seq->init();
		_sequence.push_back(seq);
		return seq;
	}

	vector2 GameObject::isTestingIntersecting(vector2& point)
	{
		return  PointRotate(point, glm::radians(_globalTransform.rotation), _globalTransform.position);
	}


	void GameObject::objectAddedAsAChild() {
		refreshTransform();
	}

	Transform2D GameObject::getWorldTransform()
	{
		Transform2D transform;
		std::shared_ptr<GameObject> cur = shared_from_this();
		while (cur->getParent() != nullptr) {
			cur = cur->getParent();
			transform.position += cur->_transform.position;
			//transform.position = PointRotate(transform.position, _transform.rotation, cur->_transform.position);
			transform.rotation += cur->_transform.rotation;
			transform.scale *= cur->_transform.scale;
		}
		transform.position += _transform.position;
		transform.rotation += _transform.rotation;
		transform.scale *= _transform.scale;
		return transform;
	}

	glm::vec4 GameObject::AABB()
	{
		glm::vec4 ret;
		ret.x = _globalTransform.position.x - (_size.x*_globalTransform.scale.x) / 2;
		ret.y = _globalTransform.position.y - (_size.y * _globalTransform.scale.x) / 2;
		ret.w = _globalTransform.position.x + (_size.x * _globalTransform.scale.x) / 2;
		ret.z = _globalTransform.position.y + (_size.y * _globalTransform.scale.x) / 2;
		return ret;
	}

	void GameObject::refreshTransform()
	{
		_isDirty = true;
		_globalTransform = getWorldTransform();
		for (auto child : _children) {
			child->refreshTransform();
		}
	}

	vector2 GameObject::PointRotate(vector2 point, float angle, vector2 centerOfRotation)
	{
		float sinus = sin(angle);
		float cosinus = cos(angle);
		vector2 temp;

		point = point - centerOfRotation;
		temp.x = point.x * cosinus - point.y * sinus;
		temp.y = point.x * sinus + point.y * cosinus;
		point = temp + centerOfRotation;

		return point;
	}
}