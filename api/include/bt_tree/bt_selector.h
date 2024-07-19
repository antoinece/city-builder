#ifndef API_BT_TREE_BT_SELECTOR_H
#define API_BT_TREE_BT_SELECTOR_H

#include <iostream>

#include "bt_node.h"

using namespace behaviour_tree;

class BtSelector : public BtNodeList
{
public:
	Status Process() override;
	~BtSelector() override = default;
};

inline Status BtSelector::Process()
{

	if (current_child_ < children_.size())
	{
		const Status status = children_[current_child_]->Process();

		if (status == Status::kFailure)
		{
			//std::cout << "Next leaf !" << std::endl;

			children_[current_child_]->Reset();

			current_child_++;
			if (current_child_ >= children_.size())
			{
				current_child_ = 0;
				return Status::kFailure;
			}else
			{
				return Status::kRunning;
			}
		}

		return status;

	}

	return Status::kFailure;

}

#endif // BT_SELECTOR_H
