
#include "gameplay/stones_man.h"


#include <iostream>
#include <random>

#include "sfml_vec2f.h"
#include "bt_tree/bt_leaf.h"
#include "pathfinding/path_finder.h"

using namespace behaviour_tree;

Stonesman::Stonesman(float x, float y, float linear_speed, Tilemap& tilemap) : Walker(x, y, linear_speed), tilemap_(tilemap)
{
	Stonesman::DefineTexture();

	rect_.setPosition(shape_.getGlobalBounds().getPosition());
	rect_.setSize(shape_.getGlobalBounds().getSize());


	homePosition = sf::Vector2f(x, y);
	InitiateBehaviours();

}

Stonesman::~Stonesman()
{
	//std::cout << "What happens Woodsman ?" << std::endl;
}

Stonesman::Stonesman(const Stonesman& w) : Walker(w), tilemap_(w.tilemap_)
{
	stamina_ = w.stamina_;
	InitiateBehaviours();
}

void Stonesman::DefineTexture()
{
	shape_.setTexture(ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kStoneMan));
}

void Stonesman::InitiateBehaviours()
{
	stamina_ = 3;

	Path p = Pathfinder::CalculatePath(tilemap_.GetWalkables(), LastDestination(), getPosition(), 64);
	set_path(p);

	BtLeaf* check_stamina = new BtLeaf("check stamina", [this]()
		{

			//std::cout << "Check Stamina : " << stamina_ << std::endl;

			if (stamina_ >= 0)
				return Status::kSuccess;
			else
				return Status::kFailure;

		}
	);

	BtLeaf* seek_wood = new BtLeaf("seek", [this]()
		{
			return SeekCaillou();
		}
	);

	BtLeaf* gather_wood = new BtLeaf("gather", [this]()
		{
			return GatherCaillou();
		}
	);

	BtLeaf* back_home = new BtLeaf("back", [this]()
		{
			return BackHome();
		}
	);

	BtLeaf* refill_stamina = new BtLeaf("check stamina", [this]()
		{
			stamina_ = PickNewStamina();
			//std::cout << "Refill Stamina : " << stamina_ << std::endl;
			return Status::kFailure;
		}
	);

	std::unique_ptr<BtSelector> main_select = std::make_unique<BtSelector>();

	BtSequence* gather_sequence = new BtSequence();
	BtSequence* home_sequence = new BtSequence();

	main_select->Add(gather_sequence);
	main_select->Add(home_sequence);

	gather_sequence->Add(check_stamina);
	gather_sequence->Add(seek_wood);
	gather_sequence->Add(gather_wood);

	home_sequence->Add(back_home);
	home_sequence->Add(refill_stamina);

	bt_tree_.Attach(main_select);

}

void Stonesman::Tick()
{
	// -------------------------------------
	Walker::Tick();
	// -------------------------------------
	bt_tree_.Tick();
}

Status Stonesman::SeekCaillou()
{
	sf::Vector2f closestCaillou = tilemap_.GetClosestCaillou(getPosition());

	if (squaredMagnitude(closestCaillou - path_.FinalDestination()) > std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Recalculate path" << std::endl;
		Path p = Pathfinder::CalculatePath(tilemap_.GetWalkables(), LastDestination(), closestCaillou, 16);
		set_path(p);

		// - - - - - - - - - - - - - - -
		stamina_ -= p.GetSteps().size();

	}

	if (!path_.IsAvailable())
	{
		//std::cout << "Path not available" << std::endl;
		return Status::kFailure;
	}

	float sq_mag = squaredMagnitude(getPosition() - path_.FinalDestination());
	if (sq_mag < std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Arrived !!!!!!" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		//std::cout << "Not arrived yet" << std::endl;
		return Status::kRunning;
	}

}


Status Stonesman::GatherCaillou()
{

	if (tilemap_.GatherCaillou(getPosition()))
	{
		//std::cout << "Cutting caillou" << std::endl;
		return Status::kSuccess;
	}

	//std::cout << "not Cutting trees" << std::endl;
	return Status::kFailure;

}

Status Stonesman::BackHome()
{

	sf::Vector2f closestHome = tilemap_.GetClosestHome(getPosition());

	if (squaredMagnitude(closestHome - path_.FinalDestination()) > std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Recalculate path" << std::endl;
		Path p = Pathfinder::CalculatePath(tilemap_.GetWalkables(), LastDestination(), closestHome, 16);
		set_path(p);

		// - - - - - - - - - - - - - - -
		stamina_ -= p.GetSteps().size();

	}

	if (!path_.IsAvailable())
	{
		//std::cout << "Path not available" << std::endl;
		return Status::kFailure;
	}

	float sq_mag = squaredMagnitude(getPosition() - path_.FinalDestination());
	if (sq_mag < std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Arrived !!!!!!" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		//std::cout << "Not arrived yet" << std::endl;
		return Status::kRunning;
	}
	/*
	if (squaredMagnitude(homePosition - path_.FinalDestination()) > std::numeric_limits<float>::epsilon())
	{
		Path p = Pathfinder::CalculatePath(tilemap_.GetWalkables(), LastDestination(), homePosition, 16);
		set_path(p);
	}

	if (!path_.IsAvailable())
	{
		//std::cout << "Path not available" << std::endl;
		return Status::kFailure;
	}

	if (squaredMagnitude(getPosition() - path_.FinalDestination()) < std::numeric_limits<float>::epsilon())
	{
		//std::cout << "Arrived at home !!!!!!" << std::endl;
		return Status::kSuccess;
	}
	else
	{
		//std::cout << "Not arrived yet at home" << std::endl;
		return Status::kRunning;
	}*/

}

int Stonesman::PickNewStamina()
{

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> int_distribution(1, 5); // distribution in range [1, 6]

	return int_distribution(rng);

}
