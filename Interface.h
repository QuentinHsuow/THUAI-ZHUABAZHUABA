#ifndef INTERFACE_H_
#define INTERFACE_H_
class ICamp
{
public:
	virtual int** getCurrentPlants() = 0;
	virtual int*** getCurrentZombies() = 0;
	virtual int getSun() = 0;
	virtual int* getPlantCD() = 0;
	virtual int* getLeftLines() = 0;
	virtual int getRows() = 0;
	virtual int getColumns() = 0;
	virtual int getCurrentType() = 0;
};
class IPlayer
{
public:
	ICamp* Camp;
	virtual void PlacePlant(int type, int x, int y) = 0;
	virtual void PlaceZombie(int type, int y) = 0;
	virtual int getTime() = 0;
	virtual int getScore() = 0;
	virtual int getKillPlantsScore() = 0;
	virtual int getKillZombiesScore() = 0;
	virtual int getNotBrokenLines() = 0;
	virtual int getBrokenLinesScore() = 0;
	virtual int getLeftPlants() = 0;
	virtual void removePlant(int x, int y) = 0;
};

#endif