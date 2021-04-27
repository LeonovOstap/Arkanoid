# Arkanoid
Simple 3D arkanoid using Opengl + Prophecy SDK

At this state, i would say its 60% ready. Sure you can play around with your ball(s), but you will get annoying problems like: memory leaks, ui absence etc.etc.
For now im not planning to continue developing this project, but maybe one day it`ll change...

dependencies and requirements - 
    - Visual Studio 2017  <br>
    - Prophecy SDK (https://www.twilight3d.com/)  <br>
    - OpenGL (i used the one from WinSDK,it sucks btw)  <br>
    
 There is a lot of disabled functions/classes but still, you can play and (presumably) have fun with it.
 
 The core principle behind this, is to import MDL(Q1) files using primport(from prophecysdk),and then render them in realtime using OGL.
 The physics simulations,movement, serialization is all done by me.
 
And couple of words about init process: 
So it works like this - <br>
    1. We deserialize object properties from level file (.sar)  <br>
    2. We spawn those objects in World class  <br>
    3. Then world class updates and executes draw calls each frame  <br>
    5. Profit, you have a game  <br>
Although its not so simple, you get an idea.

If you want to test it yourself, you can download executable from releases folder.GL
