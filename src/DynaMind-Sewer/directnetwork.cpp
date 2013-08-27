/**
 * @file
 * @author  Chrisitan Urich <christian.urich@gmail.com>
 * @version 1.0
 * @section LICENSE
 *
 * This file is part of DynaMind
 *
 * Copyright (C) 2012  Christian Urich
 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "directnetwork.h"
#include <algorithm>

DM_DECLARE_NODE_NAME(DirectNetwork, Sewer)
DirectNetwork::DirectNetwork()
{
	std::vector<DM::View> views;
	this->conduits = DM::View("NETWORK", DM::EDGE, DM::MODIFY);
	this->outfalls = DM::View("ENDPOINT", DM::NODE, DM::MODIFY);
	this->startpoints = DM::View("STARTPOINT", DM::NODE, DM::WRITE);

	views.push_back(conduits);
	views.push_back(outfalls);

	this->addData("Vec", views);
}

void DirectNetwork::run() {

	sys = this->getData("Vec");

	std::vector<std::string> s_outfalls = sys->getUUIDsOfComponentsInView(this->outfalls);
	std::vector<DM::Node*> outfalls;
	foreach (std::string s, s_outfalls) {
		outfalls.push_back(sys->getNode(s));
	}


	//Create EdgeList
	std::vector<std::string> s_edges = sys->getUUIDsOfComponentsInView(this->conduits);



	foreach (std::string s, s_edges) {
		DM::Edge * e = sys->getEdge(s);
		e->addAttribute("VISITED", 0);
		std::vector<std::string> v1 = ConnectionList[e->getStartpointName()];
		v1.push_back(s);
		ConnectionList[e->getStartpointName()]  = v1;
		std::vector<std::string> v2 = ConnectionList[e->getEndpointName()];
		v2.push_back(s);
		ConnectionList[e->getEndpointName()]= v2;

	}

	foreach (std::string s,s_outfalls ) {
		NextEdge(s);
	}

}

void DirectNetwork::NextEdge(std::string startnode) {
	std::vector<std::string> connected;
	if (ConnectionList[startnode].size() == 1) {
		sys->addComponentToView(sys->getNode(startnode), this->startpoints);
	}
	foreach (std::string s, ConnectionList[startnode]) {
		if (std::find(visitedEdges.begin(), visitedEdges.end(), s) ==   visitedEdges.end()) {
			connected.push_back(s);
		}
	}
	//Diameter Sorted max first
	std::vector<std::string> connected_new;
	while (connected.size() > 0) {
		std::string maxID = "";
		double maxDiameter = 0;
		for (int i = 0; i < connected.size(); i++) {
			if (i == 0) {
				maxID = connected[i];
			}
			if (sys->getEdge(connected[i])->getAttribute("DIAMETER")->getDouble() > maxDiameter) {
				maxDiameter = sys->getEdge(connected[i])->getAttribute("DIAMETER")->getDouble();
				maxID = connected[i];

			}

		}
		connected.erase(std::find(connected.begin(), connected.end(), maxID));
		connected_new.push_back(maxID);
	}



	connected = connected_new;
	foreach (std::string s, connected) {
		DM::Edge * e = sys->getEdge(s);
		e->getAttribute("VISITED")->setDouble(1);
		if (e->getStartpointName().compare(startnode)==0) {
			e->setStartpointName(e->getEndpointName());
			e->setEndpointName(startnode);
		}
		this->visitedEdges.push_back(s);
		NextEdge(e->getStartpointName());
	}
}



