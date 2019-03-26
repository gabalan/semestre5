// Pour utiliser les bibliothèques standards
import java.util.Random;
import java.util.Scanner;

class Mystere {
	// Permet de lire ce que l'utilisateur saisi au clavier
	public static Scanner clavier = new Scanner(System.in);

	public static void main(String[] args) {
		// Un générateur de nombre aléatoire
    int compteur=0;
		Random aleatoire = new Random();
    int essai=0;
    int mystere=0;
    int reste=0;
		// Génère un nombre compris entreo 0 et 100 (exclus)
    do{
    mystere = aleatoire.nextInt(100);
		System.out.print("Tirez un Nombre en 0 et 99: ");
		// Lit un entier au clavier, génère une erreur si la valeur saisie n'est pas un entier
		essai = clavier.nextInt();
    compteur=compteur+1;
    reste=10-compteur;
    System.out.println("Votre nombre est " + essai + " et le nombre mystere est " + mystere);
    System.out.println("vous avez esseyé "+compteur+" fois");
	}while(compteur<10 && essai!=mystere);
  if(essai!=mystere){
    System.out.println("vous avez perdu");
  }else{
    System.out.println("vous avez gagnez");
  }
}
}
