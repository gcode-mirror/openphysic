Objet Visual Basic 6 permettant d'acc�der � la carte d'entr�e/sortie Labjack U12
================================================================================
Entr�es / sorties num�riques
============================

Installation (pour les utilisateurs de l'objet)
============
Ex�cuter l'installeur U12SetupV120a.exe
 (ce fichier fournit par Labjack installe les DLL, les contr�les OCX (ActiveX), etc... n�cessaires � l'utilisation de la carte

Copier le fichier ES_Analog_LabjackU12.ocx dans le r�pertoire
C:\Program Files\DevStudio\VB\ES_Num_LabjackU12
ou
C:\Program Files\Microsoft Visual Studio\VB98\ES_Analog_LabjackU12

Premi�re utilisation (par administrateur)
Fichier Nouveau projet Exe
Clic droit sur composant et Parcourir
Led.ocx
ByteDisplay.ocx
ES_Num_Labjack_U12.ocx

Placer sur la feuille ES_Num_Labjack_U12

Tester avec un utilisateur restreint


Utilisation du composant
========================
Fichier Nouveau projet Exe
Clic droit sur composant et ajouter ES_Num_LabjackU12


D�veloppeur (pour modifier l'objet et en recr�er un)
===========
ES_Num.ctl : fichier contr�le Utilisateur
Test et modification du contr�le utilisateur
 ouvrir le projet Test_ES_Num_LabjackU12.vbp
 Rem : mettre la propri�t� Public du contr�le utilisateur � False 
 Ex�cuter avec compilation compl�te
 modifier, etc...

Cr�ation du fichier ocx
 ouvrir le projet ES_Num_LabjackU12.vbp
 Rem : mettre la propri�t� Public � True
 Menu Fichier>Cr�er fichier.ocx
 

D�ploiement
 voir installation (pour les utilisateurs de l'objet)