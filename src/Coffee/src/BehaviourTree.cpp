#include "../include/BehaviourTree.hpp"

namespace Coffee::BehaviourTree
{
    Node::Node()
    {
        _currentRunningNode = nullptr;
        _hasEntered = false;
    }

    void Node::onEnter()
    {
        _hasEntered = true;
    }

    void Node::onExit()
    {
        _hasEntered = false;
    }

    Status Node::execute()
    {
        if (!_hasEntered)
        {
            onEnter();
        }
        for (std::shared_ptr<Node> child : _children)
        {
            Status status = child->execute();
            if (status == Status::RUNNING)
            {
                return Status::RUNNING;
            }
            else if (status == Status::FAILURE)
            {
                onExit();
                return Status::FAILURE;
            }
        }
        onExit();
        return Status::SUCCESS; // All children succeeded
    }

    void Node::addChild(std::shared_ptr<Node> child)
    {
        child->_parent = shared_from_this();
        _children.push_back(child);
    }

    Status Root::execute()
    {
        return Node::execute();
    }

    Status Sequence::execute()
    {
        return Node::execute();
    }

    // // Action node: performs an action
    Action::Action(std::function<bool()> actionFunc)
    {
        _action = actionFunc;
    }

    Status Action::execute()
    {
        // Perform the action
        if (_action())
        {
            return Status::SUCCESS;
        }
        return Status::FAILURE;
    }

    Condition::Condition(std::function<bool()> conditionFunc)
    {
        _condition = conditionFunc;
        _trueChild = nullptr;
        _falseChild = nullptr;
    }

    Status Condition::execute()
    {
        if (_condition != nullptr && _condition())
        {
            if (_trueChild != nullptr)
                return _trueChild->execute();
        }
        else
        {
            if (_falseChild != nullptr)
                return _falseChild->execute();
        }
        return Status::FAILURE;
    }

    void Condition::onTrue(std::shared_ptr<Node> trueChild)
    {
        _trueChild = trueChild;
    }

    void Condition::onFalse(std::shared_ptr<Node> falseChild)
    {
        _falseChild = falseChild;
    }

    // Utility node: performs an utility
    void Utility::addAction(const std::shared_ptr<UtilityNode> action)
    {
        _children.push_back(action);
    }

    Status Utility::execute()
    {
        float highestUtility = 0.0f;
        std::shared_ptr<UtilityNode> bestAction = nullptr;

        // Find the child with the highest utility
        for (const auto &child : _children)
        {
            float utility = child->GetUtility();
            if (utility > highestUtility)
            {
                highestUtility = utility;
                bestAction = child;
            }
        }

        // Execute the best action
        if (bestAction != nullptr)
        {
            return bestAction->execute();
        }
        return Status::FAILURE;
    }

    // Repeater node: repeats a child node a number of times
    // Use -1 for infinite loop
    Repeater::Repeater(int count)
    {
        _repeatCount = count;
    }

    void Repeater::setChild(std::shared_ptr<Node> child)
    {
        _child = child;
    }

    void Repeater::onEnter()
    {
        Node::onEnter();
        _i = 0;
    }

    Status Repeater::execute()
    {
        if (!_hasEntered)
        {
            onEnter();
        }
        if (_repeatCount <= -1)
        {
            while (true)
            {
                _child->execute();
                return Status::RUNNING;
            }
        }
        else
        {
            while (_i < _repeatCount)
            {
                if(_child->execute() != Status::RUNNING) _i++;
                return Status::RUNNING;
            }
            Node::onExit();
            return Status::SUCCESS;
        }
        Node::onExit();
        return Status::SUCCESS;
    }

    Wait::Wait(float seconds)
    {
        _waitTime = (int32_t)seconds * 1000;
    }

    void Wait::onEnter()
    {
        Node::onEnter();
        _startTime = Time::GetTicks();
    }

    Status Wait::execute()
    {
        if (!_hasEntered)
        {
            onEnter();
        }
        if (Time::GetTicks() >= _startTime + _waitTime)
        {
            onExit();
            return Status::SUCCESS;
        }
        return Status::RUNNING;
    }
} // namespace Coffee::BehaviourTree