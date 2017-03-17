/*
 * AlignmentTest.cpp
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
 * \file AlignmentTest.cpp
 * \brief .
 */


#ifndef AlignmentTEST_HPP_
#define AlignmentTEST_HPP_

#include "../../src/lib/Sequence/Sequence.h"
#include "../../src/lib/Sequence/Alignment.h"


BOOST_AUTO_TEST_SUITE(Alignment_Test)

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( Alignment_Test )
{
	BioTools::Seq::Alignment aln;
	aln.addSeqAln(new BioTools::Seq::Sequence("NAME", "COMMENT", "CLCOCLDREAITRS"));
	aln.addSeqAln(new BioTools::Seq::Sequence("NAME2", "COMMENT2", "XXCOCLDREAITRS"));
    
	BioTools::Seq::Alignment alnCopy;
	alnCopy.copyAln(aln);
	
	printf("Number of seqs in Initial Alignment: %d\n", aln.n_seqs() );
	printf("Number of seqs in Copy Alignment: %d\n", alnCopy.n_seqs() );
	printf("Initial Alignment length: %d\n", aln.size() );
	printf("Copy Alignment length: %d\n", alnCopy.size() );
	
	printf("Initial Alignment ID: %d\n", aln.id() );
	printf("Copy Alignment ID: %d\n", alnCopy.id() );
	
	BOOST_CHECK_EQUAL(alnCopy[0].sequence(), aln[0].sequence());
	alnCopy[0][1] = 'X';
	BOOST_CHECK_EQUAL(alnCopy[0][1], 'X');
	BOOST_CHECK_EQUAL(aln[0][1], 'L');
    BOOST_CHECK_EQUAL(alnCopy[1][1], 'X');
    BOOST_CHECK_EQUAL(alnCopy[1].name(), "NAME2");
}

BOOST_AUTO_TEST_SUITE_END()

#endif /* AlignmentTEST_HPP_ */
