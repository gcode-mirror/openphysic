Cross compilation x86->ARM (iPaq)
Pour WinCE
PocketPC-gcc


Pour Linux pour PocketPC
http://www.handhelds.org/moin/moin.cgi/GpeCrossCompilation
http://www.scratchbox.org/ (projet r�cent)

http://people.debian.org/~debacle/cross/ (plus vieux)
voir toolchain-source dpkg-cross

http://www.aleph1.co.uk/oldsite/armlinux//docs/toolchain/




On peut v�rifier le binaire g�n�r� avec la commande "file"




On peut directement passer l'argument CC (compilateur) au Makefile
exemple :
make CC=arm-linux-gcc


avec les GNU/Autotools on proc�de ainsi :
./configure --host=arm-linux




Scratchbox http://www.scratchbox.org/documentation/user/scratchbox-1.0/html/installdoc.html
Penser � ajouter l'utilisateur au groupe sbox
# sb-adduser <username>
$ groups   # on doit voir sbox
$ /scratchbox/login

