#ifndef API_BT_TREE_BT_NODE_H_
#define API_BT_TREE_BT_NODE_H_

#include <memory>
#include <vector>


namespace behaviour_tree
{


	enum class Status
	{
		kRunning,
		kFailure,
		kSuccess
	};

	class BtNode
	{
	
	public:
		BtNode() = default;
		virtual ~BtNode() = default;
		virtual Status Process() = 0;
		virtual void Reset() = 0;

	};

	class BtNodeList : public BtNode
	{

	protected:
		int current_child_ = 0;
		std::vector<BtNode*> children_;

	public:
		void Add(BtNode* node)
		{
			children_.push_back(node);
		}
		void Reset() override;

	};

}
#endif // BT_NODE_H
