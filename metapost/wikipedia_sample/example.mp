transform pagecoords;
pagecoords:=identity scaled 10mm shifted (100mm,150mm);

beginfig(1)
    fill ((0,0)--(2,0)--(2,1)--(1,1)--(1,2)--(0,2)--cycle)
        transformed pagecoords withcolor green;
    draw ((2,0)..(2,1)..(1,1)..(1,2)..(0,2))
        transformed pagecoords;
    drawarrow ((0,0)--(2,2)) transformed pagecoords;
endfig;

beginfig(2)
    draw (for i=0 upto 7: dir(135i)-- endfor cycle)
        transformed pagecoords;
endfig;
        
pagecoords:=identity scaled 15mm shifted (100mm,150mm);
beginfig(3);
    path p[],p[]t;
    z1=(0,0);   z2=z1+2up;
    z3=z1+whatever*dir(60)=z2+whatever*dir(-50);
    z4=z3+(-1.5,-.5);
    z5=z1+dir(135);
    z0=whatever[z1,z2]=whatever[z3,z4];
    p0=fullcircle yscaled .5 rotated 45 shifted z0 ;
    p1=z2--z4..z0..z3---z1;
    p2=p1 cutbefore p0 cutafter p0;
    p3=p0 cutbefore p1 cutafter p1;
    p4=p2--p3--cycle;
    for i=0 upto 4: p[i]t=p[i] transformed pagecoords; endfor
    for i=0 upto 5: z[i]t=z[i] transformed pagecoords; endfor
    fill p4t withcolor (1,1,0.2);
    draw z1t--z2t withcolor .5white;
    draw z3t--z4t withcolor .5white;
    pickup pencircle;
    draw p0t dashed withdots scaled .3;
    draw p1t dashed evenly;
    draw p2t withcolor blue;
    draw p3t withcolor red;
    label.lrt(btex $z_0$ etex, z0t);
    label.llft(btex $z_1$ etex, z1t);
    label.top(btex $z_2$ etex, z2t);
    label.rt(btex $z_3$ etex, z3t);
    label.llft(btex $z_4$ etex, z4t);
    for i=0 upto 4:
        drawdot z[i]t withpen pencircle scaled 2;
    endfor
endfig;
bye