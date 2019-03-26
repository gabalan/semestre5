import fr.jussieu.script.*;

class Point
{
      int abs, ord;
      char nom;
}


class Test
{
// ***********************************************************************
// Méthodes modifiant des champs des objets qu'elles prennent en argument.
// ***********************************************************************

    /**
     * Correction de l'exercice 3, page 11, polycopié 4. Normalement,
     * on écrirait plutôt un constructeur qu'une telle méthode.
     * @param x l'abscisse du point à créer.
     * @param y l'ordonnée du point à créer.
     * @param c le nom du point à créer.
     * @return le point défini par les paramètres.
     */
      static Point nouveau (int x, int y, char c)

      {
         Point p = new Point ();
         p.abs = x;
         p.ord = y;
         p.nom = c;
         return p;
      }

    /**
     * Correction de l'exercice 4, page 11, polycopié 4.
     */
      static Point translate (Point a, int dx, int dy)
      {
         Point p = new Point ();
         p.abs = a.abs + dx;
         p.ord = a.ord + dy;
         p.nom = a.nom;
         return p;
      }

    /**
     * Correction de l'exercice 4, page 11, polycopié 4.
     * Le point calculé par cette méthode n'est pas exactement le milieu,
     * car les coordonnées sont entières.
     */
      static Point milieu (Point a, Point b, char c)
      {
         Point p = new Point ();
         p.abs = (a.abs + b.abs)/2;
         p.ord = (a.ord + b.ord)/2;
         p.nom = c;
         return p;
      }

// ***********************************************************************
// Méthodes modifiant des champs des objets qu'elles prennent en paramètre.
// ***********************************************************************

    /**
     * Correction de l'exercice 1, page 14, polycopié 4.
     */
      static void deplacer (Point a, int x, int y)
      {
         a.abs = x;
         a.ord = y;
         // On ne retourne rien.
         // Les champs de a ont été modifiés.
      }

    /**
     * Correction de l'exercice 2, page 14, polycopié 4.
     */
      static void translater (Point a, int dx, int dy)
      {
         deplacer (a, a.abs + dx, a.ord + dy);
      }

    /**
     * Correction de l'exercice 3, page 14, polycopié 4.
     */
      static void ajouter (Point a, Point b)
      {
         translater (a, b.abs, b.ord);
      }

    /**
     * Méthode d'affichage d'un point.
     * @param p le point à afficher.
     */
      static void afficher (Point p)
      {
         Deug.println ("Point " + p.nom + " d'abscisse " + p.abs + " et d'ordonnée " + p.ord);
      }

      public static void main (String [] args)
      {
         Deug.println ("Utilisation des méthodes accédant aux champs");
         Point p = nouveau (1,2,'x');
         Deug.print("\t\t(Variable p) ");
         afficher(p);

         Point q = translate (p, 2, 2);
         Deug.print("\t\t(Variable q) ");
         afficher(q);

         Point r = milieu(p,q,'a');
         Deug.print("\t\t(Variable r) ");
         afficher(r);

         Deug.println ("\nUtilisation des méthodes modifiant les champs");
         Deug.print("\t\t(Variable p) ");
         afficher(p);

         deplacer (p,10,10);
         Deug.print("\n\tAprès deplacer(p,10,10)\n\t\t(Variable p) ");
         afficher(p);

         translater (p,4,5);
         Deug.print("\n\tAprès translater(p,4,5)\n\t\t(Variable p) ");
         afficher(p);

         ajouter (p,p);
         Deug.print("\n\tAprès ajouter(p,p)\n\t\t(Variable p) ");
         afficher(p);
      }
