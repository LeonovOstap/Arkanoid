#include "GameObject.h"


#include <prmath/intersect.hpp>
#include <prmath/vector2.hpp>
#include <prmath/vector3.hpp>
#include <prmath/vector3float.hpp>



#include "Game.h"
#include "../mesh/MeshFactory.h"
#include "../misc/Util.h"
#include "../Physics/PhysicsSolver.h"


GameObject::~GameObject()
{
}

void GameObject::update(double delta)
{
    //if(attributes != STATIC)

    linear_velocity = util::clamp(linear_velocity,-70,70);
    
    position += linear_velocity * delta;
}

void GameObject::render()
{
    if (attributes & NO_DRAW)
        return;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glLoadMatrixf(getWorldTransform().m16);
    updateTransform();
    /*glTranslatef(position.x,position.y,position.z);
    glRotatef(quat.x,1,0,0);
    glRotatef(quat.y,0,1,0);
    glRotatef(quat.z,0,0,1);
    glScalef(scale.x,scale.y,scale.z);

    //todo:: this should not be in render()
    float m16[16];
    matrix4x4f r;
    
    glGetFloatv(GL_MODELVIEW_MATRIX,m16);

    //Convert to 4x4 matrix
    for ( int i=0; i<4; ++i )
    {
        const float* v = m16 + i * 4;
        r.m44[i][0] = v[0];
        r.m44[i][1] = v[1];
        r.m44[i][2] = v[2];
        r.m44[i][3] = v[3];
    }
    
    transform = r;*/

    glBindTexture(GL_TEXTURE_2D, model.GetTexture());
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 1.f, 1.f);
    const prcore::Array<primport::VertexMDL>& va0 = model.GetModel()->frames[0].vertexarray;

    for (int i = 0; i < model.GetModel()->faces.GetSize(); ++i)
    {
        const primport::FaceMDL& face = model.GetModel()->faces[i];

        for (int j = 0; j < 3; ++j)
        {
            int index = face.index[j];

            glTexCoord2fv(face.texcoord[j]);
            glNormal3fv(va0[index].normal);
            glVertex3fv(va0[index].point);
            //glDrawArrays()
        }
    }
    glEnd();

    // glGenVertexArray
}

void GameObject::Serialize(prcore::Stream& stream)
{
    using namespace util::serialization;

    //WriteLittleEndian<char*>(stream, (char*)Object);
    //Array<char> v = util::strToBinary(Object->model->filePath);
    //WriteLittleEndian<Array<char>>(ss, v);

    WriteVector(stream,position);
    WriteVector(stream,rotation);
    WriteVector(stream,scale);
    WriteVector(stream,linear_velocity);
    WriteLittleEndian<EGameObjectAttributes>(stream,attributes);

    WriteStr(stream,const_cast<char*>(model.GetPath()));
    
}

void GameObject::Deserialize(prcore::Stream& stream)
{
    using namespace util::serialization;
    //char* mem_offset = ReadLittleEndian<char*>(is);

    //GameObject* Object = (GameObject*)mem_offset;
    //if(!Object)
    //Object = static_cast<GameObject*>(malloc(sizeof(GameObject)));

    //Array<char> c;


    //String model = util::binaryToStr(ReadLittleEndian<Array<char>>(is));
    //Object->model = MeshFactory::Get().ConstructObject(model);

    position = ReadVector(stream);
    rotation = ReadVector(stream);
    scale = ReadVector(stream);
    linear_velocity = ReadVector(stream);

    attributes = ReadLittleEndian<EGameObjectAttributes>(stream);

    char* modelpath = ReadStr(stream);
    if(strlen(modelpath) > 0)
        model = MeshFactory::Get().ConstructObject(modelpath);

    worldPointer = GGameProcess->getWorld();

    GGameProcess->getWorld()->GameObjects.push_back(this);

    
}

void GameObject::handle_collision(hit_info& info)
{
   // linear_velocity = Reflect(linear_velocity, info.hit_normal * -1);

    //this was supposed to be penetration resolution
    //position += info.hit_normal * 0.5f;

    linear_velocity = util::reflection(linear_velocity,info.hit_normal);

    
    //cout << info.hit_normal.x << " " << info.hit_normal.y << " " << info.hit_normal.z << endl;

   // attributes |= NO_COLLISION_RESPONSE;

    //cout << info.hit_normal.x << " " << info.hit_normal.y << " " << info.hit_normal.z << endl;
}
