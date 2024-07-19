#ifndef API_BT_TREE_BT_TREE_H
#define API_BT_TREE_BT_TREE_H

#include <memory>

#include "bt_node.h"

#include "bt_tree/bt_leaf.h"
#include "bt_tree/bt_selector.h"
#include "bt_tree/bt_sequence.h"

namespace behaviour_tree
{
	class BtTree
	{
		std::unique_ptr<BtNode> root_;

	public:

		void Tick();

		void Attach(std::unique_ptr<BtLeaf>& node);
		void Attach(std::unique_ptr<BtSequence>& node);
		void Attach(std::unique_ptr<BtSelector>& node);

	};

}

#endif

