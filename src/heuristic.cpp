#include "heuristic.h"


// You can include an option like -Dwhatever_HEURISTIC in the compilation line of the Makefile to choosa a heuristic, using here the ifdef...

// no informativa
#ifdef ni_HEURISTIC
float h(position p,lp goals)
{
 return 0.0;
}
#endif

// Euclidea
#ifdef euclidea_HEURISTIC
float h(position p,lp goals)
{
    float d = 0, min = FLT_MAX;
    for(lp::iterator it=goals.begin(); it!=goals.end(); it++){
        d = sqrt(pow(p.first - (*it).first, 2) + pow(p.second - (*it).second, 2));
        if(d < min){
             min = d;
        }
    }
 return min;
}
#endif

// Manhattan
// |x-x'|+|y-y'|
#ifdef manhattan_HEURISTIC
float h(position p,lp goals)
{
    float d = 0,min = FLT_MAX; 
    
    for(lp::iterator it=goals.begin();it!=goals.end();it++){
        d = abs(p.first - (*it).first) + abs(p.second - (*it).second);
        if(d < min){
             min = d;
        }
    }
 return min;
}
#endif
