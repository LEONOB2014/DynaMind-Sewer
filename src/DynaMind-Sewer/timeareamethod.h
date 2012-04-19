/**
 * @file
 * @author  Chrisitan Urich <christian.urich@gmail.com>
 * @version 1.0
 * @section LICENSE
 *
 * This file is part of DynaMind
 *
 * Copyright (C) 2011  Christian Urich

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
#ifndef TIMEAREAMETHOD_H
#define TIMEAREAMETHOD_H

#include <dmmodule.h>
#include <dm.h>


/*
* @ingroup Sewer
* @brief TimeAreaMethod
*
* @author Christian Urich
*/
class DM_HELPER_DLL_EXPORT TimeAreaMethod : public  DM::Module {

DM_DECLARE_NODE (TimeAreaMethod)

public:
    TimeAreaMethod();
void run();
private:
    DM::View conduit;
    DM::View inlet;
    DM::View shaft;
    DM::View wwtps;
    DM::View catchment;
    DM::View outfalls;
    DM::View weir;
    DM::View storage;
    DM::View globals;

    std::vector<DM::Node*> EndPointList;

    double v;
    double r15;
    double chooseDiameter(double diameter);
    double caluclateAPhi(DM::Component *  attr, double r15) const;


    std::map<DM::Node *, std::vector<DM::Edge*> > StartNodeSortedEdges;
    std::map<DM::Node *, std::vector<DM::Edge*> > EndNodeSortedEdges;
    std::map<DM::Node *, std::vector<DM::Edge*> > ConnectedEdges;




};

#endif // TIMEAREAMETHOD_H
