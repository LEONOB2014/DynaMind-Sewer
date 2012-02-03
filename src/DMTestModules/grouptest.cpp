/**
 * @file
 * @author  Chrisitan Urich <christian.urich@gmail.com>
 * @version 1.0
 * @section LICENSE
 *
 * This file is part of VIBe2
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

#include "grouptest.h"
#include <guigrouptest.h>



VIBe_DECLARE_GROUP_NAME(GroupTest, Loops)
GroupTest::GroupTest() {
    i = 0;
    Runs = 1;

    this->addParameter("Runs", DM::INT, &Runs);



}

void GroupTest::run() {
    this->Steps = Runs;



    Group::run();
}

void GroupTest::init() {



}

void GroupTest::addInPort(std::string n) {

    this->addTuplePort(n, DM::INTUPLESYSTEM);

}

void GroupTest::addOutPort(std::string n) {

    this->addTuplePort(n, DM::OUTTUPLESYSTEM);

}


bool GroupTest::createInputDialog() {

    QWidget * w = new GUIGroupTest(this);
    w->show();
    return true;
}
