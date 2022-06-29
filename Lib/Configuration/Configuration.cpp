#include <iostream>
#include "Configuration.hpp"


Configuration::Configuration(){
  std::cout << "Test" << std::endl;
  depth = 19;
  nDims = 2;
  base = 3;
  seed = rand() %  65537;
  npts = 729; // number of points to generate,
  m = 19; // input matrix size,
  owen_permut_flag = true; // apply Owen permutation on output points,
  nbReal = 1; // number of realizations of the sampler (for the scrambling)
  dbg_flag = true; // dbg_flag,
  output_fname = "out.dat"; // output samples filename,
  input_matrices = "../MatBuilder_matrices/2D_0m2net_000001.dat";
  std::cout << nDims << std::endl;
}







Configuration::~Configuration(){

}
