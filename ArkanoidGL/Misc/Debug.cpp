#include "Util.h"
#include <GL/GL.h>

void util::debug::drawDebugBox(matrix4x4f transform, box3f box, color3f color)
{
    point3f box0[8];
    box = collision::CalculateAABB(box, transform);
    box.GetVertexArray8(box0);

    toOGLColor(color);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINE_LOOP);
    glColor3f(color.r, color.g, color.b);
    glVertex3fv(box0[0]);
    glVertex3fv(box0[1]);
    glVertex3fv(box0[3]);
    glVertex3fv(box0[2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3fv(box0[4]);
    glVertex3fv(box0[5]);
    glVertex3fv(box0[7]);
    glVertex3fv(box0[6]);
    glEnd();
    glBegin(GL_LINES);
    for (int j = 0; j < 4; ++j)
    {
        glVertex3fv(box0[j]);
        glVertex3fv(box0[j + 4]);
    }
    glEnd();
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
}

void util::debug::drawDebugSphere(matrix4x4f transform, sphere3f sphere, color3f color, int lat, int lon)
{
    //sphere = collision::SphereToWorld(sphere,Obj->getLocation(),Obj->getScale());
    //sphere.center *= transform;
    int i, j;
    int r = sphere.radius;
    toOGLColor(color);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(transform.m16);
    glScalef(1.2, 1.2, 1.2);
    glDisable(GL_TEXTURE_2D);

    for (i = 0; i <= lat; i++)
    {
        double lat0 = prmath::pi * (-0.5 + static_cast<double>(i - 1) / lat);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = prmath::pi * (-0.5 + static_cast<double>(i) / lat);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_LINE_LOOP);
        glColor3f(color.r, color.g, color.b);
        for (j = 0; j <= lon; j++)
        {
            double lng = 2 * prmath::pi * static_cast<double>(j - 1) / lon;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
}

void util::debug::drawDebugLine(matrix4x4f transform, vec3f start, vec3f end, color3f color)
{
    toOGLColor(color);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(transform.m16);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINE_LOOP);
    glColor3f(color.r, color.g, color.b);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
    glColor3f(1.f, 1.f, 1.f);
    glEnable(GL_TEXTURE_2D);
}
