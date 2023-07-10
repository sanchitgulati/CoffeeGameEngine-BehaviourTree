#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include "Time.hpp"

namespace Coffee::BehaviourTree
{
    enum class Status
    {
        SUCCESS,
        FAILURE,
        RUNNING
    };
    // Base class for all nodes
    class Node : public std::enable_shared_from_this<Node> 
    {
    private:
        std::shared_ptr<Node> _currentRunningNode;
        std::shared_ptr<Node> _parent;
        std::vector<std::shared_ptr<Node>> _children;

    protected:
        bool _hasEntered = false;

    public:
        Node();
        void addChild(std::shared_ptr<Node> child);
        virtual void onEnter();
        virtual void onExit();
        virtual Status execute() = 0;
    };

    // Define the base class for utility AI actions
    class UtilityNode : Node
    {
    public:
        virtual float GetUtility() const = 0;
        virtual Status execute() = 0;
    };

    // Selector node: executes children nodes until one succeeds
    class Root : public Node
    {
    private:
        std::map<std::string, float> _blackboard;

    public:
        Status execute() override;
    };

    // Sequence node: executes children nodes until one fails
    class Sequence : public Node
    {
        Status execute() override;
    };

    // Action node: performs an action
    class Action : public Node
    {
    private:
        std::function<bool()> _action;

    public:
        Action(std::function<bool()> actionFunc);
        Status execute() override;
    };

    // Condition node: performs an condition
    class Condition : public Node
    {
    private:
        std::function<bool()> _condition;
        std::shared_ptr<Node> _trueChild;
        std::shared_ptr<Node> _falseChild;

    public:
        Condition(std::function<bool()> conditionFunc);
        void onTrue(std::shared_ptr<Node> trueChild);
        void onFalse(std::shared_ptr<Node> falseChild);
        Status execute() override;
    };

    // Condition node: performs an condition
    class Utility : public Node
    {
    private:
        std::function<bool()> _utilityFunc;
        std::vector<std::shared_ptr<UtilityNode>> _children;

    public:
        Utility();
        Status execute() override;
        void addAction(const std::shared_ptr<UtilityNode> action);
    };

    class Repeater : public Node
    {
    private:
        int _repeatCount;
        int _i;
        std::shared_ptr<Node> _child;

    public:
        void onEnter() override;
        Repeater(int count);
        void setChild(std::shared_ptr<Node> child);
        Status execute() override;
    };

    class Wait : public Node
    {
    private:
        int32_t _waitTime;
        int32_t _startTime;
        std::shared_ptr<Node> _child;

    public:
        void onEnter() override;
        Wait(float seconds);
        Status execute() override;
    };
}