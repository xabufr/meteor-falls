#include "EngineManager.h"

Engine* EngineManager::get(EngineType p_engine_type){
    int i;
    for(i=0;i<=engines.size();i++){
        if(p_engine_type == engines[i]->getType()){
            return engines[i];
        }
    }
}