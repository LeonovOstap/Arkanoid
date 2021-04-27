#pragma once
#include <sstream>
#include <prcore/array.hpp>
#include <prcore/stream.hpp>
#include <prcore/string.hpp>
#include <prcore/timer.hpp>
#include <prmath/box.hpp>
#include <prmath/matrix4x4.hpp>
#include <prmath/vector2.hpp>


#include "../Physics/Collision.h"
#include "Serializer.h"
#include "../gameobject/Ball.h"
#include "../gameobject/GameTile.h"
#include "../gameobject/Player.h"
#include "../gameobject/TileSpawner.h"
#include "../general/GameObject.h"


namespace util
{
    //inline prcore::Array<char> strToBinary(prcore::String str)
    //{
    //    return std::hash<char>()
    //}

    inline void toOGLColor(color3f& color)
    {
        color /= 255;
    }
    
    inline float clamp(float num, float min, float max) {
        return std::max(min, std::min(num, max));
    }

    inline vec3f clamp(vec3f vec,float min,float max)
    {
        vec3f out = vec;
        out.x = clamp(out.x,min,max);
        out.y = clamp(out.y,min,max);
        out.z = clamp(out.z,min,max);
        return out;
    }

    inline vec3f reflection(vec3f direction,vec3f normal)
    {
        return direction - 2 * prmath::DotProduct(direction,normal) * normal;
    }

    inline void vinterp(vec3f& src,vec3f target,float time)
    {
        prcore::Timer t;
        vec3f identy = src;
        while(t.GetTime() < time)
        {
            //cout << time << " " << t.GetTime() << " " << t.GetTime()/time << endl;
            src = (identy + t.GetTime()/time * (target-identy));
            cout << src.x << " " << src.y << endl;
        }
        
    }


    namespace debug
    {
        void drawDebugBox(matrix4x4f transform, box3f box, color3f color);

        void drawDebugSphere(matrix4x4f transform,
                             sphere3f sphere,
                             color3f color,
                             int lat = 12,
                             int lon = 12);

        void drawDebugLine(matrix4x4f transform,
                           vec3f start,
                           vec3f end,
                           color3f color);
    }

    namespace serialization
    {
        using namespace prcore;
        inline vec3f ReadVector(Stream& stream)
        {
            vec3f k;
            k.x = ReadLittleEndian<float>(stream);
            k.y = ReadLittleEndian<float>(stream);
            k.z = ReadLittleEndian<float>(stream);
            return k;
        }

        inline void WriteVector(Stream& stream,vec3f v)
        {
            WriteLittleEndian<float>(stream,v.x);
            WriteLittleEndian<float>(stream,v.y);
            WriteLittleEndian<float>(stream,v.z);
        }

        //Code from KLX.cpp
        inline char* ReadStr(Stream& stream)
        {
            static char buffer[256];
            std::fill_n(buffer,256,0);

            int len = ReadLittleEndian<int>(stream);

            char* ptr = buffer;
            for (int i = len; i > 0; --i)
            {
                char c;
                stream.Read(&c,1);
                if ( !c)
                    break;
                *ptr++ = c;

                
            }

            return buffer;
        }

        inline void WriteStr(Stream& stream,char* str)
        {
            char* ptr = str;
            WriteLittleEndian<int>(stream,strlen(str));
            for (char c = *ptr; c; c=*++ptr) {
                stream.Write(&c,1);

                if(!c)
                    break;
            }
            //stream.Write("\n",1);
        }

        // i dont have a time for reflection system(
        // and yes RTTI will dump your performance
        inline Serializable* identAndMalloc(const char* t_n)
        {
            auto pn = typeid(Player).name();
            bool b = std::string(typeid(Player).name()) == t_n;
            if(std::string(typeid(GameObject).name()) == t_n)
                return new GameObject(Mesh());

            if(std::string(typeid(Player).name()) == t_n)
                return new Player(Mesh());

            if(std::string(typeid(GameTile).name()) == t_n)
                return new GameTile(Mesh());

            if(std::string(typeid(Ball).name()) == t_n)
                return new Ball(Mesh());

            if(std::string(typeid(MediumTileGrid12x).name()) == t_n)
                return new MediumTileGrid12x(Mesh());
            
            if(std::string(typeid(SmallTileGrid8x).name()) == t_n)
                return new SmallTileGrid8x(Mesh());

            if(std::string(typeid(LargeTileGrid24x).name()) == t_n)
                return new LargeTileGrid24x(Mesh());
            
            return nullptr;
        }
        
        
    }
}
