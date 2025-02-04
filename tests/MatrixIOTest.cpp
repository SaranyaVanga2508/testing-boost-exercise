#define BOOST_TEST_DYN_LINK

#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include "../src/matrixIO.hpp"

using namespace Eigen;
using namespace std;
using namespace matrixIO;

BOOST_AUTO_TEST_SUITE(MatrixIOTestSuite, *boost::unit_test::tolerance(1e-6))

// **Test Case: Successfully read a matrix from a CSV file**
BOOST_AUTO_TEST_CASE(TestOpenData)
{
  const string testFileName = "test_matrix.csv";

  // Create expected 3x3 matrix
  MatrixXd expectedMatrix(3, 3);
  expectedMatrix << 0.680375, 0.59688, -0.329554,
      -0.211234, 0.823295, 0.536459,
      0.566198, -0.604897, -0.444451;

  // Write to a CSV file
  ofstream file(testFileName);
  if (file.is_open()) {
    file << "0.680375, 0.59688, -0.329554\n"
         << "-0.211234, 0.823295, 0.536459\n"
         << "0.566198, -0.604897, -0.444451\n";
    file.close();
  } else {
    BOOST_FAIL("Could not create test CSV file!");
  }

  // Read matrix from the CSV file
  MatrixXd loadedMatrix = openData(testFileName, 3);

  // Compare with expected matrix
  BOOST_TEST(loadedMatrix.isApprox(expectedMatrix));

  // **Delete test file after the test**
  remove(testFileName.c_str());
}

BOOST_AUTO_TEST_SUITE_END()
