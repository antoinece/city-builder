#ifndef API_BT_TREE_BT_LEAF_H
#define API_BT_TREE_BT_LEAF_H

#include <functional>
#include <iostream>
#include <string>

#include "bt_node.h"

namespace behaviour_tree
{

	class BtLeaf final : public BtNode
	{

	private:
		//std::function<Status()> leaf_action_;
		std::string name_;

	public:
		~BtLeaf() override = default;
		BtLeaf(std::string name, const std::function<Status()>& leaf_action) : leaf_action_(leaf_action), name_(name) {};
	

		Status Process() override;
		void Reset() override {};

		void SetAction(const std::function<Status()>& leaf_action)
		{
			leaf_action_ = leaf_action;
		}

		std::function<Status()> leaf_action_;

	};

	inline Status BtLeaf::Process()
	{

		//std::cout << "Leaf Process : " << name_ << std::endl;

		if (leaf_action_ != nullptr)
			return leaf_action_();
		else
			return Status::kFailure;

	}


}




#endif // API_BT_TREE_BT_LEAF_H
