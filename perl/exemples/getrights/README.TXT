:: Un script pour enregistrer/restaurer les permissions sur les fichiers et repertoires
:: redig� par fab
:: distribuable selon les termes de la FDL


Dans un souci de s�curisation, j'ai voulu faire diff�rents essais sur les permissions de mon systeme. Il me fallait un moyen simple pour pouvoir revenir en arri�re et je n'ai pas assez de Go libres pour pouvoir tout sauver... J'ai donc eu l'id�e de ce script, il necessite uniquement une version convenable de perl.

Son utilisation :

./getrights > perms
(tapez ENTER une fois le programme execut�)
Cela enregistre les droits et les utilisateurs pour le r�pertoire '/' r�cursivement dans "perms", regardez le d�but du script pour changer qques variables (pour ne pas TOUT sauvegarder par exemple). Sur mon systeme, 600ko son suffisant pour tout enregistrer.

./getrights < perms
Restaure les droits/utilisateurs/groupes pour tous les fichiers ki ont �t� plac�s dans "perms"