/*
 * TreeTest.cpp
 *
 *  Created on: 13 Jun 2014
 *      Author: Carsten Kemena
 *		 Email: CarstenK[@]posteo.de
 *	 Copyright: 20142013
 *
 *  This file is part of BioTools.
 *
 *  BioTools is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  BioTools is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with BioTools.  If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * \file TreeTest.cpp
 * \brief .
 */


#ifndef TREETEST_HPP_
#define TREETEST_HPP_

#include "../../src/lib/TreeClustering/Tree.h"


BOOST_AUTO_TEST_SUITE(Tree_Test)

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( Tree_Test )
{
	BioTools::TreeClustering::Tree tree;
	tree.read_newick("../tests/clustering/data/tree1.nwk");
	BOOST_CHECK_EQUAL(tree.newickString(), "(A,(B,C,D),(E,F));");
}

BOOST_AUTO_TEST_SUITE_END()

#endif /* TREETEST_HPP_ */
