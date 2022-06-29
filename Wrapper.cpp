
  /*
Copyright 2022, CNRS
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <iostream>
#include <stdlib.h> 
#include <sys/stat.h>
#include <ios>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <vector>
#include <cstring>
#include <fstream>
#include "MatrixTools.h"
#include "MatrixSamplerClass.h"
#include "Scrambling.h"
#include "CLI11.hpp"
#include "Lib/Configuration/Configuration.hpp"

/* ------ Utils ------ */


bool DoesPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

std::string i2s(int acct_no) {
  std::ostringstream out;
  out << std::internal << std::setfill('0') << std::setw(8) << acct_no;
  return out.str();
}


// InitVariables

void initVariables(int& depth, int& nDims, int& base, int& seed, int& npts, int& m,bool& owen_permut_flag, int& nbReal, bool& dbg_flag,std::string& output_fname, std::string& input_matrices){


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


  return;
}

// FillPointTable

void fillPointTable(int innoctave = 10, int insetNo = 1, bool prevFlag = false, bool debug = true,double** pointHolder = nullptr){
  
  int depth = 19;
  int nDims = 2;
  int base = 3;
  int seed = rand() %  65537;
  int npts = 729; // number of points to generate,
  int m = 19; // input matrix size,
  bool owen_permut_flag = true; // apply Owen permutation on output points,
  int nbReal = 1; // number of realizations of the sampler (for the scrambling)
  bool dbg_flag = true; // dbg_flag,
  std::string output_fname = "out.dat"; // output samples filename,
  std::string input_matrices = "../MatBuilder_matrices/2D_0m2net_000001.dat";

  if (depth == -1)
    depth = m;

  std::ifstream in(input_matrices);
  if (in.fail()) {
    std::cerr << "Error: Could not open input file: " << input_matrices << std::endl;
    exit(-1);
  }

  std::ofstream out(output_fname);
  if (out.fail()) {
    std::cerr << "Error: Could not open output file: " << output_fname << std::endl;
     exit(-1);
  }
  std::cout << seed << std::endl;  
initVariables(depth,nDims,base, seed, npts, m, owen_permut_flag, nbReal, dbg_flag, output_fname, input_matrices); 
 std::cout << seed << std::endl; 
  
 

  out << std::setprecision(16);

  std::vector<std::vector<int> > Bs(nDims, std::vector<int>(m*m));
  std::vector<std::vector<int> > Cs(nDims, std::vector<int>(m*m));

  readMatrices(in, m, nDims, Cs);

  if(dbg_flag) {
    writeMatrices(std::cout,m,Cs,true);
  }
  std::minstd_rand gen(seed);
  std::uniform_int_distribution<int> unif;
  for (int real = 0; real < nbReal; ++real) {
    int real_seed = unif(gen);
    for (int indpt = 0; indpt < npts; ++indpt) {
      for (int inddim = 0; inddim < nDims; ++inddim) {
        double pos;
        if (owen_permut_flag){
          pos = getScrambledDouble(Cs[inddim], m, base, indpt, real_seed + inddim, depth);
          pointHolder[indpt][inddim] = pos;
        } else {
          pos = getDouble(Cs[inddim], m, base, indpt);
        }
        out << pos << " ";
        if(dbg_flag) std::cout << " " << pos << " | ";
      }
      out << std::endl;
      if(dbg_flag) std::cout << std::endl;
    }
    if (real != nbReal-1) out << "#" << std::endl;
  }
  out.close();







}


// FillTilesVector

  
  
  
  
  
  
  
  




int main(int argc, char *argv[])
{
  srand (time(NULL));
  

  /* ------- Lecture du fichier de configuration -------- */


  Configuration* config = new Configuration();
  // config->init();

  /* ------- Initialisation du tableau de point initiaux ------ */
  


  double **pointHolder = new double*[config->npts];
  for (int i = 0; i < config->npts; ++ i) {
   pointHolder[i] = new double[config->nDims]; 
  }
  fillPointTable(10,1,false,true,pointHolder);
    
  std::cout << RAND_MAX << std::endl;
  std::cout << std::to_string(DoesPathExist("Here"))<< std::endl;


  /* ------ Initialisation du vecteur de tuile ------ */

  // InitVariables
  // FillPointTable
  // FillTilesVector


  delete(config);
  return 0;
}
