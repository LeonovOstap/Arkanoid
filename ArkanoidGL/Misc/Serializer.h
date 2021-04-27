#pragma once
#include <sstream>
#include <vector>
#include <prcore/stream.hpp>

class Serializer
{
public:
    void Serialize(const char* file);

    void DeserializeAll(const char* file);


};
class Serializable
{
    friend class Serializer;
    friend class Player;
public:
    
    Serializable() =default;

protected:
    virtual bool IsSerializable() {return false;}
    virtual void Serialize(prcore::Stream& stream) = 0;
    virtual void Deserialize(prcore::Stream& stream) = 0;
};