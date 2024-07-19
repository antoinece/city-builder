#include "bt_tree/bt_tree.h"

#include <iostream>


using namespace behaviour_tree;

void BtTree::Tick()
{
	if (root_ != nullptr)
	{
		Status status = root_->Process();
	}

}

void BtTree::Attach(std::unique_ptr<BtLeaf>& node)
{
	root_ = std::move(node);
}

void BtTree::Attach(std::unique_ptr<BtSequence>& node)
{
	root_ = std::move(node);
}

void BtTree::Attach(std::unique_ptr<BtSelector>& node)
{
	root_ = std::move(node);
}
