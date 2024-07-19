#ifndef API_GAMEPLAY_STONES_MAN_H
#define API_GAMEPLAY_STONES_MAN_H

#include "Walker.h"
#include "bt_tree/bt_tree.h"
#include "graphics/Tilemap.h"

class Stonesman : public Walker
{
private:
	Tilemap& tilemap_;

	behaviour_tree::BtTree bt_tree_;

	int stamina_ = 1;
	sf::Vector2f homePosition;
public:
	Stonesman(float x, float y, float linear_speed, Tilemap& tilemap);
	~Stonesman() override;
	Stonesman(const Stonesman& w);
	
	void DefineTexture() override;

	void InitiateBehaviours();
	void Tick();

	behaviour_tree::Status SeekCaillou();
	behaviour_tree::Status GatherCaillou();
	behaviour_tree::Status BackHome();

	int PickNewStamina();
};

#endif // WOODS_MAN_H
