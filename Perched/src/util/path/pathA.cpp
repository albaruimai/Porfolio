//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#include "pathA.hpp"

bool PathA_t::isValid(int x, int y, std::vector<ECS::Entity_t *> &bsalientes, ECS::Entity_t* btunel, bool enTunel) { //If our Node is an obstacle it is not valid
	if (enTunel == false) {
		for(auto& sal: bsalientes){

			auto* col = sal->getComponent<ColliderComponent_t>();
			auto* phy = sal->getComponent<PhysicsComponent_t>();

			if(col != nullptr && phy != nullptr && col->properties == ColliderComponent_t::P_Saliente){
				for (auto& box: col->boxes) {
					if(x*12 > (box.box.xLeft + box.disX)+phy->x && x*12 <= (box.box.xRight + box.disX)+phy->x
					&& y*12 > (box.box.yUp + box.disY)+phy->y && y*12 <= (box.box.yDown + box.disY)+phy->y){

						return false;
					}
				}
			}
		}
	} else {
		if (btunel != nullptr) {
			auto* col = btunel->getComponent<ColliderComponent_t>();
			auto* phy = btunel->getComponent<PhysicsComponent_t>();

			if(col != nullptr && phy != nullptr && col->properties == ColliderComponent_t::P_PlanoS){
				for (auto& box: col->boxes) {
					if(x*12 > (box.box.xLeft + box.disX)+phy->x && x*12 <= (box.box.xRight + box.disX)+phy->x
					&& y*12 > (box.box.yUp + box.disY)+phy->y && y*12 <= (box.box.yDown + box.disY)+phy->y){

						return false;
					}
				}
			}
		}
	}
	

	return true;
}

bool PathA_t::isDestination(int x, int y, Casilla& dest){
	if (x == dest.x && y == dest.y) {
		return true;
	}

	return false;
}

double PathA_t::calculateH(int x, int y,Casilla& dest) {
	double H = (sqrt((x - dest.x)*(x - dest.x) + (y - dest.y)*(y - dest.y)));

	return H;
}

std::vector<Casilla> PathA_t::makePath(std::array<std::array < Casilla, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)>& map, Casilla& dest){
	//std::cout << "Found a path" << std::endl;
	int x = dest.x;
	int y = dest.y;
	std::stack<Casilla> path;
	std::vector<Casilla> usablePath;

	if (x < map.size() && y < map[x].size())
	{
		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
		&& map[x][y].x != -1 && map[x][y].y != -1) 
	{
		path.push(map[x][y]);
		int tempX = map[x][y].parentX;
		int tempY = map[x][y].parentY;
		x = tempX;
		y = tempY;
		
	}
	path.push(map[x][y]);

	while (!path.empty()) {
		Casilla top = path.top();
		path.pop();
		//std::cout << top.x << " " << top.y << "\n";
		usablePath.emplace_back(top);
	}
	}
	
	return usablePath;
}

std::vector<Casilla> PathA_t::aStar(Casilla& player, Casilla& dest, std::vector<ECS::Entity_t *> &bsalientes, ECS::Entity_t* btunel, bool enTunel) {
	
	std::vector<Casilla> empty;
	empty.reserve(1);
	
	if (isValid(dest.x, dest.y, bsalientes, btunel, enTunel) == false) {
		//std::cout << "Destination is an obstacle" << std::endl;
		return empty;
		//Destination is invalid
	}
	if (isDestination(player.x, player.y, dest)) {
		//std::cout << "You are the destination" << std::endl;
		return empty;
		//You clicked on yourself
	}

	//std::cout << "Inicio: " << player.x << "," << player.y << "\n";
	//std::cout << "Fin: " << dest.x << "," << dest.y << "\n";
	
	bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

	//Initialize whole map

	std::array<std::array < Casilla, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
	
	for (int x {0}; x < (X_MAX / X_STEP) && x<allMap.size(); ++x) {
		for (int y {0}; y < (Y_MAX / Y_STEP) && y<allMap.size(); ++y) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;		
		}
	}

	//Initialize our starting list
	int x = player.x;
	int y = player.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	//std::cout << "ALLMAP:\nSIZE: " << allMap.size() << " " << allMap[0].size() << "\n X and Y: " << x << " " <<y << "\n";

	std::vector<Casilla> openList;	

	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size()<(X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
		Casilla node;
		do {
			float temp = FLT_MAX;
			std::vector<Casilla>::iterator itNode = openList.begin();
			for (std::vector<Casilla>::iterator it = openList.begin(); it != openList.end(); it = next(it)) {
				Casilla n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					
					itNode = it;
				}
			}
			//std::cout<<"coste:"<<temp<<"\n";
			if(itNode != openList.begin()){
				node = *itNode;
				openList.erase(itNode);
			}
			
		} while (isValid(node.x, node.y, bsalientes, btunel, enTunel) == false);
		
		x = node.x;
		y = node.y;
		if (x<30 && y<90)
		{
			closedList[x][y] = true;	
		}
		
		//std::cout<<"Casilla actual:"<<x<<","<<y<<"\n";
		
		//For each neighbour starting from North-West to South-East
		for (int newX {-1}; newX <= 1; ++newX) {
			for (int newY {-1}; newY <= 1; ++newY) {
				double gNew, hNew, fNew;
				
				if (isValid(x + newX, y + newY, bsalientes, btunel, enTunel)) {
					if ((x+newX) < allMap.size() && (y+newY) < allMap[(x+newX)].size() && isDestination(x + newX, y + newY, dest))
					{
						//Destination found - make path
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;
							
						return makePath(allMap, dest);
					}
					else if (x+newX < 30 && y+newY < 80 && closedList[x + newX][y + newY] == false)
					{
						if(newX == newY){
							gNew = node.gCost + 1.414;
						} else {
							gNew = node.gCost + 1.0;
						}

						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						// Check if this path is better than the one already present
						
						if ((x+newX) < allMap.size() && (y+newY) < allMap[(x+newX)].size() && allMap[x + newX][y + newY].fCost == FLT_MAX ||
							allMap[x + newX][y + newY].fCost > fNew)
						{
							// Update the details of this neighbour node
							allMap[x + newX][y + newY].fCost = fNew;
							allMap[x + newX][y + newY].gCost = gNew;
							allMap[x + newX][y + newY].hCost = hNew;
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}

	//std::cout<<"HOLA PEPE\n";
	if (destinationFound == false) {
		//std::cout << "Destination not found" << std::endl;
		return empty;
	}
	return empty;
}