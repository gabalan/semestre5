public class Ville{
  String nomville;
  String nompays;
  int nbrehabitants;


public Ville(){
  System.out.println("salut");
  nomville="inconnu";
  nompays="inconnu";
  nbrehabitants=0;
}
public Ville(String pNom, int pNbre, String pPays)
  {
    System.out.println("Création d'une ville avec des paramètres !");
    nomVille = pNom;
    nomPays = pPays;
    nbreHabitants = pNbre;
  }
}
