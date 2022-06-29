#include <iostream>

class Configuration
{
public: 
  int depth;
  int nDims;
  int base;
  int seed;
  int npts; // number of points to generate,
  int m; // input matrix size,
  bool owen_permut_flag; // apply Owen permutation on output points,
  int nbReal; // number of realizations of the sampler (for the scrambling)
  bool dbg_flag; // dbg_flag,
  std::string output_fname; // output samples filename,
  std::string input_matrices;


  Configuration();
  ~Configuration();
};

