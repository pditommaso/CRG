/*
 * HMMTest.cpp
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
 * \file HMMTest.cpp
 * \brief .
 */


#ifndef HMMTEST_HPP_
#define HMMTEST_HPP_

#include "../../src/lib/Sequence/Sequence.h"
#include "../../src/lib/HMM/HMM.h"
#include "../../src/lib/HMM/fw_bw.h"

BOOST_AUTO_TEST_SUITE(HMM_Test)

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( HMM_Test )
{
	BioTools::Seq::Sequence seq1("NAME", "COMMENT", "CLCOCLDREAITRS");
	BioTools::Seq::Sequence seq2("NAME2", "COMMENT", "ARTLKIREGTTW");
	BioTools::HMM::HMM hmm('P');

	BioTools::Utils::Matrix<float> forward_mat = BioTools::Utils::Matrix<float>(15, 15);
	BioTools::Utils::Matrix<float> backward_mat = BioTools::Utils::Matrix<float>(15, 15);
	float **insert_matrices = new float*[8];
	for (size_t i=0; i<8; ++i)
		insert_matrices[i] = new float[15];

	BioTools::Seq::Sequence seq3("NAME", "COMMENT", "SRTIAERDLCOCLC");
	BioTools::Seq::Sequence seq4("NAME2", "COMMENT", "WTTGERIKLTRA");

	float fw_p = hmm_forward(seq1, seq2, hmm, forward_mat, insert_matrices);
	float bw_p =hmm_backward(seq3, seq4, hmm, backward_mat, insert_matrices);
	BOOST_CHECK_EQUAL(fw_p, bw_p);

}

BOOST_AUTO_TEST_SUITE_END()

#endif /* HMMTEST_HPP_ */
