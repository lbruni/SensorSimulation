
#include "run_simulation.cpp"
#include "TApplication.h"
#include "TBrowser.h"

//int main() {
////  int argc_asdasddsa = 1;
////  char **argv_sadsda = new char*[1];
////  argv_sadsda[0] = "dummy";
////  TApplication theApp("App", &argc_asdasddsa, argv_sadsda);
////
////  run_cluster_size_simulation r;
////    r.LoopOnSigma();
////    new TBrowser();
////    theApp.Run();
////    return 0;
//}
void run(){
  run_simulation r;
    //r.LoopOnSigma();
    //r.init();
    //r.loop(1);
    r.run_efficiency();
    
}
