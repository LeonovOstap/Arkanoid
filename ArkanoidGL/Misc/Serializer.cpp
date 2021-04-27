#include "Serializer.h"

#include <prcore/filestream.hpp>
#include <prcore/stream.hpp>

#include "Util.h"
#include "../general/Game.h"
#include "../general/GameObject.h"
#include "../general/World.h"

using namespace prcore;


struct SerializationData
{
    
};

void Serializer::Serialize(const char* file)
{
    FileStream ss = FileStream(file, Stream::WRITE);
    ss.Seek(0, Stream::START);

    std::vector<class Serializable*> ObjectPool;

    for(auto GameObj : GGameProcess->getWorld()->GameObjects)
    {
        if(GameObj->IsSerializable())
            ObjectPool.push_back(GameObj);
    }
    
    WriteLittleEndian<int>(ss,ObjectPool.size());

    cout << printf("Found %i Objects in serialization pool",ObjectPool.size()) << endl;

    for(Serializable* sr : ObjectPool)
    {
        char* t_n = const_cast<char*>(typeid(*sr).name());
        util::serialization::WriteStr(ss,t_n);
        sr->Serialize(ss);
        
        cout << printf("Object type %s serialized (%i) bytes",t_n,sizeof(*sr)) << endl; 
    }


    //ss.Release();
}

void Serializer::DeserializeAll(const char* file)
{
    FileStream is = FileStream(file, Stream::READ);
    is.Seek(0, Stream::START);

    int loopIters = ReadLittleEndian<int>(is);

    cout << printf("Found %i Objects written ",loopIters) << endl;
    

    for(int i = 0; i < loopIters;++i)
    {
        //size_t typeSize = ReadLittleEndian<float>(is);
        
        
        //Sar = util::identAndMalloc(typeSize);

        // Sar->Deserialize(is);
        //ReadVec

        // cout << Sar << endl;

        char* t_n = util::serialization::ReadStr(is);
        Serializable* us_obj = util::serialization::identAndMalloc(t_n);
        us_obj->Deserialize(is);
        cout << printf("Object type %s loaded (%i) bytes",t_n,sizeof(*us_obj)) << endl; 
    }


    
}

